#ifndef GGS_TAG_DICTIONARY_H
#define GGS_TAG_DICTIONARY_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

namespace ggs
{
	/// @brief The tag dictionary resource.
	class TagDictionary : public Resource
	{
		GDCLASS(TagDictionary, Resource)

	public:
		/// @brief The tag dictionary divider.
		static const char *TAG_DICTIONARY_DIVIDER;
		/// @brief Default constructor.
		TagDictionary();
		/// @brief Constructor.
		/// @param p_tags The tags.
		TagDictionary(PackedStringArray p_tags);
		/// @brief Destructor.
		~TagDictionary();
		/// @brief	Adds a tag to the tag dictionary. It will not be added if it already exists.
		/// @param tag The tag to add.
		void add_tag(const StringName &tag);
		/// @brief Adds as many tags as possible to the tag dictionary.
		/// @param p_tags The tags to add.
		void add_tags(const PackedStringArray &p_tags);
		/// @brief Adds all tags from the tag dictionary.
		/// @param p_tag_dictionary The tag dictionary to add.
		void add_tags(const TagDictionary &p_tag_dictionary);
		/// @brief Removes all tags from the tag dictionary.
		void clear_tags();
		/// @brief Adds all tags from the tag dictionaries passed to this one.
		/// @param p_tag_dictionaries
		void from_many(const TypedArray<TagDictionary> p_tag_dictionaries);
		/// @brief Returns all tags as an array of packed string arrays.
		/// @return
		TypedArray<PackedStringArray> get_chunks() const;
		/// @brief Gets the tag dictionary as a tree of dictionaries.
		/// @return
		Dictionary get_tree() const;
		/// @brief Returns all tags as a packed string array.
		/// @return
		PackedStringArray get_tags() const;
		/// @brief Returns all tags which include the tag path.
		/// @param p_tag_path The tag path to get.
		/// @return
		PackedStringArray get_tags_from_path(const StringName &p_tag_path) const;
		/// @brief Checks if the tag dictionary has all the tags.
		/// @param tags The tags to check.
		/// @return True if the tag dictionary has all the tags, false otherwise.
		bool has_all(const PackedStringArray p_tags) const;
		/// @brief Checks if the tag dictionary has any of the tags.
		/// @param p_tags The tags to check.
		/// @return True if the tag dictionary has any of the tags, false otherwise.
		bool has_some(const PackedStringArray p_tags) const;
		/// @brief Returns `true` if the tag dictionary has the tag.
		/// @param tag The tag to check.
		/// @return `true` if the tag dictionary has the tag.
		bool has_tag(const StringName &tag) const;
		/// @brief Returns `true` if the tag dictionary has the tag path.
		/// @example "tag1.tag2" is a tag path and "tag1.tag2.tag3" includes "tag1.tag2".
		/// @param tag_path The tag path to check.
		/// @return `true` if the tag dictionary has the tag path.
		bool has_tag_path(const StringName &tag_path) const;
		/// @brief	Removes a tag from the tag dictionary.
		/// @param tag	The tag to remove.
		void remove_tag(const StringName &tag);
		/// @brief Removes as many tags as possible from the tag dictionary.
		/// @param p_tags The tags to remove.
		void remove_tags(const PackedStringArray &p_tags);
		/// @brief	Removes all tags which include the tag path.
		/// @param tag_path	The tag path to remove.
		void remove_tag_path(const StringName &tag_path);
		/// @brief	Replaces a tag at the index from the tag dictionary.
		/// @param index	The index of the tag to remove.
		/// @param tag 		The tag to remove.
		void replace_tag_at_index(int index, const StringName &tag);
		/// @brief	Replaces a tag with a new tag.
		void replace_tag(const StringName &old_tag, const StringName &new_tag);
		/// @brief Replaces a tag path with a new tag path.
		/// @param old_path The old tag path.
		/// @param new_path The new tag path.
		void replace_tag_path(const StringName &old_path, const StringName &new_path);
		/// @brief Sets the tags.
		/// @param p_tags The tags.
		void set_tags(PackedStringArray p_tags);

	protected:
		static void _bind_methods();
		/// @brief Sets the tags.
		/// @param p_tags The tags.
		PackedStringArray tags;
	};
}

#endif
