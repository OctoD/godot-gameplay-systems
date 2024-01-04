#include <godot_cpp/classes/label.hpp>

#include "system/tag/tag_dictionary.h"
#include "tag_tree.h"

using namespace ggs;

const char *TagTree::TAG_PATH_META_KEY = "GGS_TAG_PATH_META_KEY";

void TagTree::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("_handle_item_edited"), &TagTree::_handle_item_edited);
	ClassDB::bind_method(D_METHOD("_handle_tag_dictionary_changed"), &TagTree::_handle_tag_dictionary_changed);
	ClassDB::bind_method(D_METHOD("get_tag_dictionary"), &TagTree::get_tag_dictionary);
	ClassDB::bind_method(D_METHOD("render"), &TagTree::render);
	ClassDB::bind_method(D_METHOD("set_tag_dictionary", "p_tag_dictionary"), &TagTree::set_tag_dictionary);

	/// binds properties
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary"), "set_tag_dictionary", "get_tag_dictionary");

	/// adds signals
	ADD_SIGNAL(MethodInfo("tags_deselected", PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags")));
	ADD_SIGNAL(MethodInfo("tags_selected", PropertyInfo(Variant::PACKED_STRING_ARRAY, "tags")));
}

void TagTree::_handle_item_edited()
{
	TreeItem *item = get_selected();

	if (item == nullptr)
	{
		return;
	}

	if (can_be_checked)
	{
		String tag_path = item->get_meta(TAG_PATH_META_KEY);

		bool checked = item->is_checked(0);

		item->set_checked(0, !checked);
		item->propagate_check(0);

		PackedStringArray tags = tag_dictionary->get_tags_from_path(item->get_meta(TAG_PATH_META_KEY));

		for (StringName tag : tags)
		{
			if (checked)
			{
				selected_tag_paths->append(tag);
			}
			else
			{
				int index = selected_tag_paths->find(tag);

				if (index != -1)
				{
					selected_tag_paths->remove_at(index);
				}
			}
		}

		item->deselect(0);

		if (checked)
		{
			emit_signal("tags_deselected", tags);
		}
		else
		{
			emit_signal("tags_selected", tags);
		}
	}
}

void TagTree::_handle_tag_dictionary_changed()
{
	clear();
	render();
}

void TagTree::render_dictionary(Dictionary p_dictionary, TreeItem *p_parent, String p_current_path)
{
	Array keys = p_dictionary.keys();

	for (int i = 0; i < keys.size(); i++)
	{
		String key = keys[i];
		TreeItem *item = create_item(p_parent);
		bool has_children = p_dictionary[key].get_type() == Variant::DICTIONARY && p_dictionary[key].operator Dictionary().size() > 0;

		if (can_be_checked)
		{
			item->set_cell_mode(0, TreeItem::CELL_MODE_CHECK);
			item->set_checked(0, false);
			item->set_checked(0, is_path_selected(p_current_path + key));
		}

		if (can_add)
		{
			item->add_button(0, get_theme_icon("Add", "EditorIcons"), ButtonIndex::ADD_TAG, false, tr("Add child tag"));
		}

		if (can_rename)
		{
			item->add_button(0, get_theme_icon("Edit", "EditorIcons"), ButtonIndex::EDIT_TAG, false, has_children ? tr("Rename tag (renames all descendants too)") : tr("Rename tag"));
		}

		if (can_delete)
		{
			item->add_button(0, get_theme_icon("Remove", "EditorIcons"), ButtonIndex::REMOVE_TAG, false, has_children ? tr("Remove tag (removes all descendants too)") : tr("Remove tag"));
		}

		item->set_tooltip_text(0, tr("Tag path: ") + p_current_path + key);
		item->set_meta(TAG_PATH_META_KEY, p_current_path + key);
		item->set_text(0, key);

		if (has_children)
		{
			render_dictionary(p_dictionary[key], item, p_current_path + key + TagDictionary::TAG_DICTIONARY_DIVIDER);
		}
	}
}

TagTree::TagTree()
{
	selected_tag_paths = memnew(PackedStringArray);
}

TagTree::~TagTree()
{
	if (selected_tag_paths != nullptr)
	{
		memfree(selected_tag_paths);
	}
}

void TagTree::_ready()
{
	set_display_folded(true);
	set_hide_root(true);
	set_v_size_flags(SIZE_EXPAND_FILL);

	connect("item_selected", Callable(this, "_handle_item_edited"));

	if (tag_dictionary != nullptr)
	{
		render();
	}
}

void TagTree::render()
{
	if (tag_dictionary == nullptr)
	{
		return;
	}

	clear();
	render_dictionary(tag_dictionary->get_tree(), create_item(), "");
}

TagDictionary *TagTree::get_tag_dictionary() const
{
	return tag_dictionary;
}

void TagTree::set_tag_dictionary(TagDictionary *p_tag_dictionary)
{
	Callable callable = Callable(this, "_handle_tag_dictionary_changed");

	if (tag_dictionary == p_tag_dictionary)
	{
		if (tag_dictionary->is_connected("changed", callable))
		{
			tag_dictionary->disconnect("changed", callable);
		}
	}

	tag_dictionary = p_tag_dictionary;
	tag_dictionary->connect("changed", callable);
}

bool TagTree::get_can_add() const
{
	return can_add;
}

bool TagTree::get_can_be_checked() const
{
	return can_be_checked;
}

bool TagTree::get_can_delete() const
{
	return can_delete;
}

bool TagTree::get_can_rename() const
{
	return can_rename;
}

bool TagTree::is_path_selected(const String p_tag_path) const
{
	if (selected_tag_paths == nullptr)
	{
		return false;
	}

	for (StringName tag_path : *selected_tag_paths)
	{
		if (tag_path.begins_with(p_tag_path))
		{
			return true;
		}
	}

	return false;
}

void TagTree::set_can_add(const bool p_can_add)
{
	can_add = p_can_add;
}

void TagTree::set_can_be_checked(const bool p_can_be_checked)
{
	can_be_checked = p_can_be_checked;
}

void TagTree::set_can_delete(const bool p_can_delete)
{
	can_delete = p_can_delete;
}

void TagTree::set_can_rename(const bool p_can_rename)
{
	can_rename = p_can_rename;
}

void TagTree::select(const String p_tag_path)
{
	if (selected_tag_paths == nullptr)
	{
		selected_tag_paths = memnew(PackedStringArray);
		selected_tag_paths->append(p_tag_path);
		return;
	}

	if (!selected_tag_paths->has(p_tag_path))
	{
		selected_tag_paths->append(p_tag_path);
		render();
	}
}

void TagTree::select_many(const PackedStringArray p_tag_paths)
{
	if (selected_tag_paths == nullptr)
	{
		selected_tag_paths = memnew(PackedStringArray);
		selected_tag_paths->append_array(p_tag_paths);
		return;
	}

	int affected = 0;

	for (int i = 0; i < p_tag_paths.size(); i++)
	{
		if (!selected_tag_paths->has(p_tag_paths[i]))
		{
			affected++;
			selected_tag_paths->append(p_tag_paths[i]);
		}
	}

	if (affected > 0)
	{
		render();
	}
}
