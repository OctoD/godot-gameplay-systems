#ifndef GGS_TAG_MANAGER_H
#define GGS_TAG_MANAGER_H

#include "tag_dictionary.h"

#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/node.hpp>

using namespace godot;

namespace ggs
{
	/// @brief The tag manager node. It is used to manage tags.
	class TagManager : public Node
	{
		GDCLASS(TagManager, Node)

		enum TagManagerFilter
		{
			ALL = 0,
			NONE = 1,
			SOME = 2,
		};

		/// @brief The tag manager instance.
		static TagManager *singleton;

	public:
		TagManager();
		~TagManager();
		/// @brief The tag manager tag group name.
		const static char *GGS_TAG_MANAGER_TAGGED_GROUP_NAME;
		const static char *GGS_TAG_MANAGER_TAGGED_NODE_META;
		/// @brief Returns the tag manager.
		/// @return The tag manager.
		static TagManager *get_singleton();
		/// @brief Adds a tag to a node.
		/// @param p_node
		/// @param p_tag
		void add_tag(Node *p_node, const String &p_tag);
		/// @brief Adds tags to a node.
		/// @param p_node
		/// @param p_tags
		void add_tags(Node *p_node, const PackedStringArray &p_tags);
		/// @brief Gets all tagged nodes.
		/// @param p_tag
		/// @return
		TypedArray<Node> get_all_tagged_nodes() const;
		/// @brief Gets the tag container of a node. Returns nullptr if the node does not contains it.
		/// @param p_node The node to get the tag container from.
		/// @return
		TypedArray<Node> get_child_tagged_nodes(const Node *p_node) const;
		/// @brief Returns the dictionaries
		/// @return The dictionaries
		TypedArray<TagDictionary> get_dictionaries() const;
		/// @brief Gets the tags associated with a node.
		/// @param p_node The node to get the tags from.
		/// @return The tags associated with the node.
		PackedStringArray get_tags(const Node *p_node) const;
		/// @brief Checks if the node has a tag.
		/// @param p_node The node to check.
		/// @param p_tag The tag to check.
		/// @return True if the node has the tag, false otherwise.
		bool has_tag(const Node *p_node, const String &p_tag) const;
		/// @brief Checks if the node has all tags provided.
		/// @param p_node the node to check.
		/// @param p_tags The tags to check.
		/// @return
		bool has_all_tags(const Node *p_node, const PackedStringArray &p_tags) const;
		/// @brief Checks if the node has any tag provided.
		/// @param p_node the node to check.
		/// @param p_tags the tags to check.
		/// @return
		bool has_any_tag(const Node *p_node, const PackedStringArray &p_tags) const;
		/// @brief Checks if the node has none tag provided.
		/// @param p_node the node to check.
		/// @param p_tags the tags to check.
		/// @return
		bool has_none_tag(const Node *p_node, const PackedStringArray &p_tags) const;
		/// @brief Checks if the node has all tags.
		/// @param p_node The node to check.
		/// @param p_tags The tags to check.
		/// @return True if the node has all tags, false otherwise.
		bool has_tags(const Node *p_node, const PackedStringArray &p_tags, TagManagerFilter p_filter) const;
		/// @brief Removes a tag from a node.
		/// @param p_node
		/// @param p_tag
		void remove_tag(Node *p_node, const String &p_tag);
		/// @brief Removes tags from a node.
		/// @param p_node
		/// @param p_tags
		void remove_tags(Node *p_node, const PackedStringArray &p_tags);
		/// @brief Loads all dictionaries.
		void load_dictionaries();
		/// @brief Called when the node enters the scene tree for the first time.
		void _ready() override;

	protected:
		/// @brief Registers all methods that can be called from Godot.
		static void _bind_methods();
		/// @brief Adds a tag dictionary.
		/// @param dictionary The tag dictionary to add.
		/// @return The size of the tag dictionary array.
		int add_dictionary(TagDictionary *p_dictionary);
		/// @brief Checks if a tag dictionary exists.
		/// @param dictionary	The tag dictionary to check.
		/// @return	True if the tag dictionary exists, false otherwise.
		bool has_dictionary(const TagDictionary *p_dictionary) const;
		/// @brief	Removes a tag dictionary.
		/// @param dictionary	The tag dictionary to remove.
		void remove_dictionary(TagDictionary *p_dictionary);
		/// @brief The tag dictionary.
		TypedArray<TagDictionary> dictionaries;

	private:
		/// @brief Binds all signals of a tag dictionary.
		/// @param p_tag_dictionary The tag dictionary.
		void _bind_dictionary_signals(TagDictionary *p_tag_dictionary);
		/// @brief Unbinds all signals of a tag dictionary.
		/// @param p_tag_dictionary The tag dictionary.
		void _unbind_dictionary_signals(TagDictionary *p_tag_dictionary);
		/// @brief Handles the tag added signal of a tag dictionary.
		/// @param p_tag_dictionary The tag dictionary.
		/// @param p_tag The tag that was added.
		void _handle_dictionary_tag_added(const TagDictionary *p_tag_dictionary, const String &p_tag);
		/// @brief Handles the tag already exists signal of a tag dictionary.
		/// @param p_tag_dictionary The tag dictionary.
		/// @param p_tag The tag that already exists.
		void _handle_dictionary_tag_already_exists(const TagDictionary *p_tag_dictionary, const String &p_tag);
		/// @brief Handles the tag removed signal of a tag dictionary.
		/// @param p_tag_dictionary The tag dictionary.
		/// @param p_tag The tag that was removed.
		void _handle_dictionary_tag_removed(const TagDictionary *p_tag_dictionary, const String &p_tag);
		/// @brief Handles the tag replaced signal of a tag dictionary.
		/// @param p_tag_dictionary The tag dictionary.
		/// @param p_old_tag The old tag.
		/// @param p_new_tag The new tag.
		void _handle_dictionary_tag_replaced(const TagDictionary *p_tag_dictionary, const String &p_old_tag, const String &p_new_tag);
	};
}

#endif
