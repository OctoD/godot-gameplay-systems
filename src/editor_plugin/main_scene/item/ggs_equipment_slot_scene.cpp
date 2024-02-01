#include "ggs_equipment_slot_scene.h"

#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>

#include "resource_manager/resource_manager.h"
#include "system/attribute/attribute_manager.h"
#include "system/item/equipment_manager.h"
#include "system/tag/tag_manager.h"
#include "system/tag/tag_tree.h"

using namespace ggs;
using namespace ggs::editor_plugin;

void EquipmentSlotScene::_handle_slot_create_requested(String p_name)
{
    if (p_name.replace(" ", "").length() == 0)
    {
        return;
    }

    GGSResourceManager *resource_manager = GGSResourceManager::get_singleton();
    Ref<EquipmentSlot> slot = resource_manager->create_equipment_slot_resource(p_name);

    resource_manager->save_resource(slot);

    EquipmentManager::get_singleton()->add_slot(slot);

    _render_slots_tree();
}

void EquipmentSlotScene::_handle_item_edited()
{
    TreeItem *selected = slots_tree->get_edited();

    if (selected == nullptr)
    {
        return;
    }

    String slot_name = selected->get_text(0);
    Variant slot_variant = EquipmentManager::get_singleton()->slots[selected->get_index()];
    EquipmentSlot *slot = cast_to<EquipmentSlot>(slot_variant);

    if (slot)
    {
        slot->set_slot_name(slot_name);
        GGSResourceManager::get_singleton()->save_resource(slot);
    }
}

void EquipmentSlotScene::_handle_slot_item_selected()
{
    TreeItem *selected = slots_tree->get_selected();

    if (selected == nullptr)
    {
        return;
    }

    Variant slot_variant = EquipmentManager::get_singleton()->slots[selected->get_index()];
    EquipmentSlot *slot = cast_to<EquipmentSlot>(slot_variant);

    if (slot == nullptr)
    {
        return;
    }

    if (selected->is_selected(TagSelectionMode::ACCEPTED))
    {
        selected_slot_tag_selection_window->set_title(tr("Selected tags: allows items with tags"));
        selected_slot_tag_selection_tree->select_many(slot->get_accepts_items_with_tags());
        tag_selection_mode = TagSelectionMode::ACCEPTED;
    }
    else if (selected->is_selected(TagSelectionMode::DENIED))
    {
        selected_slot_tag_selection_window->set_title(tr("Selected tags: denies items with tags"));
        selected_slot_tag_selection_tree->select_many(slot->get_denies_items_with_tags());
        tag_selection_mode = TagSelectionMode::DENIED;
    }
    else
    {
        return;
    }

    selected_slot_tag_selection_tree->render();

    selected_slot_tag_selection_window->set_min_size(get_size());
    selected_slot_tag_selection_window->popup_centered();
}

void EquipmentSlotScene::_handle_slot_item_name_edited(String p_new_text)
{
    TreeItem *selected = slots_tree->get_selected();

    if (selected == nullptr)
    {
        return;
    }

    Variant slot_variant = EquipmentManager::get_singleton()->slots[selected->get_index()];
    EquipmentSlot *slot = cast_to<EquipmentSlot>(slot_variant);

    if (slot == nullptr)
    {
        return;
    }

    if (slot->get_slot_name() == p_new_text)
    {
        return;
    }

    slot->set_slot_name(p_new_text);
    selected->set_text(0, p_new_text);

    GGSResourceManager::get_singleton()->save_resource(slot);
}

void EquipmentSlotScene::_handle_tags_changed()
{
    TypedArray<TagDictionary> *dictionaries = TagManager::get_singleton()->dictionaries;

    for (int i = 0; i < dictionaries->size(); i++)
    {
        Variant dictionary_variant = dictionaries->operator[](i);
        TagDictionary *_dictionary = cast_to<TagDictionary>(dictionary_variant);

        if (_dictionary)
        {
            selected_slot_tag_dictionary->add_tags(_dictionary->get_tags());
        }
    }

    selected_slot_tag_dictionary->remove_tags(AttributeManager::get_singleton()->get_attributes());
}

void EquipmentSlotScene::_handle_tags_deselected(PackedStringArray p_tags)
{
    Variant slot_variant = EquipmentManager::get_singleton()->slots[slots_tree->get_selected()->get_index()];
    EquipmentSlot *slot = cast_to<EquipmentSlot>(slot_variant);

    if (slot)
    {
        String new_text = String("");

        if (tag_selection_mode == TagSelectionMode::ACCEPTED)
        {
            slot->remove_accepts_items_with_tags(p_tags);
            new_text = new_text.join(slot->get_accepts_items_with_tags());
        }
        else if (tag_selection_mode == TagSelectionMode::DENIED)
        {
            slot->remove_denies_items_with_tags(p_tags);
            new_text = new_text.join(slot->get_denies_items_with_tags());
        }

        slots_tree->get_selected()->set_text(tag_selection_mode, new_text);

        GGSResourceManager::get_singleton()->save_resource(slot);
    }
}

void EquipmentSlotScene::_handle_tags_selected(PackedStringArray p_tags)
{
    Variant slot_variant = EquipmentManager::get_singleton()->slots[slots_tree->get_selected()->get_index()];
    EquipmentSlot *slot = cast_to<EquipmentSlot>(slot_variant);

    if (slot)
    {
        String new_text = String("");

        if (tag_selection_mode == TagSelectionMode::ACCEPTED)
        {
            slot->add_accepts_items_with_tags(p_tags);
            new_text = new_text.join(slot->get_accepts_items_with_tags());
        }
        else if (tag_selection_mode == TagSelectionMode::DENIED)
        {
            slot->add_denies_items_with_tags(p_tags);
            new_text = new_text.join(slot->get_denies_items_with_tags());
        }

        slots_tree->get_selected()->set_text(tag_selection_mode, new_text);

        GGSResourceManager::get_singleton()->save_resource(slot);
    }
}

void EquipmentSlotScene::_handle_tag_selection_window_closed()
{
    selected_equipment_slot = nullptr;
    selected_slot_tag_selection_tree->deselect_all();
    selected_slot_tag_selection_window->hide();
}

void EquipmentSlotScene::_render_slots_tree()
{
    slots_tree->clear();

    EquipmentManager::get_singleton()->load_slots();

    TypedArray<EquipmentSlot> slots = EquipmentManager::get_singleton()->slots;

    for (int i = 0; i < slots.size(); i++)
    {
        TreeItem *slot_item = slots_tree->create_item();
        Variant slot_variant = slots[i];
        EquipmentSlot *slot = cast_to<EquipmentSlot>(slot_variant);

        slot_item->set_editable(0, true);
        slot_item->set_text(0, slot->get_slot_name());
        slot_item->set_text(1, String("").join(slot->get_accepts_items_with_tags()));
        slot_item->set_text(2, String("").join(slot->get_denies_items_with_tags()));
        slot_item->add_button(3, get_theme_icon("Remove", "EditorIcons"));
        slot_item->set_tooltip_text(0, slot->get_path());
        slot_item->set_tooltip_text(1, String("\n").join(slot->get_accepts_items_with_tags()));
        slot_item->set_tooltip_text(2, String("\n").join(slot->get_denies_items_with_tags()));
    }
}

void EquipmentSlotScene::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("_handle_item_edited"), &EquipmentSlotScene::_handle_item_edited);
    ClassDB::bind_method(D_METHOD("_handle_slot_create_requested"), &EquipmentSlotScene::_handle_slot_create_requested);
    ClassDB::bind_method(D_METHOD("_handle_slot_item_name_edited"), &EquipmentSlotScene::_handle_slot_item_name_edited);
    ClassDB::bind_method(D_METHOD("_handle_slot_item_selected"), &EquipmentSlotScene::_handle_slot_item_selected);
    ClassDB::bind_method(D_METHOD("_handle_tag_selection_window_closed"), &EquipmentSlotScene::_handle_tag_selection_window_closed);
    ClassDB::bind_method(D_METHOD("_handle_tags_changed"), &EquipmentSlotScene::_handle_tags_changed);
    ClassDB::bind_method(D_METHOD("_handle_tags_deselected", "p_tag_path"), &EquipmentSlotScene::_handle_tags_deselected);
    ClassDB::bind_method(D_METHOD("_handle_tags_selected", "p_tag_path"), &EquipmentSlotScene::_handle_tags_selected);
}

void EquipmentSlotScene::render_single_slot(EquipmentSlot *p_slot)
{
    VBoxContainer *slot_container = memnew(VBoxContainer);
    Label *accepts_items_with_tags_label = memnew(Label);
    Label *denies_items_with_tags_label = memnew(Label);
    TagTree *accepts_items_with_tags = memnew(TagTree);
    TagTree *denies_items_with_tags = memnew(TagTree);
    LineEdit *slot_name = memnew(LineEdit);

    Label *slot_name_label = memnew(Label);
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
    set_anchors_and_offsets_preset(PRESET_FULL_RECT);
    set_h_size_flags(SIZE_EXPAND_FILL);
    set_v_size_flags(SIZE_EXPAND_FILL);

    selected_slot = memnew(VBoxContainer);
    slots_tree = memnew(Tree);
    selected_slot_tag_dictionary = memnew(TagDictionary);

    new_resource_modal = memnew(NewResourceModal);
    new_resource_modal->connect("create_requested", Callable(this, "_handle_slot_create_requested"));

    add_child(new_resource_modal);

    Button *add_button = memnew(Button);
    add_button->connect("pressed", Callable(new_resource_modal, "toggle_visibility"));
    add_button->set_button_icon(get_theme_icon("Add", "EditorIcons"));
    add_button->set_text(tr("Add slot"));

    Label *name_label = memnew(Label);
    name_label->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
    name_label->set_h_size_flags(SIZE_EXPAND_FILL);
    name_label->set_text(tr("Equipment Slots"));

    HBoxContainer *header = memnew(HBoxContainer);
    header->add_child(name_label);
    header->add_child(add_button);
    header->set_anchors_and_offsets_preset(PRESET_TOP_WIDE);
    header->set_h_size_flags(SIZE_EXPAND_FILL);

    slots_tree->connect("item_selected", Callable(this, "_handle_slot_item_selected"));
    slots_tree->connect("item_edited", Callable(this, "_handle_item_edited"));
    slots_tree->set_columns(4);
    slots_tree->set_column_title(0, tr("Slot name"));
    slots_tree->set_column_title(1, tr("Accepts items with tags"));
    slots_tree->set_column_title(2, tr("Denies items with tags"));
    slots_tree->set_column_titles_visible(true);
    slots_tree->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
    slots_tree->set_h_size_flags(SIZE_EXPAND_FILL);
    slots_tree->set_v_size_flags(SIZE_EXPAND_FILL);
    slots_tree->set_column_clip_content(1, true);
    slots_tree->set_column_clip_content(2, true);

    HBoxContainer *content = memnew(HBoxContainer);
    content->add_child(selected_slot);
    content->add_child(slots_tree);
    content->set_anchors_and_offsets_preset(PRESET_BOTTOM_WIDE);
    content->set_h_size_flags(SIZE_EXPAND_FILL);
    content->set_v_size_flags(SIZE_EXPAND_FILL);

    add_child(header);
    add_child(content);
    add_child(selected_slot_tag_selection_window);

    _render_slots_tree();

    /// starts creating the modal which will be used to select the tags for the selected slot
    selected_slot_tag_selection_window = memnew(Window);

    VBoxContainer *selected_slot_tag_selection_window_content = memnew(VBoxContainer);
    selected_slot_tag_selection_window_content->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
    selected_slot_tag_selection_window_content->set_h_size_flags(SIZE_EXPAND_FILL);
    selected_slot_tag_selection_window_content->set_v_size_flags(SIZE_EXPAND_FILL);

    selected_slot_tag_selection_tree = memnew(TagTree);
    selected_slot_tag_selection_tree->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
    selected_slot_tag_selection_tree->set_can_be_checked(true);
    selected_slot_tag_selection_tree->set_column_title(0, tr("Tag"));
    selected_slot_tag_selection_tree->set_column_titles_visible(true);
    selected_slot_tag_selection_tree->set_h_size_flags(SIZE_EXPAND_FILL);
    selected_slot_tag_selection_tree->set_v_size_flags(SIZE_EXPAND_FILL);
    selected_slot_tag_selection_tree->connect("tags_deselected", Callable(this, "_handle_tags_deselected"));
    selected_slot_tag_selection_tree->connect("tags_selected", Callable(this, "_handle_tags_selected"));

    selected_slot_tag_selection_window_content->add_child(selected_slot_tag_selection_tree);

    Callable close_window_callable = Callable(this, "_handle_tag_selection_window_closed");

    Button *close_window_button = memnew(Button);
    close_window_button->set_text(tr("Close"));
    close_window_button->connect("pressed", close_window_callable);

    selected_slot_tag_selection_window_content->add_child(close_window_button);

    selected_slot_tag_selection_window->add_child(selected_slot_tag_selection_window_content);
    selected_slot_tag_selection_window->connect("close_requested", close_window_callable);
    selected_slot_tag_selection_window->hide();

    add_child(selected_slot_tag_selection_window);

    TagManager::get_singleton()->connect("dictionaries_changed", Callable(this, "_handle_tags_changed"));

    _handle_tags_changed();

    selected_slot_tag_selection_tree->set_tag_dictionary(selected_slot_tag_dictionary);
}
