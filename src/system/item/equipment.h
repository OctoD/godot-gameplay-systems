#ifndef GGS_EQUIPMENT_H
#define GGS_EQUIPMENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "equipment_slot.h"
#include "item.h"

using namespace godot;

namespace ggs
{
	/// @brief The equipment node.
	class Equipment : public Node
	{
		GDCLASS(Equipment, Node)

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();
		/// @brief The owner of the equipment.
		Node *equipment_owner;
		/// @brief The equipment slots.
		TypedArray<EquipmentSlot> slots;

	public:
		/// @brief Check if an item can be equipped.
		/// @param p_item The item to check.
		/// @param p_slot The slot to check.
		/// @return Whether the item can be equipped.
		bool can_equip(Ref<Item> p_item, String p_slot) const;
		/// @brief Check if an item can be unequipped.
		/// @param p_slot The slot to check.
		/// @return Whether the item can be unequipped.
		bool can_unequip(String p_slot) const;
		/// @brief Equip an item.
		/// @param p_item The item to equip.
		/// @param p_slot The slot to equip the item to.
		/// @return The previously equipped item if any.
		Item *equip(Ref<Item> p_item, String p_slot);
		/// @brief Get the equipment_owner of the equipment.
		/// @return The equipment_owner of the equipment.
		Node *get_equipment_owner() const;
		/// @brief Get the equipment slots.
		/// @return The equipment slots.
		PackedStringArray get_slots() const;
		/// @brief Check if an item is equipped.
		/// @param p_item The item to check.
		/// @return Whether the item is equipped.
		bool is_equipped(Ref<Item> p_item) const;
		/// @brief Check if a slot is occupied.
		/// @param p_slot The slot to check.
		/// @return Whether the slot is occupied.
		bool is_slot_occupied(String p_slot) const;
		/// @brief Set the equipment_owner of the equipment.
		/// @param p_equipment_owner The equipment_owner of the equipment.
		void set_equipment_owner(Node *p_equipment_owner);
		/// @brief Set the equipment slots.
		/// @param p_slots The equipment slots.
		void set_slots(PackedStringArray p_slots);
		/// @brief Unequip an item.
		/// @param p_slot The slot to unequip the item from.
		/// @return Whether the item was unequipped.
		bool unequip(String p_slot);
	};
}

#endif
