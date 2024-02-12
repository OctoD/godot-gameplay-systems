#include <godot_cpp/classes/engine.hpp>

#include "attribute_container.h"
#include "attribute_manager.h"

using namespace ggs;

void AttributeContainer::_handle_attribute_owner_received_node(Node *p_node)
{
	if (p_node->get_class() == GameplayEffect::get_class_static())
	{
		GameplayEffect *attribute_effect = cast_to<GameplayEffect>(p_node);

		if (attribute_effect != nullptr)
		{
			apply_effect(attribute_effect);

			if (attribute_effect->get_parent() != nullptr)
			{
				attribute_effect->call_deferred("queue_free");
			}
		}
	}
}

void AttributeContainer::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("_handle_attribute_owner_received_node", "node"), &AttributeContainer::_handle_attribute_owner_received_node);
	ClassDB::bind_method(D_METHOD("apply_effect", "effect"), &AttributeContainer::apply_effect);
	ClassDB::bind_method(D_METHOD("count_timeouts", "attribute_effect"), &AttributeContainer::count_timeouts);
	ClassDB::bind_method(D_METHOD("ensure_attributes", "attributes"), &AttributeContainer::ensure_attributes);
	ClassDB::bind_method(D_METHOD("get_attribute", "attribute_name"), &AttributeContainer::get_attribute);
	ClassDB::bind_method(D_METHOD("get_attributes_as_dictionary"), &AttributeContainer::get_attributes_as_dictionary);
	ClassDB::bind_method(D_METHOD("get_attributes_owner"), &AttributeContainer::get_attributes_owner);
	ClassDB::bind_method(D_METHOD("get_attributes"), &AttributeContainer::get_attributes);
	ClassDB::bind_method(D_METHOD("get_ongoing_effects"), &AttributeContainer::get_ongoing_effects);
	ClassDB::bind_method(D_METHOD("has_attribute", "attribute_name"), &AttributeContainer::has_attribute);
	ClassDB::bind_method(D_METHOD("set_attributes_owner", "attributes_owner"), &AttributeContainer::set_attributes_owner);
	ClassDB::bind_method(D_METHOD("set_attributes", "attributes"), &AttributeContainer::set_attributes);

	/// properties binding
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "attributes_owner", PROPERTY_HINT_NODE_TYPE, "Node"), "set_attributes_owner", "get_attributes_owner");
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_RESOURCE_TYPE, "24/17:Attribute"), "set_attributes", "get_attributes");

	/// signals binding
	ADD_SIGNAL(MethodInfo("all_effects_removed"));
	ADD_SIGNAL(MethodInfo("attribute_buff_added", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute"), PropertyInfo(Variant::FLOAT, "buff_amount")));
	ADD_SIGNAL(MethodInfo("attribute_buff_set", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute"), PropertyInfo(Variant::FLOAT, "buff_amount")));
	ADD_SIGNAL(MethodInfo("attribute_buff_subtracted", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute"), PropertyInfo(Variant::FLOAT, "buff_amount")));
	ADD_SIGNAL(MethodInfo("attribute_changed", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute")));
	ADD_SIGNAL(MethodInfo("attribute_effect_applied", PropertyInfo(Variant::OBJECT, "attribute_effect", PROPERTY_HINT_RESOURCE_TYPE, "AttributeEffect")));
	ADD_SIGNAL(MethodInfo("attribute_effect_blocked", PropertyInfo(Variant::OBJECT, "attribute_effect", PROPERTY_HINT_RESOURCE_TYPE, "AttributeEffect")));
	ADD_SIGNAL(MethodInfo("attribute_effect_conditions_not_met", PropertyInfo(Variant::OBJECT, "attribute_effect", PROPERTY_HINT_RESOURCE_TYPE, "AttributeEffect")));
	ADD_SIGNAL(MethodInfo("attribute_effect_removed", PropertyInfo(Variant::OBJECT, "attribute_effect", PROPERTY_HINT_RESOURCE_TYPE, "AttributeEffect")));
	ADD_SIGNAL(MethodInfo("attribute_value_added", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute"), PropertyInfo(Variant::FLOAT, "value_amount")));
	ADD_SIGNAL(MethodInfo("attribute_value_set", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute"), PropertyInfo(Variant::FLOAT, "value_amount")));
	ADD_SIGNAL(MethodInfo("attribute_value_subtracted", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute"), PropertyInfo(Variant::FLOAT, "value_amount")));
}

void AttributeContainer::apply_attribute_effect(AttributeEffect *attribute_effect, Ref<Attribute> &attribute)
{
	if (get_multiplayer_authority() != 1)
	{
		return;
	}

	float affected_amount = attribute_effect->_calculate_affected_amount(this);

	switch (attribute_effect->get_application_type())
	{
	case AttributeEffect::ApplicationType::ADD_BUFF:
	{
		attribute->add_buff(affected_amount);
		emit_signal("attribute_buff_added", Ref<Attribute>(attribute), affected_amount);
		emit_signal("attribute_changed", Ref<Attribute>(attribute));
		break;
	}
	case AttributeEffect::ApplicationType::ADD_VALUE:
	{
		attribute->add_value(affected_amount);
		emit_signal("attribute_value_added", Ref<Attribute>(attribute), affected_amount);
		emit_signal("attribute_changed", Ref<Attribute>(attribute));
		break;
	}
	case AttributeEffect::ApplicationType::ADD_VALUE_OR_BUFF:
	{
		attribute->add_value_or_buff(affected_amount);
		emit_signal("attribute_value_added", Ref<Attribute>(attribute), affected_amount);
		emit_signal("attribute_changed", Ref<Attribute>(attribute));
		break;
	}
	case AttributeEffect::ApplicationType::SUBTRACT_BUFF:
	{
		attribute->subtract_buff(affected_amount);
		emit_signal("attribute_buff_subtracted", Ref<Attribute>(attribute), affected_amount);
		emit_signal("attribute_changed", Ref<Attribute>(attribute));
		break;
	}
	case AttributeEffect::ApplicationType::SUBTRACT_VALUE:
	{
		attribute->subtract_value(affected_amount);
		emit_signal("attribute_value_subtracted", Ref<Attribute>(attribute), affected_amount);
		emit_signal("attribute_changed", Ref<Attribute>(attribute));
		break;
	}
	case AttributeEffect::ApplicationType::SET_BUFF:
	{
		attribute->set_buff(affected_amount);
		emit_signal("attribute_buff_set", Ref<Attribute>(attribute), affected_amount);
		emit_signal("attribute_changed", Ref<Attribute>(attribute));
		break;
	}
	case AttributeEffect::ApplicationType::SET_VALUE:
	{
		attribute->set_value(affected_amount);
		emit_signal("attribute_value_set", Ref<Attribute>(attribute), affected_amount);
		emit_signal("attribute_changed", Ref<Attribute>(attribute));
		break;
	}
	}
}

bool AttributeContainer::are_attribute_conditions_met(AttributeEffect *attribute_effect)
{
	if (attribute_effect->get_conditions().size() > 0)
	{
		for (int i = 0; i < attribute_effect->get_conditions().size(); i++)
		{
			Variant condition = attribute_effect->get_conditions()[i];
			Ref<AttributeEffectCondition> attribute_effect_condition = Ref<AttributeEffectCondition>(condition);

			if (!attribute_effect_condition->_should_apply_effect(attribute_effect, this))
			{
				return false;
			}
		}
	}

	return true;
}

int AttributeContainer::increase_attribute_effect_timer_count(AttributeEffect *p_attribute_effect)
{
	int p_id = p_attribute_effect->get_instance_id();

	if (timeouts_count.has(p_id))
	{
		int count = timeouts_count[p_id];
		count++;
		timeouts_count[p_id] = count;
	}
	else
	{
		timeouts_count[p_id] = 1;
	}

	return timeouts_count[p_id];
}

AttributeContainer::AttributeContainer()
{
}

AttributeContainer::AttributeContainer(Array p_attributes)
{
	attributes = TypedArray<Attribute>(p_attributes);
}

AttributeContainer::AttributeContainer(TypedArray<Attribute> p_attributes)
{
	attributes = p_attributes;
}

AttributeContainer::AttributeContainer(Node *p_attributes_owner, TypedArray<Attribute> p_attributes)
{
	attributes_owner = p_attributes_owner;
	attributes = p_attributes;
	timeouts_count = Dictionary();
}

AttributeContainer::~AttributeContainer()
{
}

void AttributeContainer::_process(double delta)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		return;
	}

	_process_delta += delta;

	/// get if a second has passed since the last process
	/// note: this will have to be balanced once multiplayer api will kick in. The check should be made taking in consideration the average ping of the players.
	if (_process_delta - 1.0f >= 0.05f)
	{
		_process_delta = 0.0f;

		for (int i = ongoing_effects.size() - 1; i >= 0; i--)
		{
			Variant effect_variant = ongoing_effects[i];
			AttributeEffect *attribute_effect = cast_to<AttributeEffect>(effect_variant);

			if (attribute_effect == nullptr)
			{
				WARN_PRINT("ERR/GGS/S/A/AC::_p_000");
				continue;
			}

			Ref<AttributeEffect> attribute_effect_ref = Ref<AttributeEffect>(attribute_effect);
			Ref<Attribute> attribute_ref = get_attribute(attribute_effect->get_affected_attribute());

			int attribute_effect_application_count = increase_attribute_effect_timer_count(attribute_effect);

			if (attribute_effect->get_life_cycle() == AttributeEffect::LifeCycle::TIME_BASED && attribute_effect_application_count >= attribute_effect->get_applications_count())
			{
				ongoing_effects.remove_at(i);
				emit_signal("attribute_effect_removed", attribute_effect);
				continue;
			}

			switch (attribute_effect->get_break(this))
			{
			case AttributeEffectCondition::BreakType::NO_BREAK:
			{
				if (are_attribute_conditions_met(attribute_effect))
				{
					apply_attribute_effect(attribute_effect, attribute_ref);
				}
				else
				{
					emit_signal("attribute_effect_conditions_not_met", attribute_effect);
				}
				break;
			}
			case AttributeEffectCondition::BreakType::BREAK:
			{
				emit_signal("attribute_effect_blocked", attribute_effect);
				break;
			}
			case AttributeEffectCondition::BreakType::BREAK_RESET_COUNTER:
			{
				emit_signal("attribute_effect_blocked", attribute_effect);
				timeouts_count[attribute_effect->get_instance_id()] = 0;
				break;
			}
			case AttributeEffectCondition::BreakType::BREAK_REMOVE_ANY_ATTRIBUTE_EFFECT:
			{
				for (int j = ongoing_effects.size() - 1; j >= 0; j--)
				{
					Variant ongoing_effect_variant = ongoing_effects[j];
					AttributeEffect *ongoing_effect = cast_to<AttributeEffect>(ongoing_effect_variant);

					if (ongoing_effect != nullptr && ongoing_effect->get_rid() == attribute_effect->get_rid())
					{
						ongoing_effects.erase(ongoing_effect);
					}
				}
				emit_signal("attribute_effect_removed", attribute_effect);
				break;
			}
			case AttributeEffectCondition::BreakType::BREAK_REMOVE_ATTRIBUTE_EFFECT:
			{
				emit_signal("attribute_effect_blocked", attribute_effect);
				ongoing_effects.remove_at(i);
				emit_signal("attribute_effect_removed", attribute_effect);
				break;
			}
			}
		}
	}
}

void AttributeContainer::_ready()
{
	if (attributes_owner == nullptr)
	{
		attributes_owner = get_parent();
	}

	attributes_owner->connect("child_entered_tree", Callable(this, "_handle_attribute_owner_received_node"));
}

void AttributeContainer::apply_effect(GameplayEffect *p_game_effect)
{
	if (get_multiplayer_authority() != 1)
	{
		return;
	}

	TypedArray<AttributeEffect> effects = p_game_effect->get_attribute_effects_applied();

	for (int i = 0; i < effects.size(); i++)
	{
		Variant effect_variant = effects[i];
		AttributeEffect *attribute_effect = cast_to<AttributeEffect>(effect_variant);

		if (attribute_effect == nullptr)
		{
			WARN_PRINT("ERR/GGS/S/A/AC::AE_000");
			continue;
		}

		if (!has_attribute(attribute_effect->get_affected_attribute()))
		{
			WARN_PRINT("ERR/GGS/S/A/AC::AE_001");
			continue;
		}

		Ref<Attribute> attribute_ref = get_attribute(attribute_effect->get_affected_attribute());

		if (attribute_effect->get_life_cycle() == AttributeEffect::LifeCycle::ONE_TIME)
		{
			if (are_attribute_conditions_met(attribute_effect))
			{
				apply_attribute_effect(attribute_effect, attribute_ref);
			}
			else
			{
				emit_signal("attribute_effect_conditions_not_met", attribute_effect);
			}
		}
		else
		{
			ongoing_effects.push_back(attribute_effect);
		}
	}
}

int AttributeContainer::count_timeouts(AttributeEffect *p_effect)
{
	int p_id = p_effect->get_instance_id();

	if (timeouts_count.has(p_id))
	{
		return timeouts_count[p_id];
	}

	return 0;
}

void AttributeContainer::ensure_attributes(PackedStringArray p_attributes)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		PackedStringArray copy = p_attributes.duplicate();

		copy.sort();
		
		for (StringName tagname : copy)
		{
			if (!has_attribute(tagname))
			{
				Attribute *attribute = memnew(Attribute);

				attribute->set_tag_name(tagname);
				attributes.push_back(attribute);
			}
		}

		for (int i = 0; i < attributes.size(); i++)
		{
			Ref<Attribute> attribute = cast_to<Attribute>(attributes[i]);

			if (attribute.is_valid() && !attribute.is_null() && !p_attributes.has(attribute->get_tag_name()))
			{
				attributes.remove_at(i);
			}
		}
	}
}

bool AttributeContainer::has_attribute(StringName p_attribute_name) const
{
	for (int i = 0; i < attributes.size(); i++)
	{
		Variant attribute_variant = attributes[i];
		Attribute *attribute = cast_to<Attribute>(attribute_variant);

		if (attribute != nullptr && attribute->has_tag_name(p_attribute_name))
		{
			return true;
		}
	}

	return false;
}

Ref<Attribute> AttributeContainer::get_attribute(StringName p_attribute_name) const
{
	for (int i = 0; i < attributes.size(); i++)
	{
		Variant attribute_variant = attributes[i];
		Attribute *attribute = cast_to<Attribute>(attribute_variant);

		if (attribute != nullptr && attribute->has_tag_name(p_attribute_name))
		{
			return Ref<Attribute>(attribute);
		}
	}

	return nullptr;
}

TypedArray<AttributeEffect> AttributeContainer::get_ongoing_effects() const
{
	return ongoing_effects.duplicate(true);
}

Dictionary AttributeContainer::get_attributes_as_dictionary() const
{
	Dictionary attributes_dictionary;

	for (int i = 0; i < attributes.size(); i++)
	{
		Variant attribute_variant = attributes[i];
		Attribute *attribute = cast_to<Attribute>(attribute_variant);

		if (attribute != nullptr)
		{
			attributes_dictionary[attribute->get_tag_name()] = attribute->get_value();
		}
	}

	return attributes_dictionary;
}

Node *AttributeContainer::get_attributes_owner() const
{
	return attributes_owner;
}

TypedArray<Attribute> AttributeContainer::get_attributes() const
{
	return attributes;
}

void AttributeContainer::set_attributes(const TypedArray<Attribute> &p_attributes)
{
	attributes = p_attributes;
}

void AttributeContainer::set_attributes_owner(Node *p_attributes_owner)
{
	attributes_owner = p_attributes_owner;
}
