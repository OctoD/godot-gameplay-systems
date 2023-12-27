#ifndef GGS_TAG_MAIN_SCENE_H
#define GGS_TAG_MAIN_SCENE_H

#include <godot_cpp/classes/confirmation_dialog.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/editor_file_dialog.hpp>
#include <godot_cpp/classes/tree.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

using namespace godot;

class TagDictionary;

class GGSTagMainScene : public Control
{
	GDCLASS(GGSTagMainScene, Control);

public:
	void _ready() override;

protected:
	static void _bind_methods();
	/// @brief Renders the tag dictionaries.
	void render_tag_dictionaries();

private:
	VBoxContainer *_dictionaries_container;
	ConfirmationDialog *_confirmation_dialog;
	/// @brief Called when the user selects a directory.
	/// @param p_path
	void _handle_dir_selected(String p_path);
	/// @brief Called when the user selects a file.
	/// @param p_path
	void _handle_file_selected(String p_path);
	/// @brief Called when the user selects multiple files.
	/// @param p_paths
	void _handle_files_selected(PackedStringArray p_paths);
	/// @brief Called when the user presses the add tag dictionary button.
	void _handle_delete_tag(TagDictionary *p_dictionary, String p_tag_path);
	/// @brief Called when the user presses the remove tag dictionary button.
	/// @param p_dictionary
	void _handle_remove_tag_dictionary_pressed(TagDictionary *p_dictionary);
	/// @brief Called when the user presses the remove tag button.
	/// @param p_dictionary
	/// @param p_tag_path
	void _handle_remove_tag_requested(TagDictionary *p_dictionary, String p_tag_path);
};

#endif