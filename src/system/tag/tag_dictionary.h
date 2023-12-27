#ifndef GGS_TAG_DICTIONARY_H
#define GGS_TAG_DICTIONARY_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

/// @brief The tag dictionary resource.
class TagDictionary : public Resource
{
	GDCLASS(TagDictionary, Resource)

public:
	enum Error
	{
		OK,
		CANT_WRITE_FILE,
		CANT_CLOSE_FILE,
		FILE_CORRUPTED,
		NOT_IN_EDITOR_HINT,
		TIMEOUT,
		EMPTY_PATH_WHILE_SAVING,
		RESOURCE_UNHANDLED_ERROR_REPORT_THIS_AS_A_BUG,
	};
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
	/// @brief Removes all tags from the tag dictionary.
	void clear_tags();
	/// @brief Returns all tags as an array of packed string arrays.
	/// @return
	TypedArray<PackedStringArray> get_chunks() const;
	/// @brief Gets the tag dictionary as a tree of dictionaries.
	/// @return
	Dictionary get_tree() const;
	/// @brief Returns all tags as a packed string array.
	/// @return
	PackedStringArray get_tags() const;
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

private:
	friend class GGSTagMainScene;
	friend class GGSTagDictionaryItem;
	/// @brief Saves the tag dictionary.
	Error save();
};

VARIANT_ENUM_CAST(TagDictionary::Error);

#endif
