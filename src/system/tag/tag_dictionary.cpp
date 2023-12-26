#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_saver.hpp>

#include "tag_dictionary.h"

using namespace godot;

const char *TagDictionary::TAG_DICTIONARY_DIVIDER = ".";

void TagDictionary::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("add_tag", "tag"), &TagDictionary::add_tag);
	ClassDB::bind_method(D_METHOD("clear_tags"), &TagDictionary::clear_tags);
	ClassDB::bind_method(D_METHOD("get_tags"), &TagDictionary::get_tags);
	ClassDB::bind_method(D_METHOD("has_tag_path", "tag_path"), &TagDictionary::has_tag_path);
	ClassDB::bind_method(D_METHOD("has_tag", "tag"), &TagDictionary::has_tag);
	ClassDB::bind_method(D_METHOD("remove_tag", "tag"), &TagDictionary::remove_tag);
	ClassDB::bind_method(D_METHOD("replace_tag_at_index", "index", "tag"), &TagDictionary::replace_tag_at_index);
	ClassDB::bind_method(D_METHOD("replace_tag", "old_tag", "new_tag"), &TagDictionary::replace_tag);
	ClassDB::bind_method(D_METHOD("set_tags", "tags"), &TagDictionary::set_tags);

	// signals bindings
	ClassDB::add_signal("TagDictionary", MethodInfo("tag_added", PropertyInfo(Variant::OBJECT, "tag_dictionary"), PropertyInfo(Variant::STRING, "tag")));
	ClassDB::add_signal("TagDictionary", MethodInfo("tag_already_exists", PropertyInfo(Variant::OBJECT, "tag_dictionary"), PropertyInfo(Variant::STRING, "tag")));
	ClassDB::add_signal("TagDictionary", MethodInfo("tag_removed", PropertyInfo(Variant::OBJECT, "tag_dictionary"), PropertyInfo(Variant::STRING, "tag")));
	ClassDB::add_signal("TagDictionary", MethodInfo("tag_replaced", PropertyInfo(Variant::OBJECT, "tag_dictionary"), PropertyInfo(Variant::STRING, "old_tag"), PropertyInfo(Variant::STRING, "new_tag")));
	ClassDB::add_signal("TagDictionary", MethodInfo("tags_removed"));

	// properties bindings
	ClassDB::add_property("TagDictionary", PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags"), "set_tags", "get_tags");
}

TagDictionary::TagDictionary()
{
	tags = PackedStringArray();
}

TagDictionary::TagDictionary(PackedStringArray p_tags)
{
	tags = p_tags;
}

TagDictionary::~TagDictionary()
{
}

void TagDictionary::add_tag(const StringName &tag)
{
	if (tags.has(tag))
	{
		emit_signal("tag_already_exists", this, tag);
	}
	else
	{
		tags.push_back(tag);
		emit_signal("tag_added", this, tag);
	}
}

void TagDictionary::clear_tags()
{
	tags.clear();
	emit_signal("tags_removed");
}

TypedArray<PackedStringArray> TagDictionary::get_chunks() const
{
	TypedArray<PackedStringArray> output = TypedArray<PackedStringArray>();

	for (int i = 0; i < tags.size(); i++)
	{
		output.append(tags[i].split(TAG_DICTIONARY_DIVIDER, false));
	}

	return output;
}

Dictionary TagDictionary::get_tree() const
{
	Dictionary root = Dictionary();

	for (int i = 0; i < tags.size(); i++)
	{
		PackedStringArray chunks = tags[i].split(TAG_DICTIONARY_DIVIDER, false);
		Dictionary current = root;

		for (StringName chunk : chunks)
		{
			if (current.has(chunk))
			{
				current = current[chunk];
			}
			else
			{
				Dictionary new_dict = Dictionary();
				current[chunk] = new_dict;
				current = current[chunk];
			}
		}
	}

	return root;
}

PackedStringArray TagDictionary::get_tags() const
{
	return PackedStringArray(tags);
}

bool TagDictionary::has_tag(const StringName &tag) const
{
	return tags.has(tag);
}

bool TagDictionary::has_tag_path(const StringName &tag_path) const
{
	PackedStringArray path_chunks = tag_path.split(TAG_DICTIONARY_DIVIDER);
	TypedArray<PackedStringArray> tags_chunks = get_chunks();
	int expected_count = path_chunks.size();

	for (int i = 0; i < tags_chunks.size(); i++)
	{
		PackedStringArray chunks = tags_chunks[i];
		int count = 0;

		if (chunks.size() < expected_count)
		{
			continue;
		}

		for (int j = 0; j < chunks.size(); j++)
		{
			if (chunks[j] == path_chunks[j])
			{
				count++;
			}
		}

		if (count == expected_count)
		{
			return true;
		}
	}

	return false;
}

void TagDictionary::remove_tag(const StringName &tag)
{
	if (tags.has(tag))
	{
		int index = tags.find(tag);

		if (index >= 0)
		{
			tags.remove_at(index);
			emit_signal("tag_removed", this, tag);
		}
	}
}

void TagDictionary::replace_tag_at_index(int index, const StringName &tag)
{
	if (tags.size() >= index)
	{
		StringName old_tag = tags[index];
		tags.set(index, tag);
		emit_signal("tag_replaced", this, old_tag, tag);
	}
}

void TagDictionary::replace_tag(const StringName &old_tag, const StringName &new_tag)
{
	if (tags.has(old_tag))
	{
		int index = tags.find(old_tag);

		if (index >= 0)
		{
			tags.set(index, new_tag);
			emit_signal("tag_replaced", this, old_tag, new_tag);
		}
	}
}

TagDictionary::Error TagDictionary::save()
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		if (!get_path().is_empty())
		{
			switch (ResourceSaver::get_singleton()->save(this, get_path()))
			{
			case godot::Error::OK:
				return TagDictionary::Error::OK;
			case godot::Error::FAILED:
				ERR_PRINT("Failed to save tag dictionary.");
				return TagDictionary::Error::CANT_WRITE_FILE;
			case godot::Error::ERR_UNAVAILABLE:
				ERR_PRINT("Tag dictionary saving is unavailable.");
				return TagDictionary::Error::CANT_WRITE_FILE;
			case godot::Error::ERR_FILE_UNRECOGNIZED:
				ERR_PRINT("Tag dictionary file is unrecognized.");
				return TagDictionary::Error::CANT_WRITE_FILE;
			case godot::Error::ERR_FILE_CORRUPT:
				ERR_PRINT("Tag dictionary file is corrupted.");
				return TagDictionary::Error::FILE_CORRUPTED;
			case godot::Error::ERR_TIMEOUT:
				ERR_PRINT("Tag dictionary file saving timed out.");
				return TagDictionary::Error::TIMEOUT;
			default:
				ERR_PRINT("Tag dictionary file saving failed with an unknown error. Please report.");
				return TagDictionary::Error::RESOURCE_UNHANDLED_ERROR_REPORT_THIS_AS_A_BUG;
			}
		}
		else
		{
			ERR_PRINT("Tag dictionary file path is empty.");
			return TagDictionary::Error::EMPTY_PATH_WHILE_SAVING;
		}
	}

	return TagDictionary::Error::NOT_IN_EDITOR_HINT;
}

void TagDictionary::set_tags(PackedStringArray p_tags)
{
	tags = p_tags;
}
