#include "equipment.h"
#include "equipment_slot.h"

using namespace ggs;

void Equipment::_bind_methods()
{
}

bool Equipment::can_equip(Ref<Item> p_item, String p_slot) const
{
	return false;
}

bool Equipment::can_unequip(String p_slot) const
{
	return false;
}

Item *Equipment::equip(Ref<Item> p_item, String p_slot)
{
	return nullptr;
}

Node *Equipment::get_equipment_owner() const
{
	return nullptr;
}

PackedStringArray Equipment::get_slots() const
{
	PackedStringArray slots = PackedStringArray();

	for (int i = 0; i < slots.size(); i++)
	{
		Variant slot_variant = slots[i];
		EquipmentSlot *slot = cast_to<EquipmentSlot>(slot_variant);

		slots.append(slot->get_slot_name());
	}

	return slots;
}

bool Equipment::is_equipped(Ref<Item> p_item) const
{
	return false;
}

bool Equipment::is_slot_occupied(String p_slot) const
{
	return false;
}

void Equipment::set_equipment_owner(Node *p_equipment_owner)
{
}

void Equipment::set_slots(PackedStringArray p_slots)
{
}

bool Equipment::unequip(String p_slot)
{
	return false;
}
