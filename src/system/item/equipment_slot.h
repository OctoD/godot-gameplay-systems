#ifndef GGS_EQUIPMENT_SLOT_H
#define GGS_EQUIPMENT_SLOT_H

#include <godot_cpp/classes/resource.hpp>

#include "item.h"

using namespace godot;

namespace ggs
{
	class EquipmentSlot : public Resource
	{
		GDCLASS(EquipmentSlot, Resource);

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();
		/// @brief The name of the slot.
		StringName slot_name;
		/// @brief The items' tags that the slot accepts.
		PackedStringArray accepts_items_with_tags;
		/// @brief The items' tags that the slot denies.
		PackedStringArray denies_items_with_tags;

	public:
		/// @brief Check if the slot can accept an item.
		/// @param p_item The item to check.
		/// @return True if the slot can accept the item, false otherwise.
		bool can_accept(Item *p_item) const;
		/// @brief Gets the slot name.
		/// @return The slot name.
		StringName get_slot_name() const;
		/// @brief Gets the items' tags that the slot accepts.
		/// @return The items' tags that the slot accepts.
		PackedStringArray get_accepts_items_with_tags() const;
		/// @brief Gets the items' tags that the slot denies.
		/// @return The items' tags that the slot denies.
		PackedStringArray get_denies_items_with_tags() const;
        /// @brief Adds the items' tags that the slot accepts.
        /// @param p_accepts_items_with_tags The items' tags that the slot accepts.
        void add_accepts_items_with_tags(PackedStringArray p_accepts_items_with_tags);
        /// @brief Adds the items' tags that the slot denies.
        /// @param p_denies_items_with_tags The items' tags that the slot denies.
        void add_denies_items_with_tags(PackedStringArray p_denies_items_with_tags);
        /// @brief Removes the items' tags that the slot accepts.
        /// @param p_accepts_items_with_tags
        void remove_accepts_items_with_tags(PackedStringArray p_accepts_items_with_tags);
		/// @brief Removes the items' tags that the slot denies.
		/// @param p_denies_items_with_tags The items' tags that the slot denies.
		void remove_denies_items_with_tags(PackedStringArray p_denies_items_with_tags);
        /// @brief Sets the slot name.
        /// @param p_slot_name The slot name.
        void set_slot_name(StringName p_slot_name);
		/// @brief Sets the items' tags that the slot accepts.
		/// @param p_accepts_items_with_tags The items' tags that the slot accepts.
		void set_accepts_items_with_tags(PackedStringArray p_accepts_items_with_tags);
		/// @brief Sets the items' tags that the slot denies.
		/// @param p_denies_items_with_tags The items' tags that the slot denies.
		void set_denies_items_with_tags(PackedStringArray p_denies_items_with_tags);
	};
}

#endif