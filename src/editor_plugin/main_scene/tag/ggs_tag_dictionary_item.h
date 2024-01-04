#ifndef GGS_TAG_DICTIONARY_ITEM_H
#define GGS_TAG_DICTIONARY_ITEM_H

#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/tree.hpp>

namespace ggs
{
	class TagDictionary;
	class TagTree;

	using namespace godot;

	class GGSTagDictionaryItem : public VBoxContainer
	{
		GDCLASS(GGSTagDictionaryItem, VBoxContainer);

	public:
		/// @brief Called when the node enters the scene tree for the first time.
		void _ready() override;
		/// @brief Returns the tag dictionary.
		/// @return
		TagDictionary *get_dictionary() const;
		/// @brief Sets the tag dictionary.
		/// @param dictionary The tag dictionary.
		void set_tag_dictionary(TagDictionary *p_dictionary);
		/// @brief Renders the tag dictionary.
		void render();

	protected:
		/// @brief The tag dictionary.
		TagDictionary *dictionary;
		TagTree *tag_tree;
		LineEdit *new_tag_line_edit;
		/// @brief Binds the methods to Godot.
		static void _bind_methods();

	private:
		/// @brief Handles the add tag button pressed.
		void _handle_add_tag_button_pressed();
		/// @brief Handles the remove tag dictionary button pressed.
		void _handle_remove_tag_dictionary_button_pressed();
		/// @brief Handles the button pressed.
		/// @param p_item
		/// @param p_column
		/// @param p_id
		/// @param p_mouse_button_index
		void _handle_tree_button_pressed(TreeItem *p_item, int p_column, int p_id, int p_mouse_button_index);
	};
}

#endif