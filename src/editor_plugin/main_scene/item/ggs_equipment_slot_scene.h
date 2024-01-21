#ifndef GGS_EQUIPMENT_SLOT_SCENE_H
#define GGS_EQUIPMENT_SLOT_SCENE_H

#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/tree.hpp>
#include "system/item/equipment_slot.h"

using namespace godot;

namespace ggs::editor_plugin
{
    class EquipmentSlotScene : public VBoxContainer
    {
        GDCLASS(EquipmentSlotScene, VBoxContainer);

    private:
        /// @brief Handles the add button pressed event.
        void _handle_add_button_pressed();
        /// @brief Handles the slot item selected event.
        void _handle_slot_item_selected();
        /// @brief handles the slot item name edited event.
        /// @param p_new_text the new text.
        void _handle_slot_item_name_edited(String p_new_text);
        /// @brief Renders the slots tree.
        void _render_slots_tree();

    protected:
        static void _bind_methods();
        /// @brief The selected equipment slot.
        EquipmentSlot *selected_equipment_slot;
        /// @brief The selected slot.
        VBoxContainer *selected_slot;
        /// @brief The tree that contains the slots.
        Tree *slots_tree;
        /// @brief Renders a single slot.
        /// @param p_slot The slot to render.
        void render_single_slot(EquipmentSlot *p_slot);

    public:
        void _ready() override;
    };
}

#endif
