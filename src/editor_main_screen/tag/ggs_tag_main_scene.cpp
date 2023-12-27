#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/confirmation_dialog.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/tree.hpp>

#include "ggs_tag_main_scene.h"
#include "ggs_tag_dictionary_item.h"

#include "scene/tag/tag_tree.h"
#include "system/tag/tag_dictionary.h"
#include "system/tag/tag_manager.h"
#include "system/tag/tag_project_settings.h"

void GGSTagMainScene::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_handle_delete_tag", "p_dictionary", "p_tag_path"), &GGSTagMainScene::_handle_delete_tag);
	ClassDB::bind_method(D_METHOD("_handle_dir_selected", "p_path"), &GGSTagMainScene::_handle_dir_selected);
	ClassDB::bind_method(D_METHOD("_handle_file_selected", "p_path"), &GGSTagMainScene::_handle_file_selected);
	ClassDB::bind_method(D_METHOD("_handle_files_selected", "p_paths"), &GGSTagMainScene::_handle_files_selected);
	ClassDB::bind_method(D_METHOD("_handle_remove_tag_dictionary_pressed", "p_dictionary"), &GGSTagMainScene::_handle_remove_tag_dictionary_pressed);
	ClassDB::bind_method(D_METHOD("_handle_remove_tag_requested", "p_dictionary", "p_tag_path"), &GGSTagMainScene::_handle_remove_tag_requested);
}

void GGSTagMainScene::render_tag_dictionaries()
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
		GGSTagDictionaryItem *dict_container = memnew(GGSTagDictionaryItem);

		_dictionaries_container->add_child(dict_container);

		dict_container->connect("remove_tag_dictionary_pressed", Callable(this, "_handle_remove_tag_dictionary_pressed"));
		dict_container->connect("remove_tag_requested", Callable(this, "_handle_remove_tag_requested"));
		dict_container->set_tag_dictionary(cast_to<TagDictionary>(dictionaries->operator[](i)));
		dict_container->render();
	}
}

void GGSTagMainScene::_ready()
{
	VBoxContainer *wrapper = memnew(VBoxContainer);

	set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);

	wrapper->set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);

	EditorFileDialog *select_file_dialog = memnew(EditorFileDialog);
	select_file_dialog->add_filter("*.tres", "Load TagDictionary resource(s)");
	select_file_dialog->connect("file_selected", Callable(this, "_handle_file_selected"));
	select_file_dialog->connect("files_selected", Callable(this, "_handle_files_selected"));
	select_file_dialog->set_file_mode(EditorFileDialog::FILE_MODE_OPEN_FILES);
	select_file_dialog->set_title(tr("Select a TagDictionary"));

	add_child(select_file_dialog);

	Label *panel_title = memnew(Label);
	panel_title->set_text(tr("Tag management"));

	Button *select_file_button = memnew(Button);
	select_file_button->set_text(tr("Select a TagDictionary"));
	select_file_button->set_anchor(Side::SIDE_RIGHT, 1);
	select_file_button->connect("pressed", Callable(select_file_dialog, "popup_centered"));

	HBoxContainer *header = memnew(HBoxContainer);
	header->add_child(panel_title);
	header->add_child(select_file_button);
	header->set_anchors_and_offsets_preset(LayoutPreset::PRESET_TOP_WIDE);

	_dictionaries_container = memnew(VBoxContainer);
	_dictionaries_container->set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);

	wrapper->add_child(header);
	wrapper->add_child(_dictionaries_container);

	add_child(wrapper);

	render_tag_dictionaries();
}

void GGSTagMainScene::_handle_dir_selected(String p_path)
{
	// todo:
	//	- read dir files
	//	- select all resources files
	//	- open them
	//	- check if they are TagDictionary resources
	//	- add them
}

void GGSTagMainScene::_handle_file_selected(String p_path)
{
	TagProjectSettings::add_resource(p_path);
	render_tag_dictionaries();
}

void GGSTagMainScene::_handle_files_selected(PackedStringArray p_paths)
{
	for (int i = 0; i < p_paths.size(); i++)
	{
		TagProjectSettings::add_resource(p_paths[i]);
	}

	render_tag_dictionaries();
}

void GGSTagMainScene::_handle_delete_tag(TagDictionary *p_dictionary, String p_tag_path)
{
	p_dictionary->remove_tag_path(p_tag_path);
	p_dictionary->save();
	render_tag_dictionaries();
}

void GGSTagMainScene::_handle_remove_tag_dictionary_pressed(TagDictionary *p_dictionary)
{
	TagProjectSettings::remove_resource(p_dictionary->get_path());
	TagManager::get_singleton()->remove_dictionary(p_dictionary);
	render_tag_dictionaries();
}

void GGSTagMainScene::_handle_remove_tag_requested(TagDictionary *p_dictionary, String p_tag_path)
{
	if (_confirmation_dialog != nullptr)
	{
		_confirmation_dialog->queue_free();
	}
	
	_confirmation_dialog = memnew(ConfirmationDialog);
	_confirmation_dialog->set_title(tr("Remove tag"));
	_confirmation_dialog->set_text(tr("Are you sure you want to remove the tag?"));
	_confirmation_dialog->get_ok_button()->connect("pressed", Callable(this, "_handle_delete_tag").bind(p_dictionary, p_tag_path));
	_confirmation_dialog->set_cancel_button_text(tr("No, keep this tag"));
	_confirmation_dialog->set_ok_button_text(tr("Yes, remove this tag"));
	_confirmation_dialog->set_visible(true);
	_confirmation_dialog->popup_centered();
	_confirmation_dialog->set_unparent_when_invisible(true);
	add_child(_confirmation_dialog);
}
