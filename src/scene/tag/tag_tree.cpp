#include <godot_cpp/classes/label.hpp>

#include "system/tag/tag_dictionary.h"
#include "tag_tree.h"

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

void TagTree::render_dictionary(Dictionary p_dictionary, TreeItem *p_parent)
{
	Array keys = p_dictionary.keys();

	for (int i = 0; i < keys.size(); i++)
	{
		String key = keys[i];
		TreeItem *item = create_item(p_parent);

		item->set_text(0, key);

		if (p_dictionary[key].get_type() == Variant::DICTIONARY)
		{
			render_dictionary(p_dictionary[key], item);
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

	render_dictionary(tag_dictionary->get_tree(), create_item());
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
