#include "ggs_equipment_slot_scene.h"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>

#include "system/attribute/attribute_manager.h"
#include "system/item/equipment_manager.h"
#include "system/tag/tag_manager.h"
#include "system/tag/tag_tree.h"

using namespace ggs;
using namespace ggs::editor_plugin;

void EquipmentSlotScene::_handle_add_button_pressed()
{
}

void EquipmentSlotScene::_handle_slot_item_selected()
{
    TreeItem *selected = slots_tree->get_selected();

    if (selected == nullptr)
    {
        return;
    }
}

void EquipmentSlotScene::_handle_slot_item_name_edited(String p_new_text)
{
    selected_equipment_slot->set_slot_name(p_new_text);

    TreeItem *selected = slots_tree->get_selected();

    if (selected == nullptr)
    {
        return;
    }

    selected->set_text(0, p_new_text);
}

void EquipmentSlotScene::_render_slots_tree()
{
    slots_tree->clear();

    TypedArray<EquipmentSlot> slots = EquipmentManager::get_singleton()->slots;

    for (int i = 0; i < slots.size(); i++)
    {
        TreeItem *slot_item = slots_tree->create_item();
        Variant slot_variant = slots[i];
        EquipmentSlot *slot = cast_to<EquipmentSlot>(slot_variant);

        slot_item->set_text(0, slot->get_slot_name());
        slot_item->set_text(1, String("").join(slot->get_accepts_items_with_tags()));
        slot_item->set_text(2, String("").join(slot->get_denies_items_with_tags()));
    }
}

void EquipmentSlotScene::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("_handle_add_button_pressed"), &EquipmentSlotScene::_handle_add_button_pressed);
    ClassDB::bind_method(D_METHOD("_handle_slot_item_selected"), &EquipmentSlotScene::_handle_slot_item_selected);
    ClassDB::bind_method(D_METHOD("_handle_slot_item_name_edited"), &EquipmentSlotScene::_handle_slot_item_name_edited);
}

void EquipmentSlotScene::render_single_slot(EquipmentSlot *p_slot)
{
    VBoxContainer *slot_container = memnew(VBoxContainer);
    Label *slot_name_label = memnew(Label);
    Label *accepts_items_with_tags_label = memnew(Label);
    Label *denies_items_with_tags_label = memnew(Label);
    TagTree *accepts_items_with_tags = memnew(TagTree);
    TagTree *denies_items_with_tags = memnew(TagTree);
    LineEdit *slot_name = memnew(LineEdit);

    slot_name_label->set_text(tr("Slot name: "));
    accepts_items_with_tags_label->set_text(tr("Accepts items with tags: "));
    denies_items_with_tags_label->set_text(tr("Denies items with tags: "));

    slot_name->set_text(p_slot->get_slot_name());
    slot_name->connect("text_changed", Callable(this, "_handle_slot_item_name_edited"));

    slot_container->add_child(slot_name_label);
    slot_container->add_child(slot_name);
    slot_container->add_child(accepts_items_with_tags_label);
    slot_container->add_child(accepts_items_with_tags);
    slot_container->add_child(denies_items_with_tags_label);
    slot_container->add_child(denies_items_with_tags);

    for (int i = 0; i < selected_slot->get_child_count(); i++)
    {
        selected_slot->get_child(i)->queue_free();
    }

    selected_slot->add_child(slot_container);
}

void EquipmentSlotScene::_ready()
{
    HBoxContainer *header = memnew(HBoxContainer);
    HBoxContainer *content = memnew(HBoxContainer);
    Button *add_button = memnew(Button);
    Label *name_label = memnew(Label);
    selected_slot = memnew(VBoxContainer);
    slots_tree = memnew(Tree);

    add_button->connect("pressed", Callable(this, "_handle_add_button_pressed"));
    add_button->set_text(tr("Add slot"));
    name_label->set_text(tr("Equipment Slots"));

    slots_tree->connect("item_selected", Callable(this, "_handle_slot_item_selected"));
    slots_tree->set_columns(4);
    slots_tree->set_column_title(0, tr("Slot name"));
    slots_tree->set_column_title(1, tr("Accepts items with tags"));
    slots_tree->set_column_title(2, tr("Denies items with tags"));

    content->add_child(slots_tree);
    content->add_child(selected_slot);

    add_child(header);
    add_child(content);
}
