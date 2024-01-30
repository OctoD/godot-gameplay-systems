#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/confirmation_dialog.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/tree.hpp>

#include "ggs_tag_main_scene.h"
#include "ggs_tag_dictionary_item.h"

#include "resource_manager/resource_manager.h"
#include "editor_plugin/main_scene/ggs_new_resource_modal.h"

#include "system/tag/tag_tree.h"
#include "system/tag/tag_dictionary.h"
#include "system/tag/tag_manager.h"

using namespace ggs;
using namespace ggs::editor_plugin;

void TagMainScene::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_handle_add_tag_dictionary_requested", "p_name"), &TagMainScene::_handle_add_tag_dictionary_requested);
	ClassDB::bind_method(D_METHOD("_handle_delete_tag", "p_dictionary", "p_tag_path"), &TagMainScene::_handle_delete_tag);
	ClassDB::bind_method(D_METHOD("_handle_remove_tag_requested", "p_dictionary", "p_tag_path"), &TagMainScene::_handle_remove_tag_requested);
	ClassDB::bind_method(D_METHOD("_handle_tag_add_requested", "p_dictionary", "p_tag_path"), &TagMainScene::_handle_tag_add_requested);
	ClassDB::bind_method(D_METHOD("_handle_tag_edit_requested", "p_dictionary", "p_tag_path"), &TagMainScene::_handle_tag_edit_requested);
	ClassDB::bind_method(D_METHOD("_handle_add_tag", "p_dictionary", "p_tag_path_input"), &TagMainScene::_handle_add_tag);
	ClassDB::bind_method(D_METHOD("_handle_edit_tag", "p_dictionary", "p_tag_path_input", "old_path"), &TagMainScene::_handle_edit_tag);
}

void TagMainScene::render_tag_dictionaries()
{
	ERR_FAIL_NULL_MSG(_dictionaries_container, "Dictionaries container is null.");

	TagManager *tag_manager = TagManager::get_singleton();

	tag_manager->load_dictionaries();

	TypedArray<TagDictionary> *dictionaries = tag_manager->dictionaries;
	TypedArray<godot::Node> children = _dictionaries_container->get_children();

	for (int i = 0; i < _dictionaries_container->get_child_count(); i++)
	{
		Node *child = _dictionaries_container->get_child(i);

		if (!child->is_queued_for_deletion())
		{
			child->queue_free();
		}
	}

	for (int i = 0; i < dictionaries->size(); i++)
	{
		TagDictionaryItem *dict_container = memnew(TagDictionaryItem);

		_dictionaries_container->add_child(dict_container);

		dict_container->connect("remove_tag_dictionary_pressed", Callable(this, "_handle_remove_tag_dictionary_pressed"));
		dict_container->connect("remove_tag_requested", Callable(this, "_handle_remove_tag_requested"));
		dict_container->connect("add_tag_requested", Callable(this, "_handle_tag_add_requested"));
		dict_container->connect("edit_tag_requested", Callable(this, "_handle_tag_edit_requested"));
		dict_container->set_tag_dictionary(cast_to<TagDictionary>(dictionaries->operator[](i)));
		dict_container->render();
	}
}

void TagMainScene::_handle_add_tag_dictionary_requested(String p_name)
{
	GGSResourceManager *resource_manager = GGSResourceManager::get_singleton();
	resource_manager->save_resource(resource_manager->create_tag_resource(p_name));

	TagManager::get_singleton()->load_dictionaries();

	render_tag_dictionaries();
}

void TagMainScene::_ready()
{
	set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);
	set_h_size_flags(Control::SIZE_EXPAND_FILL);
	set_v_size_flags(Control::SIZE_EXPAND_FILL);

	NewResourceModal *new_resource_modal = memnew(NewResourceModal);
	new_resource_modal->connect("create_requested", Callable(this, "_handle_add_tag_dictionary_requested"));

	Label *panel_title = memnew(Label);
	panel_title->set_text(tr("Tag management"));

	Button *add_tag_dictionary_button = memnew(Button);
	add_tag_dictionary_button->set_text(tr("Create a TagDictionary"));
	add_tag_dictionary_button->connect("pressed", Callable(new_resource_modal, "popup_centered"));

	HBoxContainer *header = memnew(HBoxContainer);
	header->add_child(panel_title);
	header->add_child(add_tag_dictionary_button);
	header->set_anchors_and_offsets_preset(LayoutPreset::PRESET_TOP_WIDE);

	_dictionaries_container = memnew(VBoxContainer);
	_dictionaries_container->set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);

	VBoxContainer *wrapper = memnew(VBoxContainer);
	wrapper->set_v_size_flags(Control::SIZE_EXPAND_FILL);
	wrapper->set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);
	wrapper->add_child(header);
	wrapper->add_child(_dictionaries_container);

	add_child(new_resource_modal);
	add_child(wrapper);

	render_tag_dictionaries();
}

void TagMainScene::_handle_add_tag(TagDictionary *p_dictionary, LineEdit *p_tag_path_input)
{
	String tag_path = p_tag_path_input->get_text();

	if (tag_path.is_empty())
	{
		return;
	}

	p_dictionary->add_tag(tag_path);

	GGSResourceManager::get_singleton()->save_resource(p_dictionary);

	render_tag_dictionaries();
}
void TagMainScene::_handle_edit_tag(TagDictionary *p_dictionary, LineEdit *p_tag_path_input, String old_path)
{
	String tag_path = p_tag_path_input->get_text();

	if (tag_path.is_empty())
	{
		return;
	}

	p_dictionary->replace_tag_path(old_path, tag_path);

	GGSResourceManager::get_singleton()->save_resource(p_dictionary);

	render_tag_dictionaries();
}

void TagMainScene::_handle_delete_tag(TagDictionary *p_dictionary, String p_tag_path)
{
	p_dictionary->remove_tag_path(p_tag_path);

	GGSResourceManager::get_singleton()->save_resource(p_dictionary);

	render_tag_dictionaries();
}

void TagMainScene::_handle_tag_add_requested(TagDictionary *p_dictionary, String p_tag_path)
{
	if (_confirmation_dialog != nullptr)
	{
		_confirmation_dialog->queue_free();
	}

	LineEdit *tag_path_input = memnew(LineEdit);

	tag_path_input->set_text(p_tag_path + TagDictionary::TAG_DICTIONARY_DIVIDER);

	_confirmation_dialog = memnew(ConfirmationDialog);

	add_child(_confirmation_dialog);

	_confirmation_dialog->set_title(tr("Add tag"));
	_confirmation_dialog->add_child(tag_path_input);
	_confirmation_dialog->get_ok_button()->connect("pressed", Callable(this, "_handle_add_tag").bind(p_dictionary, tag_path_input));
	_confirmation_dialog->set_cancel_button_text(tr("Cancel"));
	_confirmation_dialog->set_ok_button_text(tr("Add tag"));
	_confirmation_dialog->set_visible(true);
	_confirmation_dialog->set_unparent_when_invisible(true);

	_confirmation_dialog->popup_centered();
}

void TagMainScene::_handle_tag_edit_requested(TagDictionary *p_dictionary, String p_tag_path)
{
	if (_confirmation_dialog != nullptr)
	{
		_confirmation_dialog->queue_free();
	}

	LineEdit *tag_path_input = memnew(LineEdit);

	tag_path_input->set_text(p_tag_path);

	_confirmation_dialog = memnew(ConfirmationDialog);

	add_child(_confirmation_dialog);

	_confirmation_dialog->set_title(tr("Edit tag"));
	_confirmation_dialog->add_child(tag_path_input);
	_confirmation_dialog->get_ok_button()->connect("pressed", Callable(this, "_handle_edit_tag").bind(p_dictionary, tag_path_input, p_tag_path));
	_confirmation_dialog->set_cancel_button_text(tr("Cancel"));
	_confirmation_dialog->set_ok_button_text(tr("Edit tag"));
	_confirmation_dialog->set_visible(true);
	_confirmation_dialog->popup_centered();
	_confirmation_dialog->set_unparent_when_invisible(true);
}

void TagMainScene::_handle_remove_tag_requested(TagDictionary *p_dictionary, String p_tag_path)
{
	if (_confirmation_dialog != nullptr)
	{
		_confirmation_dialog->queue_free();
	}

	_confirmation_dialog = memnew(ConfirmationDialog);

	add_child(_confirmation_dialog);

	_confirmation_dialog->set_title(tr("Remove tag"));
	_confirmation_dialog->set_text(tr("Are you sure you want to remove the tag?"));
	_confirmation_dialog->get_ok_button()->connect("pressed", Callable(this, "_handle_delete_tag").bind(p_dictionary, p_tag_path));
	_confirmation_dialog->set_cancel_button_text(tr("No, keep this tag"));
	_confirmation_dialog->set_ok_button_text(tr("Yes, remove this tag"));
	_confirmation_dialog->set_visible(true);
	_confirmation_dialog->popup_centered();
	_confirmation_dialog->set_unparent_when_invisible(true);
}
