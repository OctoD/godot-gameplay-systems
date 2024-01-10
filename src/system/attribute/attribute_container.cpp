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

void AttributeContainer::_handle_timer_timeout(Timer *timer, Ref<AttributeEffect> &attribute_effect, Ref<Attribute> &attribute)
{
	int count = increase_attribute_effect_timer_count(timer->get_instance_id());

	if ((attribute_effect->get_life_cycle() == AttributeEffect::LifeCycle::INFINITE_TIME_BASED && should_break_attribute_effect(attribute_effect)) || (should_break_attribute_effect(attribute_effect) || count >= attribute_effect->get_applications_count()))
	{
		timeouts_count.erase(timer->get_instance_id());
		timer->stop();
		timer->call_deferred("queue_free");
		return;
	}

	apply_attribute_effect(attribute_effect, attribute);
}

void AttributeContainer::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("_handle_attribute_owner_received_node", "node"), &AttributeContainer::_handle_attribute_owner_received_node);
	ClassDB::bind_method(D_METHOD("apply_effect", "effect"), &AttributeContainer::apply_effect);
	ClassDB::bind_method(D_METHOD("ensure_attributes", "attributes"), &AttributeContainer::ensure_attributes);
	ClassDB::bind_method(D_METHOD("get_attribute", "attribute_name"), &AttributeContainer::get_attribute);
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
	ADD_SIGNAL(MethodInfo("attribute_effect_removed", PropertyInfo(Variant::OBJECT, "attribute_effect", PROPERTY_HINT_RESOURCE_TYPE, "AttributeEffect")));
	ADD_SIGNAL(MethodInfo("attribute_value_added", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute"), PropertyInfo(Variant::FLOAT, "value_amount")));
	ADD_SIGNAL(MethodInfo("attribute_value_set", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute"), PropertyInfo(Variant::FLOAT, "value_amount")));
	ADD_SIGNAL(MethodInfo("attribute_value_subtracted", PropertyInfo(Variant::OBJECT, "attribute", PROPERTY_HINT_RESOURCE_TYPE, "Attribute"), PropertyInfo(Variant::FLOAT, "value_amount")));
}

void AttributeContainer::apply_attribute_effect(Ref<AttributeEffect> &attribute_effect, Ref<Attribute> &attribute)
{
	switch (attribute_effect->get_application_type())
	{
	case AttributeEffect::ApplicationType::ADD_BUFF:
	{
		attribute->add_buff(attribute_effect->get_affected_amount());
		emit_signal("attribute_buff_added", Ref<Attribute>(attribute), attribute_effect->get_affected_amount());
		break;
	}
	case AttributeEffect::ApplicationType::ADD_VALUE:
	{
		attribute->add_value(attribute_effect->get_affected_amount());
		emit_signal("attribute_value_added", Ref<Attribute>(attribute), attribute_effect->get_affected_amount());
		break;
	}
	case AttributeEffect::ApplicationType::ADD_VALUE_OR_BUFF:
	{
		attribute->add_value_or_buff(attribute_effect->get_affected_amount());
		emit_signal("attribute_value_added", Ref<Attribute>(attribute), attribute_effect->get_affected_amount());
		break;
	}
	case AttributeEffect::ApplicationType::SUBTRACT_BUFF:
	{
		attribute->subtract_buff(attribute_effect->get_affected_amount());
		emit_signal("attribute_buff_subtracted", Ref<Attribute>(attribute), attribute_effect->get_affected_amount());
		break;
	}
	case AttributeEffect::ApplicationType::SUBTRACT_VALUE:
	{
		attribute->subtract_value(attribute_effect->get_affected_amount());
		emit_signal("attribute_value_subtracted", Ref<Attribute>(attribute), attribute_effect->get_affected_amount());
		break;
	}
	case AttributeEffect::ApplicationType::SET_BUFF:
	{
		attribute->set_buff(attribute_effect->get_affected_amount());
		emit_signal("attribute_buff_set", Ref<Attribute>(attribute), attribute_effect->get_affected_amount());
		break;
	}
	case AttributeEffect::ApplicationType::SET_VALUE:
	{
		attribute->set_value(attribute_effect->get_affected_amount());
		emit_signal("attribute_value_set", Ref<Attribute>(attribute), attribute_effect->get_affected_amount());
		break;
	}
	}
}

int AttributeContainer::increase_attribute_effect_timer_count(int p_id)
{
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

Timer *AttributeContainer::setup_attribute_effect_timer(Ref<AttributeEffect> &attribute_effect, Ref<Attribute> &attribute)
{
	Timer *timer = memnew(Timer);

	timer->set_autostart(false);
	timer->set_one_shot(false);
	timer->set_wait_time(1.0f);

	add_child(timer);

	Callable callable = Callable(this, "_handle_timer_timeout");
	Array arguments = Array();

	arguments.append(timer);
	arguments.append(attribute_effect);
	arguments.append(attribute);

	callable.bindv(arguments);

	timer->connect("timeout", callable);

	return timer;
}

bool AttributeContainer::should_break_attribute_effect(Ref<AttributeEffect> &attribute_effect)
{
	switch (attribute_effect->get_break(this))
	{
	case AttributeEffectCondition::BreakType::BREAK:
	{
		emit_signal("attribute_effect_blocked", Ref<AttributeEffect>(attribute_effect));
		return true;
	}
	case AttributeEffectCondition::BreakType::BREAK_REMOVE_ATTRIBUTE_EFFECT:
	{
		ongoing_effects.erase(attribute_effect);
		emit_signal("attribute_effect_removed", Ref<AttributeEffect>(attribute_effect));
		return true;
	}
	case AttributeEffectCondition::BreakType::BREAK_REMOVE_ATTRIBUTE_EFFECT_OF_THIS_TYPE:
	{
		for (int x = ongoing_effects.size() - 1; x >= 0; x--)
		{
			Variant ongoing_effect_variant = ongoing_effects.operator[](x);
			AttributeEffect *ongoing_effect = cast_to<AttributeEffect>(ongoing_effect_variant);

			if (ongoing_effect != nullptr && ongoing_effect->get_class() == attribute_effect->get_class())
			{
				ongoing_effects.erase(ongoing_effect);
				emit_signal("attribute_effect_removed", Ref<AttributeEffect>(ongoing_effect));
			}
		}

		return true;
	}
	case AttributeEffectCondition::BreakType::BREAK_REMOVE_ANY_ATTRIBUTE_EFFECT:
	{
		ongoing_effects.clear();
		emit_signal("all_effects_removed");
		return true;
	}
	case AttributeEffectCondition::BreakType::NO_BREAK:
	{
		return false;
	}
	}

	return false;
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
	TypedArray<AttributeEffect> effects = p_game_effect->get_attribute_effects_applied();

	for (int i = 0; i < effects.size(); i++)
	{
		Variant effect_variant = effects[i];
		AttributeEffect *attribute_effect = cast_to<AttributeEffect>(effect_variant);

		if (attribute_effect != nullptr)
		{
			ongoing_effects.push_back(attribute_effect);
		}

		if (!has_attribute(attribute_effect->get_affected_attribute()))
		{
			continue;
		}

		Ref<Attribute> attribute_ref = get_attribute(attribute_effect->get_affected_attribute());
		Ref<AttributeEffect> attribute_effect_ref = Ref<AttributeEffect>(attribute_effect);

		if (should_break_attribute_effect(attribute_effect_ref))
		{
			continue;
		}

		if (attribute_effect_ref->get_life_cycle() == AttributeEffect::LifeCycle::ONE_TIME)
		{
			apply_attribute_effect(attribute_effect_ref, attribute_ref);
		}
		else
		{
			setup_attribute_effect_timer(attribute_effect_ref, attribute_ref)->start();
		}
	}
}

void AttributeContainer::ensure_attributes(PackedStringArray p_attributes)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		for (StringName tagname : p_attributes)
		{
			if (!has_attribute(tagname))
			{
				Attribute *attribute = memnew(Attribute);

				attribute->set_tag_name(tagname);
				attributes.push_back(attribute);
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
