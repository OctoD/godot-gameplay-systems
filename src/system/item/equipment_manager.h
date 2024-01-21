#ifndef GGS_EQUIPMENT_MANAGER_H
#define GGS_EQUIPMENT_MANAGER_H

#include <godot_cpp/classes/node.hpp>

#include "equipment_slot.h"

using namespace godot;

namespace ggs
{
	namespace editor_plugin
	{
		class EquipmentSlotScene;
	}

	class EquipmentManager : public Node
	{
		GDCLASS(EquipmentManager, Node)

	protected:
		friend class ggs::editor_plugin::EquipmentSlotScene;

		/// @brief The singleton instance.
		static EquipmentManager *singleton;
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The slots.
		TypedArray<EquipmentSlot> slots;
		/// @brief Adds a slot.
		/// @param p_slot The slot to add.
		void add_slot(EquipmentSlot *p_slot);
		/// @brief Checks if a slot exists.
		/// @param p_slot The slot to check.
		/// @return True if the slot exists, false otherwise.
		bool has_slot_by_instance(EquipmentSlot *p_slot) const;
		/// @brief Removes a slot.
		/// @param p_slot
		void remove_slot(EquipmentSlot *p_slot);
		/// @brief Loads the slots.
		void load_slots();

	public:
		/// @brief Default constructor.
		EquipmentManager();
		/// @brief Default destructor.
		~EquipmentManager();
		/// @brief The method called when the node enters the scene tree for the first time.
		void _ready() override;
		/// @brief Check if the item can be accepted by a slot.
		/// @param p_item The item to check.
		/// @return True if the item can be accepted by a slot, false otherwise.
		bool can_accept(Item *p_item) const;
		/// @brief Check if the item can be accepted by a slot.
		/// @param p_slot_name The slot name.
		/// @return True if the slot exists, false otherwise.
		bool has_slot(StringName p_slot_name) const;
		/// @brief Gets the singleton instance.
		/// @return The singleton instance.
		static EquipmentManager *get_singleton();
		/// @brief Gets the slots.
		/// @return The slots.
		PackedStringArray get_slots() const;
	};
}

#endif
