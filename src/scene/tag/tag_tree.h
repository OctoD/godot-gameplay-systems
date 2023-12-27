#ifndef GGS_TAG_TREE_H
#define GGS_TAG_TREE_H

#include <godot_cpp/classes/tree.hpp>

using namespace godot;

class TagDictionary;

class TagTree : public Tree
{
	GDCLASS(TagTree, Tree);

public:
	enum ButtonIndex
	{
		ADD_TAG,
		EDIT_TAG,
		REMOVE_TAG,
	};

	static const char *TAG_PATH_META_KEY;
	/// @brief Overridden from Godot.
	void _ready() override;
	/// @brief Renders the tag tree starting from a tag dictionary.
	void render();
	/// @brief Gets the tag dictionary.
	/// @return
	TagDictionary *get_tag_dictionary() const;
	/// @brief Sets the tag dictionary.
	/// @param p_tag_dictionary
	void set_tag_dictionary(TagDictionary *p_tag_dictionary);

	/// @brief Gets whether the tree can add tags.
	/// @return
	bool get_can_add() const;
	/// @brief Gets whether the tree can delete tags.
	/// @return
	bool get_can_delete() const;
	/// @brief Gets whether the tree can rename tags.
	/// @return
	bool get_can_rename() const;
	/// @brief Sets whether the tree can add tags.
	/// @param p_can_add true if the tree can add tags, false otherwise.
	void set_can_add(const bool p_can_add);
	/// @brief Sets whether the tree can delete tags.
	/// @param p_can_delete
	void set_can_delete(const bool p_can_delete);
	/// @brief Sets whether the tree can rename tags.
	/// @param p_can_rename true if the tree can rename tags, false otherwise.
	void set_can_rename(const bool p_can_rename);

protected:
	bool can_add;
	bool can_delete;
	bool can_rename;
	TagDictionary *tag_dictionary;
	/// @brief Binds the methods to Godot.
	void static _bind_methods();
	/// @brief Clears and re-renders the tree when the TagDictionary resource changes.
	void _handle_tag_dictionary_changed();
	/// @brief Renders the tag tree starting from a dictionary.
	/// @param p_dictionary The dictionary to render.
	/// @param p_parent The parent tree item.
	void render_dictionary(Dictionary p_dictionary, TreeItem *p_parent, String p_current_path);

private:
	/// @brief Handles the button pressed.
	/// @param p_item 
	/// @param p_column 
	/// @param p_id 
	/// @param p_mouse_button_index 
	void _handle_button_pressed(TreeItem *p_item, int p_column, int p_id, int p_mouse_button_index);
};

#endif