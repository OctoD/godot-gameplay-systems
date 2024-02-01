#ifndef GGS_EQUIPMENT_SLOT_SCENE_H
#define GGS_EQUIPMENT_SLOT_SCENE_H

#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/tree.hpp>
#include <godot_cpp/classes/window.hpp>

#include "editor_plugin/main_scene/ggs_new_resource_modal.h"
#include "system/item/equipment_slot.h"
#include "system/tag/tag_dictionary.h"
#include "system/tag/tag_tree.h"

using namespace godot;

namespace ggs::editor_plugin
{
    class EquipmentSlotScene : public VBoxContainer
    {
        GDCLASS(EquipmentSlotScene, VBoxContainer);

    private:
        /// @brief Handles the add button pressed event.
        void _handle_slot_create_requested(String p_name);
        /// @brief Handles the item edited event.
        void _handle_item_edited();
        /// @brief Handles the slot item selected event.
        void _handle_slot_item_selected();
        /// @brief handles the slot item name edited event.
        /// @param p_new_text the new text.
        void _handle_slot_item_name_edited(String p_new_text);
        /// @brief Handles the selection of a tag.
        /// @param p_tags The selected tags.
        void _handle_tags_deselected(PackedStringArray p_tags);
        /// @brief Handles the change of the tags.
        void _handle_tags_changed();
        /// @brief Handles the deselection of a tag.
        /// @param p_tags The selected tags.
        void _handle_tags_selected(PackedStringArray p_tags);
        /// @brief Handles the tag selection window closed event.
        void _handle_tag_selection_window_closed();
        /// @brief Renders the slots tree.
        void _render_slots_tree();

    protected:
        enum TagSelectionMode
        {
            ACCEPTED = 1,
            DENIED = 2
        };

        static void _bind_methods();
        /// @brief The new resource modal.
        NewResourceModal *new_resource_modal;
        /// @brief The selected equipment slot.
        EquipmentSlot *selected_equipment_slot;
        /// @brief The selected slot.
        VBoxContainer *selected_slot;
        /// @brief The selected slot tag dictionary.
        TagDictionary *selected_slot_tag_dictionary;
        /// @brief The tree that contains the slots.
        Tree *slots_tree;
        /// @brief The selected slot tag selection window.
        Window *selected_slot_tag_selection_window;
        /// @brief The selected slot tag selection tree.
        TagTree *selected_slot_tag_selection_tree;
        /// @brief The selected slot tag selection mode.
        TagSelectionMode tag_selection_mode;
        /// @brief Renders a single slot.
        /// @param p_slot The slot to render.
        void render_single_slot(EquipmentSlot *p_slot);

    public:
        void _ready() override;
    };
}

#endif
