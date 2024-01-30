#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/h_box_container.hpp>

#include "ggs_tag_dictionary_item.h"

#include "resource_manager/resource_manager.h"

#include "system/tag/tag_tree.h"
#include "system/tag/tag_dictionary.h"

using namespace ggs;
using namespace ggs::editor_plugin;

void TagDictionaryItem::_bind_methods()
{
    /// binds methods
    ClassDB::bind_method(D_METHOD("_handle_add_tag_button_pressed"), &TagDictionaryItem::_handle_add_tag_button_pressed);
    ClassDB::bind_method(D_METHOD("_handle_toggle_button_pressed"), &TagDictionaryItem::_handle_toggle_button_pressed);
    ClassDB::bind_method(D_METHOD("_handle_tree_button_pressed", "p_item", "p_column", "p_id", "p_mouse_button_index"), &TagDictionaryItem::_handle_tree_button_pressed);

    /// binds signals
    ADD_SIGNAL(MethodInfo("add_tag_requested", PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary"), PropertyInfo(Variant::STRING, "tag")));
    ADD_SIGNAL(MethodInfo("edit_tag_requested", PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary"), PropertyInfo(Variant::STRING, "tag")));
    ADD_SIGNAL(MethodInfo("remove_tag_dictionary_pressed", PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary")));
    ADD_SIGNAL(MethodInfo("remove_tag_requested", PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary")));
    ADD_SIGNAL(MethodInfo("tag_add_error"));
    ADD_SIGNAL(MethodInfo("tag_added", PropertyInfo(Variant::STRING, "tag")));
}

void TagDictionaryItem::_handle_toggle_button_pressed()
{
    tag_tree->set_visible(!tag_tree->is_visible());

    if (tag_tree->is_visible())
    {
        dict_hide_tree_button->set_button_icon(get_theme_icon("ArrowUp", "EditorIcons"));
    }
    else
    {
        dict_hide_tree_button->set_button_icon(get_theme_icon("ArrowDown", "EditorIcons"));
    }
}

void TagDictionaryItem::_ready()
{
    set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);
    set_h_size_flags(Control::SIZE_EXPAND_FILL);
    set_v_size_flags(Control::SIZE_EXPAND_FILL);
}

TagDictionary *TagDictionaryItem::get_dictionary() const
{
    return dictionary;
}

void TagDictionaryItem::set_tag_dictionary(TagDictionary *p_dictionary)
{
    dictionary = p_dictionary;
}

void TagDictionaryItem::render()
{
    for (int i = 0; i < get_child_count(); i++)
    {
        Node *child = get_child(i);

        if (!child->is_queued_for_deletion())
        {
            child->queue_free();
        }
    }

    if (tag_tree != nullptr)
    {
        tag_tree->queue_free();
    }

    if (new_tag_line_edit != nullptr)
    {
        new_tag_line_edit->queue_free();
    }

    dict_hide_tree_button = memnew(Button);
    dict_hide_tree_button->connect("pressed", Callable(this, "_handle_toggle_button_pressed"));
    dict_hide_tree_button->set_button_icon(get_theme_icon("ArrowUp", "EditorIcons"));

    Label *dict_path_label = memnew(Label);
    dict_path_label->set_anchors_preset(LayoutPreset::PRESET_LEFT_WIDE);
    dict_path_label->set_h_size_flags(Control::SIZE_EXPAND_FILL);
    dict_path_label->set_mouse_filter(Control::MOUSE_FILTER_STOP);
    dict_path_label->set_text(dictionary->get_name());
    dict_path_label->set_tooltip_text(dictionary->get_path());

    new_tag_line_edit = memnew(LineEdit);
    new_tag_line_edit->set_anchors_preset(LayoutPreset::PRESET_TOP_WIDE);
    new_tag_line_edit->set_custom_minimum_size(Size2(200, 0));
    new_tag_line_edit->set_h_grow_direction(Control::GROW_DIRECTION_BEGIN);
    new_tag_line_edit->set_placeholder(tr("New tag name"));

    Button *dict_new_tag_button = memnew(Button);
    dict_new_tag_button->connect("pressed", Callable(this, "_handle_add_tag_button_pressed"));
    dict_new_tag_button->set_text(tr("Add a new tag"));

    HBoxContainer *dict_header = memnew(HBoxContainer);
    dict_header->add_child(dict_path_label);
    dict_header->add_child(new_tag_line_edit);
    dict_header->add_child(dict_new_tag_button);
    dict_header->add_child(dict_hide_tree_button);
    dict_header->set_anchors_preset(LayoutPreset::PRESET_TOP_WIDE);
    dict_header->set_h_size_flags(Control::SIZE_EXPAND_FILL);

    tag_tree = memnew(TagTree);
    tag_tree->connect("button_clicked", Callable(this, "_handle_tree_button_pressed"));
    tag_tree->set_anchors_preset(LayoutPreset::PRESET_FULL_RECT);
    tag_tree->set_can_add(true);
    tag_tree->set_can_delete(true);
    tag_tree->set_can_rename(true);
    tag_tree->set_custom_minimum_size(Vector2(0, 300));
    tag_tree->set_tag_dictionary(dictionary);
    tag_tree->set_v_scroll_enabled(false);

    add_child(dict_header);
    add_child(tag_tree);

    tag_tree->render();
}

void TagDictionaryItem::_handle_add_tag_button_pressed()
{
    String sanitized = new_tag_line_edit->get_text().strip_edges();

    if (sanitized == "")
    {
        emit_signal("tag_add_error");
        // todo: inform client ui that the tag is empty and that it cannot be added
        return;
    }

    String tag_name = new_tag_line_edit->get_text();

    dictionary->add_tag(tag_name);

    GGSResourceManager::get_singleton()->save_resource(dictionary);

    new_tag_line_edit->set_text("");
    tag_tree->clear();
    tag_tree->set_tag_dictionary(dictionary);
    tag_tree->render();

    emit_signal("tag_added", tag_name);
}

void TagDictionaryItem::_handle_tree_button_pressed(TreeItem *p_item, int p_column, int p_id, int p_mouse_button_index)
{
    String tag_path = p_item->get_meta(TagTree::TAG_PATH_META_KEY);

    if (tag_path == "")
    {
        return;
    }

    switch (p_id)
    {
    case TagTree::ButtonIndex::ADD_TAG:
    {
        emit_signal("add_tag_requested", dictionary, tag_path);
        break;
    }
    case TagTree::ButtonIndex::EDIT_TAG:
    {
        emit_signal("edit_tag_requested", dictionary, tag_path);
        break;
    }
    case TagTree::ButtonIndex::REMOVE_TAG:
    {
        emit_signal("remove_tag_requested", dictionary, tag_path);
        break;
    }
    }
}
