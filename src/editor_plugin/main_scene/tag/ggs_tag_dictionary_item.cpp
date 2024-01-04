#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/h_box_container.hpp>

#include "ggs_tag_dictionary_item.h"
#include "system/tag/tag_tree.h"
#include "system/tag/tag_dictionary.h"

using namespace ggs;

void GGSTagDictionaryItem::_bind_methods()
{
    /// binds methods
    ClassDB::bind_method(D_METHOD("_handle_add_tag_button_pressed"), &GGSTagDictionaryItem::_handle_add_tag_button_pressed);
    ClassDB::bind_method(D_METHOD("_handle_remove_tag_dictionary_button_pressed"), &GGSTagDictionaryItem::_handle_remove_tag_dictionary_button_pressed);
    ClassDB::bind_method(D_METHOD("_handle_tree_button_pressed", "p_item", "p_column", "p_id", "p_mouse_button_index"), &GGSTagDictionaryItem::_handle_tree_button_pressed);

    /// binds signals
    ADD_SIGNAL(MethodInfo("add_tag_requested", PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary"), PropertyInfo(Variant::STRING, "tag")));
    ADD_SIGNAL(MethodInfo("edit_tag_requested", PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary"), PropertyInfo(Variant::STRING, "tag")));
    ADD_SIGNAL(MethodInfo("remove_tag_dictionary_pressed", PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary")));
    ADD_SIGNAL(MethodInfo("remove_tag_requested", PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary")));
    ADD_SIGNAL(MethodInfo("tag_add_error"));
    ADD_SIGNAL(MethodInfo("tag_added", PropertyInfo(Variant::STRING, "tag")));
}

void GGSTagDictionaryItem::_ready()
{
    set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);
}

TagDictionary *GGSTagDictionaryItem::get_dictionary() const
{
    return dictionary;
}

void GGSTagDictionaryItem::set_tag_dictionary(TagDictionary *p_dictionary)
{
    dictionary = p_dictionary;
}

void GGSTagDictionaryItem::render()
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

    tag_tree = memnew(TagTree);
    tag_tree->connect("button_clicked", Callable(this, "_handle_tree_button_pressed"));
    tag_tree->set_tag_dictionary(dictionary);
    tag_tree->set_can_add(true);
    tag_tree->set_can_delete(true);
    tag_tree->set_can_rename(true);
    tag_tree->render();

    new_tag_line_edit = memnew(LineEdit);

    Button *dict_new_tag_button = memnew(Button);
    Button *remove_tag_dictionary_button = memnew(Button);
    HBoxContainer *dict_header = memnew(HBoxContainer);
    Label *dict_path_label = memnew(Label);

    dict_header->set_anchors_preset(LayoutPreset::PRESET_TOP_WIDE);
    new_tag_line_edit->set_anchors_preset(LayoutPreset::PRESET_TOP_WIDE);
    tag_tree->set_anchors_preset(LayoutPreset::PRESET_FULL_RECT);

    dict_path_label->set_anchors_preset(LayoutPreset::PRESET_LEFT_WIDE);
    dict_path_label->set_text(dictionary->get_path());

    new_tag_line_edit->set_placeholder(tr("New tag name"));

    dict_new_tag_button->connect("pressed", Callable(this, "_handle_add_tag_button_pressed"));
    dict_new_tag_button->set_text(tr("Add a new tag"));
    remove_tag_dictionary_button->connect("pressed", Callable(this, "_handle_remove_tag_dictionary_button_pressed"));
    remove_tag_dictionary_button->set_text(tr("Remove tag dictionary"));

    dict_header->add_child(dict_path_label);
    dict_header->add_child(new_tag_line_edit);
    dict_header->add_child(remove_tag_dictionary_button);
    dict_header->add_child(dict_new_tag_button);

    tag_tree->set_custom_minimum_size(Size2(0, 300));

    add_child(dict_header);
    add_child(tag_tree);
}

void GGSTagDictionaryItem::_handle_add_tag_button_pressed()
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
    dictionary->save();

    new_tag_line_edit->set_text("");
    tag_tree->clear();
    tag_tree->set_tag_dictionary(dictionary);
    tag_tree->render();

    emit_signal("tag_added", tag_name);
}

void GGSTagDictionaryItem::_handle_remove_tag_dictionary_button_pressed()
{
    emit_signal("remove_tag_dictionary_pressed", dictionary);
}

void GGSTagDictionaryItem::_handle_tree_button_pressed(TreeItem *p_item, int p_column, int p_id, int p_mouse_button_index)
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
