#ifndef GGS_TAG_TREE_H
#define GGS_TAG_TREE_H

#include <godot_cpp/classes/tree.hpp>

using namespace godot;

class TagDictionary;

class TagTree : public Tree
{
	GDCLASS(TagTree, Tree);

public:
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

protected:
	TagDictionary *tag_dictionary;
	/// @brief Binds the methods to Godot.
	void static _bind_methods();
	/// @brief Clears and re-renders the tree when the TagDictionary resource changes.
	void _handle_tag_dictionary_changed();
	/// @brief Renders the tag tree starting from a dictionary.
	/// @param p_dictionary The dictionary to render.
	/// @param p_parent The parent tree item.
	void render_dictionary(Dictionary p_dictionary, TreeItem *p_parent);
};

#endif