#ifndef GGS_TAG_TREE_H
#define GGS_TAG_TREE_H

#include <godot_cpp/classes/tree.hpp>

using namespace godot;

namespace ggs
{
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

		TagTree();
		~TagTree();

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
		/// @brief Gets whether the tree can be checked.
		/// @return
		bool get_can_be_checked() const;
		/// @brief Gets whether the tree can delete tags.
		/// @return
		bool get_can_delete() const;
		/// @brief Gets whether the tree can rename tags.
		/// @return
		bool get_can_rename() const;
		/// @brief Returns whether a tag path is selected.
		/// @param p_tag_path The tag path.
		/// @return
		bool is_path_selected(const String p_tag_path) const;
		/// @brief Sets whether the tree can add tags.
		/// @param p_can_add true if the tree can add tags, false otherwise.
		void set_can_add(const bool p_can_add);
		/// @brief Sets whether the tree can be checked.
		/// @param p_can_be_checked true if the tree can be checked, false otherwise.
		void set_can_be_checked(const bool p_can_be_checked);
		/// @brief Sets whether the tree can delete tags.
		/// @param p_can_delete
		void set_can_delete(const bool p_can_delete);
		/// @brief Sets whether the tree can rename tags.
		/// @param p_can_rename true if the tree can rename tags, false otherwise.
		void set_can_rename(const bool p_can_rename);
		/// @brief Sets whether a tag is selected.
		/// @param p_tag_path The tag path.
		void select(const String p_tag_path);
		/// @brief Sets whether many tags are selected.
		/// @param p_tag_paths The tag paths.
		void select_many(const PackedStringArray p_tag_paths);

	protected:
		/// @brief Whether the tree can add tags.
		bool can_add;
		/// @brief Whether the tree can be checked.
		bool can_be_checked;
		/// @brief Whether the tree can delete tags.
		bool can_delete;
		/// @brief Whether the tree can rename tags.
		bool can_rename;
		/// @brief The selected tag paths.
		PackedStringArray *selected_tag_paths;
		/// @brief The tag dictionary.
		TagDictionary *tag_dictionary;
		/// @brief Binds the methods to Godot.
		void static _bind_methods();
		/// @brief Handles the item_edited signal.
		void _handle_item_edited();
		/// @brief Renders the tag tree starting from a dictionary.
		/// @param p_dictionary The dictionary to render.
		/// @param p_parent The parent tree item.
		void render_dictionary(Dictionary p_dictionary, TreeItem *p_parent, String p_current_path);
	};
}

#endif