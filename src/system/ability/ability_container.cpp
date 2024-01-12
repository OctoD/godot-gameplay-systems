#include <godot_cpp/classes/engine.hpp>

#include "ability_container.h"
#include "system/tag/tag_manager.h"

using namespace ggs;

TypedArray<Ability> AbilityContainer::_get_abilities() const
{
	return _abilities;
}

void AbilityContainer::_set_abilities(TypedArray<Ability> p_abilities)
{
	_abilities = p_abilities;
}

void AbilityContainer::_handle_ability_enqueued(Ability *p_ability)
{
	if (p_ability != nullptr)
	{
		tags.add_tags(p_ability->get_tags_added_on_cooldown_start());
		emit_signal("ability_enqueued", Ref<Ability>(p_ability));
	}
}

void AbilityContainer::_handle_ability_dequeued(Ability *p_ability)
{
	if (p_ability != nullptr)
	{
		tags.remove_tags(p_ability->get_tags_removed_on_cooldown_end());
		emit_signal("ability_dequeued", Ref<Ability>(p_ability));
	}
}

void AbilityContainer::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("_get_abilities"), &AbilityContainer::_get_abilities);
	ClassDB::bind_method(D_METHOD("_set_abilities", "abilities"), &AbilityContainer::_set_abilities);
	ClassDB::bind_method(D_METHOD("activate_by_name", "ability_name"), &AbilityContainer::activate_by_name);
	ClassDB::bind_method(D_METHOD("activate", "ability"), &AbilityContainer::activate);
	ClassDB::bind_method(D_METHOD("add_ability", "ability"), &AbilityContainer::add_ability);
	ClassDB::bind_method(D_METHOD("block_by_name", "ability_name"), &AbilityContainer::block_by_name);
	ClassDB::bind_method(D_METHOD("block", "ability"), &AbilityContainer::block);
	ClassDB::bind_method(D_METHOD("can_activate_by_name", "ability_name"), &AbilityContainer::can_activate_by_name);
	ClassDB::bind_method(D_METHOD("can_activate", "ability"), &AbilityContainer::can_activate);
	ClassDB::bind_method(D_METHOD("can_block_by_name", "ability_name"), &AbilityContainer::can_block_by_name);
	ClassDB::bind_method(D_METHOD("can_block", "ability"), &AbilityContainer::can_block);
	ClassDB::bind_method(D_METHOD("can_cancel_by_name", "ability_name"), &AbilityContainer::can_cancel_by_name);
	ClassDB::bind_method(D_METHOD("can_cancel", "ability"), &AbilityContainer::can_cancel);
	ClassDB::bind_method(D_METHOD("can_grant", "ability"), &AbilityContainer::can_grant);
	ClassDB::bind_method(D_METHOD("cancel_by_name", "ability_name"), &AbilityContainer::cancel_by_name);
	ClassDB::bind_method(D_METHOD("cancel", "ability"), &AbilityContainer::cancel);
	ClassDB::bind_method(D_METHOD("get_abilities"), &AbilityContainer::get_abilities);
	ClassDB::bind_method(D_METHOD("get_ability_owner"), &AbilityContainer::get_ability_owner);
	ClassDB::bind_method(D_METHOD("get_ability", "ability_name"), &AbilityContainer::get_ability);
	ClassDB::bind_method(D_METHOD("grant_abilities"), &AbilityContainer::grant_abilities);
	ClassDB::bind_method(D_METHOD("grant_ability", "ability"), &AbilityContainer::grant_ability);
	ClassDB::bind_method(D_METHOD("has_ability_owner"), &AbilityContainer::has_ability_owner);
	ClassDB::bind_method(D_METHOD("has_ability", "ability"), &AbilityContainer::has_ability);
	ClassDB::bind_method(D_METHOD("set_abilities", "abilities"), &AbilityContainer::set_abilities);
	ClassDB::bind_method(D_METHOD("set_ability_owner", "ability_owner"), &AbilityContainer::set_ability_owner);
	ClassDB::bind_method(D_METHOD("revoke_by_name", "ability_name"), &AbilityContainer::revoke_by_name);
	ClassDB::bind_method(D_METHOD("revoke", "ability"), &AbilityContainer::revoke);
	ClassDB::bind_method(D_METHOD("revoke_all"), &AbilityContainer::revoke_all);

	ClassDB::bind_method(D_METHOD("_handle_ability_enqueued", "ability"), &AbilityContainer::_handle_ability_enqueued);
	ClassDB::bind_method(D_METHOD("_handle_ability_dequeued", "ability"), &AbilityContainer::_handle_ability_dequeued);

	/// binds properties
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "abilities", PROPERTY_HINT_RESOURCE_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "Ability")), "_set_abilities", "_get_abilities");

	/// binds signals
	ADD_SIGNAL(MethodInfo("ability_activated", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_activation_fail", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_added", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_block_fail", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_blocked", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_cancellation_failed", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_cancelled", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_dequeued", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_enqueued", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_granted", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
}

AbilityGrant *AbilityContainer::get_ability_grant(const StringName &p_ability_name) const
{
	for (int i = 0; i < abilities.size(); i++)
	{
		Variant variant = abilities[i];
		AbilityGrant *ability_grant = cast_to<AbilityGrant>(variant);
		Ref<Ability> ability = Ref<Ability>(ability_grant->get_ability());

		if (ability->get_ability_name() == p_ability_name)
		{
			return ability_grant;
		}
	}

	return nullptr;
}

AbilityGrant *AbilityContainer::get_ability_grant(Ability *p_ability) const
{
	if (p_ability != nullptr)
	{
		return get_ability_grant(p_ability->get_ability_name());
	}

	return nullptr;
}

void AbilityContainer::revoke_ability_grant(AbilityGrant *p_ability_grant)
{
	Ref<Ability> ability = Ref<Ability>(p_ability_grant->get_ability());

	if (ability != nullptr && ability.is_valid())
	{
		Ability *ability_ptr = ability.ptr();

		if (ability_queue->can_dequeue(ability_ptr))
		{
			ability_queue->dequeue(ability_ptr);
			emit_signal("ability_dequeued", ability);
		}

		p_ability_grant->set_grant(false);
		tags.remove_tags(ability_ptr->get_tags_added_on_activation());
		tags.remove_tags(ability_ptr->get_tags_added_on_grant());
		tags.remove_tags(ability_ptr->get_tags_added_on_cooldown_end());
		tags.remove_tags(ability_ptr->get_tags_added_on_cooldown_start());
	}
}

void AbilityContainer::setup_tag_dictionary()
{
	if (has_ability_owner())
	{
		tags.set_tags(TagManager::get_singleton()->get_tags(ability_owner));
	}
}

AbilityContainer::AbilityContainer()
{
	abilities = TypedArray<AbilityGrant>();
	ability_queue = memnew(AbilityQueue);
}

AbilityContainer::~AbilityContainer()
{
}

void AbilityContainer::_process(float delta)
{
	ability_queue->process(delta);
}

void AbilityContainer::_ready()
{
	if (!Engine::get_singleton()->is_editor_hint())
	{
		set_abilities(_abilities);
		setup_tag_dictionary();
		grant_abilities();

		ability_queue->connect("ability_enqueued", Callable(this, "_handle_ability_enqueued"));
		ability_queue->connect("ability_dequeued", Callable(this, "_handle_ability_dequeued"));
	}
}

void AbilityContainer::activate(Ability *p_ability)
{
	if (p_ability != nullptr)
	{
		activate_by_name(p_ability->get_ability_name());
	}
}

void AbilityContainer::activate_by_name(const StringName &p_ability_name)
{
	AbilityGrant *ability_grant = get_ability_grant(p_ability_name);

	if (ability_grant != nullptr)
	{
		Ref<Ability> ability = Ref<Ability>(ability_grant->get_ability());

		if (ability != nullptr && ability.is_valid() && can_activate_by_name(p_ability_name))
		{
			if (ability->has_method("activate"))
			{
				ability->call("activate", this, ability_owner);
			}

			tags.add_tags(ability->get_tags_added_on_activation());

			emit_signal("ability_activated", ability);

			tags.remove_tags(ability->get_tags_removed_on_activation());

			Ability *ability_ptr = ability.ptr();

			if (ability_queue->can_enqueue(ability_ptr))
			{
				ability_queue->enqueue(ability_ptr);
				emit_signal("ability_enqueued", ability);
			}
		}
		else
		{
			emit_signal("ability_activation_fail", ability);
		}
	}
}

void AbilityContainer::add_ability(Ability *p_ability)
{
	if (!has_ability(p_ability))
	{
		AbilityGrant ability_grant = AbilityGrant();
		ability_grant.set_ability(p_ability);
		abilities.append(ability_grant);
		emit_signal("ability_added", Ref<Ability>(p_ability));
	}
}

void AbilityContainer::block(Ability *p_ability)
{
	if (p_ability != nullptr)
	{
		block_by_name(p_ability->get_ability_name());
	}
}

void AbilityContainer::block_by_name(const StringName &p_ability_name)
{
	AbilityGrant *ability_grant = get_ability_grant(p_ability_name);

	if (ability_grant != nullptr)
	{
		Ref<Ability> ability = Ref<Ability>(ability_grant->get_ability());

		if (ability != nullptr && ability.is_valid() && can_block_by_name(p_ability_name))
		{
			if (ability->has_method("block"))
			{
				ability->call("block", this, ability_owner);
			}

			emit_signal("ability_blocked", ability);

			Ability *ability_ptr = ability.ptr();

			if (ability_queue->can_dequeue(ability_ptr))
			{
				ability_queue->dequeue(ability_ptr);
				emit_signal("ability_dequeued", ability);
			}

			tags.remove_tags(ability->get_tags_removed_on_block());
		}
		else
		{
			emit_signal("ability_block_fail", ability);
		}
	}
}

bool AbilityContainer::can_activate(Ability *p_ability) const
{
	if (p_ability != nullptr)
	{
		return can_activate_by_name(p_ability->get_ability_name());
	}

	return false;
}

bool AbilityContainer::can_activate_by_name(const StringName &p_ability_name) const
{
	AbilityGrant *ability_grant = get_ability_grant(p_ability_name);

	if (ability_grant != nullptr && has_ability_owner())
	{
		return tags.has_all(ability_grant->get_ability()->get_tags_required_to_activate());
	}

	return false;
}

bool AbilityContainer::can_block(Ability *p_ability) const
{
	if (p_ability != nullptr)
	{
		return can_block_by_name(p_ability->get_ability_name());
	}

	return false;
}

bool AbilityContainer::can_block_by_name(const StringName &p_ability_name) const
{
	AbilityGrant *ability_grant = get_ability_grant(p_ability_name);

	if (ability_grant != nullptr && has_ability_owner())
	{
		return !tags.has_some(ability_grant->get_ability()->get_tags_required_to_block());
	}

	return false;
}

bool AbilityContainer::can_cancel(Ability *p_ability) const
{
	if (p_ability != nullptr)
	{
		return can_cancel_by_name(p_ability->get_ability_name());
	}

	return false;
}

bool AbilityContainer::can_cancel_by_name(const StringName &p_ability_name) const
{
	AbilityGrant *ability_grant = get_ability_grant(p_ability_name);

	if (ability_grant != nullptr && has_ability_owner())
	{
		return !tags.has_some(ability_grant->get_ability()->get_tags_required_to_cancel());
	}

	return false;
}

bool AbilityContainer::can_grant(Ability *p_ability) const
{
	AbilityGrant *ability_grant = get_ability_grant(p_ability);

	if (ability_grant != nullptr && has_ability_owner())
	{
	}

	return false;
}

bool AbilityContainer::can_revoke(Ability *p_ability) const
{
	return has_ability(p_ability) && !ability_queue->has_enqueued_ability(p_ability);
}

void AbilityContainer::cancel(Ability *p_ability)
{
	if (p_ability != nullptr)
	{
		cancel_by_name(p_ability->get_ability_name());
	}
}

void AbilityContainer::cancel_by_name(const StringName &p_ability_name)
{
	if (can_cancel_by_name(p_ability_name))
	{
		AbilityGrant *ability_grant = get_ability_grant(p_ability_name);

		if (ability_grant != nullptr)
		{
			Ref<Ability> ability = Ref<Ability>(ability_grant->get_ability());

			if (ability != nullptr && ability.is_valid() && can_cancel_by_name(p_ability_name))
			{
				if (ability->has_method("cancel"))
				{
					ability->call("cancel", this, ability_owner);
				}

				Ability *ability_ptr = ability.ptr();

				if (ability_queue->can_dequeue(ability_ptr))
				{
					ability_queue->dequeue(ability_ptr);
					emit_signal("ability_dequeued", ability);
				}

				emit_signal("ability_cancelled", ability);

				tags.remove_tags(ability->get_tags_removed_on_cancel());
			}
			else
			{
				emit_signal("ability_cancellation_failed", ability);
			}
		}
	}
}

bool AbilityContainer::has_ability(Ability *p_ability) const
{
	return get_ability_grant(p_ability) != nullptr;
}

bool AbilityContainer::has_ability_owner() const
{
	return ability_owner != nullptr;
}

Ref<Ability> AbilityContainer::get_ability(const StringName &p_ability_name) const
{
	AbilityGrant *ability_grant = get_ability_grant(p_ability_name);

	if (ability_grant != nullptr)
	{
		return Ref<Ability>(ability_grant->get_ability());
	}

	return nullptr;
}

TypedArray<Ability> AbilityContainer::get_abilities() const
{
	TypedArray<Ability> output = TypedArray<Ability>();

	for (int i = 0; i < abilities.size(); i++)
	{
		Variant variant = abilities[i];
		AbilityGrant *ability_grant = cast_to<AbilityGrant>(variant);

		if (ability_grant != nullptr)
		{
			Ref<Ability> ability = Ref<Ability>(ability_grant->get_ability());

			if (ability != nullptr && ability.is_valid())
			{
				output.append(ability);
			}
		}
	}

	return output;
}

Node *AbilityContainer::get_ability_owner() const
{
	return ability_owner;
}

void AbilityContainer::grant_ability(Ability *p_ability)
{
	if (can_grant(p_ability))
	{
		AbilityGrant *ability_grant = get_ability_grant(p_ability);

		if (ability_grant != nullptr)
		{
			ability_grant->set_grant(true);
			emit_signal("ability_granted", Ref<Ability>(p_ability));
			tags.add_tags(ability_grant->get_ability()->get_tags_added_on_grant());
		}
	}
}

void AbilityContainer::grant_abilities()
{
	for (int i = 0; i < abilities.size(); i++)
	{
		Variant variant = abilities[i];
		AbilityGrant *ability_grant = cast_to<AbilityGrant>(variant);

		if (ability_grant != nullptr)
		{
			Ref<Ability> ability = ability_grant->get_ability();

			ability_grant->set_grant(tags.has_all(ability->get_tags_required_to_grant()));

			tags.add_tags(ability->get_tags_added_on_grant());

			if (ability_grant->get_grant())
			{
				emit_signal("ability_granted", ability);
			}
		}
	}
}

void AbilityContainer::revoke(Ability *p_ability)
{
	if (p_ability != nullptr)
	{
		revoke_by_name(p_ability->get_ability_name());
	}
}

void AbilityContainer::revoke_by_name(const StringName &p_ability_name)
{
	AbilityGrant *ability_grant = get_ability_grant(p_ability_name);

	if (ability_grant != nullptr)
	{
		revoke_ability_grant(ability_grant);
	}
}

void AbilityContainer::revoke_all()
{
	for (int i = 0; i < abilities.size(); i++)
	{
		Variant variant = abilities[i];
		AbilityGrant *ability_grant = cast_to<AbilityGrant>(variant);

		if (ability_grant != nullptr)
		{
			revoke_ability_grant(ability_grant);
		}
	}
}

void AbilityContainer::set_abilities(TypedArray<Ability> p_abilities)
{
	WARN_PRINT(vformat("Setting abilities"));
	for (int i = 0; i < p_abilities.size(); i++)
	{
		AbilityGrant ability_grant = AbilityGrant();
		Variant ability_variant = p_abilities[i];
		Ability *ability = cast_to<Ability>(ability_variant);

		ability_grant.set_ability(ability);
		abilities.append(ability_grant);

		if (can_grant(ability))
		{
			ability_grant.set_grant(true);
		}
	}
}

void AbilityContainer::set_ability_owner(Node *p_ability_owner)
{
	ability_owner = p_ability_owner;
	setup_tag_dictionary();
	grant_abilities();
}
