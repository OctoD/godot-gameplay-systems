#include "ability.h"

using namespace ggs;

void Ability::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("get_ability_name"), &Ability::get_ability_name);
	ClassDB::bind_method(D_METHOD("get_cooldown"), &Ability::get_cooldown);
	ClassDB::bind_method(D_METHOD("get_tags_added_on_activation"), &Ability::get_tags_added_on_activation);
	ClassDB::bind_method(D_METHOD("get_tags_added_on_cooldown_end"), &Ability::get_tags_added_on_cooldown_end);
	ClassDB::bind_method(D_METHOD("get_tags_added_on_cooldown_start"), &Ability::get_tags_added_on_cooldown_start);
	ClassDB::bind_method(D_METHOD("get_tags_added_on_grant"), &Ability::get_tags_added_on_grant);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_activation"), &Ability::get_tags_removed_on_activation);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_block"), &Ability::get_tags_removed_on_block);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_cancel"), &Ability::get_tags_removed_on_cancel);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_cooldown_end"), &Ability::get_tags_removed_on_cooldown_end);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_cooldown_start"), &Ability::get_tags_removed_on_cooldown_start);
	ClassDB::bind_method(D_METHOD("get_tags_required_to_activate"), &Ability::get_tags_required_to_activate);
	ClassDB::bind_method(D_METHOD("get_tags_required_to_block"), &Ability::get_tags_required_to_block);
	ClassDB::bind_method(D_METHOD("get_tags_required_to_cancel"), &Ability::get_tags_required_to_cancel);
	ClassDB::bind_method(D_METHOD("get_tags_required_to_grant"), &Ability::get_tags_required_to_grant);
	ClassDB::bind_method(D_METHOD("has_cooldown"), &Ability::has_cooldown);
	ClassDB::bind_method(D_METHOD("set_ability_name", "name"), &Ability::set_ability_name);
	ClassDB::bind_method(D_METHOD("set_cooldown", "cooldown"), &Ability::set_cooldown);
	ClassDB::bind_method(D_METHOD("set_tags_added_on_activation", "tags"), &Ability::set_tags_added_on_activation);
	ClassDB::bind_method(D_METHOD("set_tags_added_on_cooldown_end", "tags"), &Ability::set_tags_added_on_cooldown_end);
	ClassDB::bind_method(D_METHOD("set_tags_added_on_cooldown_start", "tags"), &Ability::set_tags_added_on_cooldown_start);
	ClassDB::bind_method(D_METHOD("set_tags_added_on_grant", "tags"), &Ability::set_tags_added_on_grant);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_activation", "tags"), &Ability::set_tags_removed_on_activation);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_block", "tags"), &Ability::set_tags_removed_on_block);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_cancel", "tags"), &Ability::set_tags_removed_on_cancel);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_cooldown_end", "tags"), &Ability::set_tags_removed_on_cooldown_end);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_cooldown_start", "tags"), &Ability::set_tags_removed_on_cooldown_start);
	ClassDB::bind_method(D_METHOD("set_tags_required_to_activate", "tags"), &Ability::set_tags_required_to_activate);
	ClassDB::bind_method(D_METHOD("set_tags_required_to_block", "tags"), &Ability::set_tags_required_to_block);
	ClassDB::bind_method(D_METHOD("set_tags_required_to_cancel", "tags"), &Ability::set_tags_required_to_cancel);
	ClassDB::bind_method(D_METHOD("set_tags_required_to_grant", "tags"), &Ability::set_tags_required_to_grant);

	/// binds properties

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "ability_name"), "set_ability_name", "get_ability_name");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "cooldown"), "set_cooldown", "get_cooldown");
	ADD_GROUP("Tags", "tags_");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_added_on_cooldown_end"), "set_tags_added_on_cooldown_end", "get_tags_added_on_cooldown_end");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_added_on_cooldown_start"), "set_tags_added_on_cooldown_start", "get_tags_added_on_cooldown_start");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_added_on_grant"), "set_tags_added_on_grant", "get_tags_added_on_grant");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_added_on_activation"), "set_tags_added_on_activation", "get_tags_added_on_activation");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_cooldown_end"), "set_tags_removed_on_cooldown_end", "get_tags_removed_on_cooldown_end");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_cooldown_start"), "set_tags_removed_on_cooldown_start", "get_tags_removed_on_cooldown_start");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_activation"), "set_tags_removed_on_activation", "get_tags_removed_on_activation");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_block"), "set_tags_removed_on_block", "get_tags_removed_on_block");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_cancel"), "set_tags_removed_on_cancel", "get_tags_removed_on_cancel");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_required_to_activate"), "set_tags_required_to_activate", "get_tags_required_to_activate");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_required_to_block"), "set_tags_required_to_block", "get_tags_required_to_block");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_required_to_cancel"), "set_tags_required_to_cancel", "get_tags_required_to_cancel");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_required_to_grant"), "set_tags_required_to_grant", "get_tags_required_to_grant");

	/// binds signals
}

Ability::Ability()
{
}

Ability::~Ability()
{
}

bool Ability::has_cooldown() const
{
	return cooldown - 1.0f > 0.05f;
}

StringName Ability::get_ability_name() const
{
	if (ability_name.length() == 0)
	{
		return StringName("ggs.ability." + String::num(get_rid().get_id()));
	}
	
    return ability_name;
}

float Ability::get_cooldown() const
{
	return cooldown;
}

PackedStringArray Ability::get_tags_added_on_cooldown_end() const
{
	return tags_added_on_cooldown_end;
}

PackedStringArray Ability::get_tags_added_on_cooldown_start() const
{
	return tags_added_on_cooldown_start;
}

PackedStringArray Ability::get_tags_added_on_grant() const
{
	return tags_added_on_grant;
}

PackedStringArray Ability::get_tags_added_on_activation() const
{
	return tags_added_on_activation;
}

PackedStringArray Ability::get_tags_removed_on_cooldown_end() const
{
	return tags_removed_on_cooldown_end;
}

PackedStringArray Ability::get_tags_removed_on_cooldown_start() const
{
	return tags_removed_on_cooldown_start;
}

PackedStringArray Ability::get_tags_removed_on_activation() const
{
	return tags_removed_on_activation;
}

PackedStringArray Ability::get_tags_removed_on_block() const
{
	return tags_removed_on_block;
}

PackedStringArray Ability::get_tags_removed_on_cancel() const
{
	return tags_removed_on_cancel;
}

PackedStringArray Ability::get_tags_required_to_activate() const
{
	return tags_required_to_activate;
}

PackedStringArray Ability::get_tags_required_to_block() const
{
	return tags_required_to_block;
}

PackedStringArray Ability::get_tags_required_to_cancel() const
{
	return tags_required_to_cancel;
}

PackedStringArray Ability::get_tags_required_to_grant() const
{
    return tags_required_to_grant;
}

void Ability::set_ability_name(const StringName &p_name)
{
	ability_name = p_name;
}

void Ability::set_cooldown(const float p_cooldown)
{
	cooldown = p_cooldown;
}

void Ability::set_tags_added_on_cooldown_end(const PackedStringArray &p_tags)
{
	tags_added_on_cooldown_end = p_tags;
}

void Ability::set_tags_added_on_cooldown_start(const PackedStringArray &p_tags)
{
	tags_added_on_cooldown_start = p_tags;
}

void Ability::set_tags_added_on_grant(const PackedStringArray &p_tags)
{
	tags_added_on_grant = p_tags;
}

void Ability::set_tags_added_on_activation(const PackedStringArray &p_tags)
{
	tags_added_on_activation = p_tags;
}

void Ability::set_tags_removed_on_cooldown_end(const PackedStringArray &p_tags)
{
	tags_removed_on_cooldown_end = p_tags;
}

void Ability::set_tags_removed_on_cooldown_start(const PackedStringArray &p_tags)
{
	tags_removed_on_cooldown_start = p_tags;
}

void Ability::set_tags_removed_on_activation(const PackedStringArray &p_tags)
{
	tags_removed_on_activation = p_tags;
}

void Ability::set_tags_removed_on_block(const PackedStringArray &p_tags)
{
	tags_removed_on_block = p_tags;
}

void Ability::set_tags_removed_on_cancel(const PackedStringArray &p_tags)
{
	tags_removed_on_cancel = p_tags;
}

void Ability::set_tags_required_to_activate(const PackedStringArray &p_tags)
{
	tags_required_to_activate = p_tags;
}

void Ability::set_tags_required_to_block(const PackedStringArray &p_tags)
{
	tags_required_to_block = p_tags;
}

void Ability::set_tags_required_to_cancel(const PackedStringArray &p_tags)
{
	tags_required_to_cancel = p_tags;
}

void Ability::set_tags_required_to_grant(const PackedStringArray &p_tags)
{
	tags_required_to_grant = p_tags;
}
