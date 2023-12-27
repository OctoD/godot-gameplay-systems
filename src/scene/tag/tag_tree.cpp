#include <godot_cpp/classes/label.hpp>

#include "system/tag/tag_dictionary.h"
#include "tag_tree.h"

const char *TagTree::TAG_PATH_META_KEY = "GGS_TAG_PATH_META_KEY";

void TagTree::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("_handle_tag_dictionary_changed"), &TagTree::_handle_tag_dictionary_changed);
	ClassDB::bind_method(D_METHOD("get_tag_dictionary"), &TagTree::get_tag_dictionary);
	ClassDB::bind_method(D_METHOD("render"), &TagTree::render);
	ClassDB::bind_method(D_METHOD("set_tag_dictionary", "p_tag_dictionary"), &TagTree::set_tag_dictionary);

	/// binds properties
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "tag_dictionary", PROPERTY_HINT_RESOURCE_TYPE, "TagDictionary"), "set_tag_dictionary", "get_tag_dictionary");
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

		// todo: fix these icons crap, it's extremely ugly, unusable and annoying to have them broken
		if (can_add)
		{
			item->add_button(0, get_theme_icon("add"), ButtonIndex::ADD_TAG, false, tr("Add child tag"));
		}

		if (can_rename)
		{
			item->add_button(0, get_theme_icon("edit"), ButtonIndex::EDIT_TAG, false, has_children ? tr("Rename tag (renames all descendants too)") : tr("Rename tag"));
		}

		if (can_delete)
		{
			item->add_button(0, get_theme_icon("remove"), ButtonIndex::REMOVE_TAG, false, has_children ? tr("Remove tag (removes all descendants too)") : tr("Remove tag"));
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

void TagTree::_ready()
{
	set_display_folded(true);
	set_hide_root(true);

	if (tag_dictionary != nullptr)
	{
		render();
	}
}

void TagTree::render()
{
	if (tag_dictionary == nullptr)
	{
		WARN_PRINT("TagTree: Tag dictionary is null in TagTree::render(). Use set_tag_dictionary(TagDictionary *tag_dictionary) to set it.");
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

bool TagTree::get_can_delete() const
{
	return can_delete;
}

bool TagTree::get_can_rename() const
{
	return can_rename;
}

void TagTree::set_can_add(const bool p_can_add)
{
	can_add = p_can_add;
}

void TagTree::set_can_delete(const bool p_can_delete)
{
	can_delete = p_can_delete;
}

void TagTree::set_can_rename(const bool p_can_rename)
{
	can_rename = p_can_rename;
}
