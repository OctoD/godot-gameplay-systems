#include <godot_cpp/classes/engine.hpp>

#include "item.h"

using namespace ggs;

void ItemSettings::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("get_decrease_quantity_on_activate"), &ItemSettings::get_decrease_quantity_on_activate);
	ClassDB::bind_method(D_METHOD("get_is_stackable"), &ItemSettings::get_is_stackable);
	ClassDB::bind_method(D_METHOD("get_max_quantity"), &ItemSettings::get_max_quantity);
	ClassDB::bind_method(D_METHOD("set_decrease_quantity_on_activate", "p_decrease_quantity_on_activate"), &ItemSettings::set_decrease_quantity_on_activate);
	ClassDB::bind_method(D_METHOD("set_is_stackable", "p_is_stackable"), &ItemSettings::set_is_stackable);
	ClassDB::bind_method(D_METHOD("set_max_quantity", "p_max_quantity"), &ItemSettings::set_max_quantity);

	/// properties binding
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "decrease_quantity_on_activate"), "set_decrease_quantity_on_activate", "get_decrease_quantity_on_activate");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_stackable"), "set_is_stackable", "get_is_stackable");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_quantity"), "set_max_quantity", "get_max_quantity");
}

bool ItemSettings::get_decrease_quantity_on_activate() const
{
	return decrease_quantity_on_activate;
}

bool ItemSettings::get_is_stackable() const
{
	return is_stackable;
}

int ItemSettings::get_max_quantity() const
{
	return max_quantity;
}

void ItemSettings::set_decrease_quantity_on_activate(bool p_decrease_quantity_on_use)
{
	decrease_quantity_on_activate = p_decrease_quantity_on_use;
}

void ItemSettings::set_max_quantity(int p_max_quantity)
{
	max_quantity = p_max_quantity;
}

void ItemSettings::set_is_stackable(bool p_is_stackable)
{
	is_stackable = p_is_stackable;
}

void ItemTags::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("get_tags_added_on_activation"), &ItemTags::get_tags_added_on_activation);
	ClassDB::bind_method(D_METHOD("get_tags_added_on_add"), &ItemTags::get_tags_added_on_add);
	ClassDB::bind_method(D_METHOD("get_tags_added_on_drop"), &ItemTags::get_tags_added_on_drop);
	ClassDB::bind_method(D_METHOD("get_tags_added_on_equip"), &ItemTags::get_tags_added_on_equip);
	ClassDB::bind_method(D_METHOD("get_tags_added_on_unequip"), &ItemTags::get_tags_added_on_unequip);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_activation"), &ItemTags::get_tags_removed_on_activation);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_add"), &ItemTags::get_tags_removed_on_add);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_drop"), &ItemTags::get_tags_removed_on_drop);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_equip"), &ItemTags::get_tags_removed_on_equip);
	ClassDB::bind_method(D_METHOD("get_tags_removed_on_unequip"), &ItemTags::get_tags_removed_on_unequip);
	ClassDB::bind_method(D_METHOD("get_tags_required_to_activate"), &ItemTags::get_tags_required_to_activate);
	ClassDB::bind_method(D_METHOD("get_tags_required_to_add"), &ItemTags::get_tags_required_to_add);
	ClassDB::bind_method(D_METHOD("get_tags_required_to_equip"), &ItemTags::get_tags_required_to_equip);
	ClassDB::bind_method(D_METHOD("get_tags_required_to_remove"), &ItemTags::get_tags_required_to_remove);
	ClassDB::bind_method(D_METHOD("get_tags_required_to_unequip"), &ItemTags::get_tags_required_to_unequip);
	ClassDB::bind_method(D_METHOD("set_tags_added_on_activation", "p_tags"), &ItemTags::set_tags_added_on_activation);
	ClassDB::bind_method(D_METHOD("set_tags_added_on_add", "p_tags"), &ItemTags::set_tags_added_on_add);
	ClassDB::bind_method(D_METHOD("set_tags_added_on_drop", "p_tags"), &ItemTags::set_tags_added_on_drop);
	ClassDB::bind_method(D_METHOD("set_tags_added_on_equip", "p_tags"), &ItemTags::set_tags_added_on_equip);
	ClassDB::bind_method(D_METHOD("set_tags_added_on_unequip", "p_tags"), &ItemTags::set_tags_added_on_unequip);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_activation", "p_tags"), &ItemTags::set_tags_removed_on_activation);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_add", "p_tags"), &ItemTags::set_tags_removed_on_add);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_drop", "p_tags"), &ItemTags::set_tags_removed_on_drop);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_equip", "p_tags"), &ItemTags::set_tags_removed_on_equip);
	ClassDB::bind_method(D_METHOD("set_tags_removed_on_unequip", "p_tags"), &ItemTags::set_tags_removed_on_unequip);
	ClassDB::bind_method(D_METHOD("set_tags_required_to_activate", "p_tags"), &ItemTags::set_tags_required_to_activate);
	ClassDB::bind_method(D_METHOD("set_tags_required_to_add", "p_tags"), &ItemTags::set_tags_required_to_add);
	ClassDB::bind_method(D_METHOD("set_tags_required_to_equip", "p_tags"), &ItemTags::set_tags_required_to_equip);
	ClassDB::bind_method(D_METHOD("set_tags_required_to_remove", "p_tags"), &ItemTags::set_tags_required_to_remove);
	ClassDB::bind_method(D_METHOD("set_tags_required_to_unequip", "p_tags"), &ItemTags::set_tags_required_to_unequip);

	/// properties binding
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_added_on_activation"), "set_tags_added_on_activation", "get_tags_added_on_activation");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_added_on_add"), "set_tags_added_on_add", "get_tags_added_on_add");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_added_on_drop"), "set_tags_added_on_drop", "get_tags_added_on_drop");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_added_on_equip"), "set_tags_added_on_equip", "get_tags_added_on_equip");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_added_on_unequip"), "set_tags_added_on_unequip", "get_tags_added_on_unequip");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_activation"), "set_tags_removed_on_activation", "get_tags_removed_on_activation");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_add"), "set_tags_removed_on_add", "get_tags_removed_on_add");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_drop"), "set_tags_removed_on_drop", "get_tags_removed_on_drop");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_equip"), "set_tags_removed_on_equip", "get_tags_removed_on_equip");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_removed_on_unequip"), "set_tags_removed_on_unequip", "get_tags_removed_on_unequip");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_required_to_activate"), "set_tags_required_to_activate", "get_tags_required_to_activate");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_required_to_add"), "set_tags_required_to_add", "get_tags_required_to_add");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_required_to_equip"), "set_tags_required_to_equip", "get_tags_required_to_equip");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_required_to_remove"), "set_tags_required_to_remove", "get_tags_required_to_remove");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags_required_to_unequip"), "set_tags_required_to_unequip", "get_tags_required_to_unequip");
}

PackedStringArray ItemTags::get_tags_added_on_activation() const
{
	return tags_added_on_activation;
}

PackedStringArray ItemTags::get_tags_added_on_add() const
{
	return tags_added_on_add;
}

PackedStringArray ItemTags::get_tags_added_on_equip() const
{
	return tags_added_on_equip;
}

PackedStringArray ItemTags::get_tags_added_on_drop() const
{
	return tags_added_on_drop;
}

PackedStringArray ItemTags::get_tags_added_on_unequip() const
{
	return tags_added_on_unequip;
}

PackedStringArray ItemTags::get_tags_required_to_activate() const
{
	return tags_required_to_activate;
}

PackedStringArray ItemTags::get_tags_required_to_add() const
{
	return tags_required_to_add;
}

PackedStringArray ItemTags::get_tags_required_to_equip() const
{
	return tags_required_to_equip;
}

PackedStringArray ItemTags::get_tags_required_to_remove() const
{
	return tags_required_to_remove;
}

PackedStringArray ItemTags::get_tags_required_to_unequip() const
{
	return tags_required_to_unequip;
}

PackedStringArray ItemTags::get_tags_removed_on_activation() const
{
	return tags_removed_on_activation;
}

PackedStringArray ItemTags::get_tags_removed_on_add() const
{
	return tags_removed_on_add;
}

PackedStringArray ItemTags::get_tags_removed_on_equip() const
{
	return tags_removed_on_equip;
}

PackedStringArray ItemTags::get_tags_removed_on_drop() const
{
	return tags_removed_on_drop;
}

PackedStringArray ItemTags::get_tags_removed_on_unequip() const
{
	return tags_removed_on_unequip;
}

void ItemTags::set_tags_added_on_activation(const PackedStringArray &p_tags)
{
	tags_added_on_activation = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_added_on_add(const PackedStringArray &p_tags)
{
	tags_added_on_add = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_added_on_equip(const PackedStringArray &p_tags)
{
	tags_added_on_equip = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_added_on_drop(const PackedStringArray &p_tags)
{
	tags_added_on_drop = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_added_on_unequip(const PackedStringArray &p_tags)
{
	tags_added_on_unequip = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_required_to_activate(const PackedStringArray &p_tags)
{
	tags_required_to_activate = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_required_to_add(const PackedStringArray &p_tags)
{
	tags_required_to_add = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_required_to_equip(const PackedStringArray &p_tags)
{
	tags_required_to_equip = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_required_to_remove(const PackedStringArray &p_tags)
{
	tags_required_to_remove = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_required_to_unequip(const PackedStringArray &p_tags)
{
	tags_required_to_unequip = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_removed_on_activation(const PackedStringArray &p_tags)
{
	tags_removed_on_activation = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_removed_on_add(const PackedStringArray &p_tags)
{
	tags_removed_on_add = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_removed_on_equip(const PackedStringArray &p_tags)
{
	tags_removed_on_equip = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_removed_on_drop(const PackedStringArray &p_tags)
{
	tags_removed_on_drop = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemTags::set_tags_removed_on_unequip(const PackedStringArray &p_tags)
{
	tags_removed_on_unequip = p_tags;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void Item::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("get_item_name"), &Item::get_item_name);
	ClassDB::bind_method(D_METHOD("get_item_settings"), &Item::get_item_settings);
	ClassDB::bind_method(D_METHOD("get_tags"), &Item::get_tags);
	ClassDB::bind_method(D_METHOD("set_item_name", "p_item_name"), &Item::set_item_name);
	ClassDB::bind_method(D_METHOD("set_item_settings", "p_item_settings"), &Item::set_item_settings);
	ClassDB::bind_method(D_METHOD("set_tags", "p_tags"), &Item::set_tags);

	/// properties binding

	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "item_name"), "set_item_name", "get_item_name");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags"), "set_tags", "get_tags");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item_settings", PROPERTY_HINT_RESOURCE_TYPE, "ItemSettings"), "set_item_settings", "get_item_settings");
}

StringName Item::get_item_name() const
{
	return item_name;
}

ItemSettings *Item::get_item_settings() const
{
	return item_settings;
}

ItemTags *Item::get_item_tags() const
{
	return item_tags;
}

PackedStringArray Item::get_tags() const
{
	return tags;
}

void Item::set_item_name(StringName p_item_name)
{
	item_name = p_item_name;
}

void Item::set_item_settings(ItemSettings *p_item_settings)
{
	item_settings = p_item_settings;
}

void Item::set_item_tags(ItemTags *p_item_tags)
{
	item_tags = p_item_tags;
}

void Item::set_tags(const PackedStringArray &p_tags)
{
	tags = p_tags;
}