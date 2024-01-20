#include "equipment_slot.h"

#include <godot_cpp/classes/engine.hpp>

using namespace ggs;

void EquipmentSlot::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("get_slot_name"), &EquipmentSlot::get_slot_name);
	ClassDB::bind_method(D_METHOD("get_accepts_items_with_tags"), &EquipmentSlot::get_accepts_items_with_tags);
	ClassDB::bind_method(D_METHOD("get_denies_items_with_tags"), &EquipmentSlot::get_denies_items_with_tags);
	ClassDB::bind_method(D_METHOD("set_slot_name", "slot_name"), &EquipmentSlot::set_slot_name);
	ClassDB::bind_method(D_METHOD("set_accepts_items_with_tags", "accepts_items_with_tags"), &EquipmentSlot::set_accepts_items_with_tags);
	ClassDB::bind_method(D_METHOD("set_denies_items_with_tags", "denies_items_with_tags"), &EquipmentSlot::set_denies_items_with_tags);

	/// binds properties
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "slot_name"), "set_slot_name", "get_slot_name");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "accepts_items_with_tags"), "set_accepts_items_with_tags", "get_accepts_items_with_tags");
	ADD_PROPERTY(PropertyInfo(Variant::PACKED_STRING_ARRAY, "denies_items_with_tags"), "set_denies_items_with_tags", "get_denies_items_with_tags");
}

bool EquipmentSlot::can_accept(Item *p_item) const
{
	for (StringName tag : accepts_items_with_tags)
	{
		if (!p_item->get_tags().has(tag))
		{
			return false;
		}
	}

	for (StringName tag : denies_items_with_tags)
	{
		if (p_item->get_tags().has(tag))
		{
			return false;
		}
	}
	
    return true;
}

StringName EquipmentSlot::get_slot_name() const
{
	return slot_name;
}

PackedStringArray EquipmentSlot::get_accepts_items_with_tags() const
{
	return PackedStringArray(accepts_items_with_tags);
}

PackedStringArray EquipmentSlot::get_denies_items_with_tags() const
{
	return PackedStringArray(denies_items_with_tags);
}

void EquipmentSlot::set_slot_name(StringName p_slot_name)
{
	slot_name = p_slot_name;
	
	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void EquipmentSlot::set_accepts_items_with_tags(PackedStringArray p_accepts_items_with_tags)
{
	accepts_items_with_tags = p_accepts_items_with_tags;
	
	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void EquipmentSlot::set_denies_items_with_tags(PackedStringArray p_denies_items_with_tags)
{
	denies_items_with_tags = p_denies_items_with_tags;
	
	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}
