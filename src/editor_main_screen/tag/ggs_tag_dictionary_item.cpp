#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/h_box_container.hpp>

#include "ggs_tag_dictionary_item.h"
#include "scene/tag/tag_tree.h"
#include "system/tag/tag_dictionary.h"

void GGSTagDictionaryItem::_bind_methods()
{
    /// binds methods
    ClassDB::bind_method(D_METHOD("_handle_add_tag_button_pressed"), &GGSTagDictionaryItem::_handle_add_tag_button_pressed);

    /// binds signals
    ADD_SIGNAL(MethodInfo("tag_added"));
    ADD_SIGNAL(MethodInfo("tag_add_error"));
    ADD_SIGNAL(MethodInfo("remove_tag_dictionary_pressed"));
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
    tag_tree->set_tag_dictionary(dictionary);
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

    dictionary->add_tag(new_tag_line_edit->get_text());
    dictionary->save();

    new_tag_line_edit->set_text("");
    tag_tree->clear();
    tag_tree->set_tag_dictionary(dictionary);
    tag_tree->render();

    emit_signal("tag_added");
}

void GGSTagDictionaryItem::_handle_remove_tag_dictionary_button_pressed()
{
    emit_signal("remove_tag_dictionary_pressed");
}
