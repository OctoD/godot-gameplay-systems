#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/project_settings.hpp>

#include "tag_dictionary.h"
#include "tag_manager.h"
#include "tag_project_settings.h"

using namespace godot;

TagManager *TagManager::singleton = nullptr;

const char *TagManager::GGS_TAG_MANAGER_TAGGED_GROUP_NAME = "GGS_TAG_MANAGER_TAGGED_GROUP_NAME";
const char *TagManager::GGS_TAG_MANAGER_TAGGED_NODE_META = "GGS_TAG_MANAGER_TAGGED_NODE_META";

void TagManager::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("add_tag", "tag"), &TagManager::add_tag);
	ClassDB::bind_method(D_METHOD("add_tags", "tags"), &TagManager::add_tags);
	ClassDB::bind_method(D_METHOD("get_all_tagged_nodes"), &TagManager::get_all_tagged_nodes);
	ClassDB::bind_method(D_METHOD("get_child_tagged_nodes", "node"), &TagManager::get_child_tagged_nodes);
	ClassDB::bind_method(D_METHOD("get_tags", "node"), &TagManager::get_tags);
	ClassDB::bind_method(D_METHOD("has_tag", "node", "tag"), &TagManager::has_tag);
	ClassDB::bind_method(D_METHOD("has_all_tags", "node", "tags"), &TagManager::has_all_tags);
	ClassDB::bind_method(D_METHOD("has_any_tag", "node", "tags"), &TagManager::has_any_tag);
	ClassDB::bind_method(D_METHOD("has_none_tag", "node", "tags"), &TagManager::has_none_tag);
	ClassDB::bind_method(D_METHOD("remove_tag", "node", "tag"), &TagManager::remove_tag);
	ClassDB::bind_method(D_METHOD("remove_tags", "node", "tags"), &TagManager::remove_tags);

	/// signals binding
	ClassDB::add_signal("TagManager", MethodInfo("dictionary_added", PropertyInfo(Variant::OBJECT, "tag_dictionary")));
	ClassDB::add_signal("TagManager", MethodInfo("dictionary_removed", PropertyInfo(Variant::OBJECT, "tag_dictionary")));
	ClassDB::add_signal("TagManager", MethodInfo("dictionary_tag_added", PropertyInfo(Variant::OBJECT, "tag_dictionary"), PropertyInfo(Variant::STRING, "tag")));
	ClassDB::add_signal("TagManager", MethodInfo("dictionary_tag_already_exists", PropertyInfo(Variant::OBJECT, "tag_dictionary"), PropertyInfo(Variant::STRING, "tag")));
	ClassDB::add_signal("TagManager", MethodInfo("dictionary_tag_removed", PropertyInfo(Variant::OBJECT, "tag_dictionary"), PropertyInfo(Variant::STRING, "tag")));
	ClassDB::add_signal("TagManager", MethodInfo("dictionary_tag_replaced", PropertyInfo(Variant::OBJECT, "tag_dictionary"), PropertyInfo(Variant::STRING, "old_tag"), PropertyInfo(Variant::STRING, "new_tag")));
	ClassDB::add_signal("TagManager", MethodInfo("node_tagged", PropertyInfo(Variant::OBJECT, "node")));
	ClassDB::add_signal("TagManager", MethodInfo("node_untagged", PropertyInfo(Variant::OBJECT, "node")));
	ClassDB::add_signal("TagManager", MethodInfo("tag_added_to_node", PropertyInfo(Variant::OBJECT, "node"), PropertyInfo(Variant::STRING, "tag")));
	ClassDB::add_signal("TagManager", MethodInfo("tag_removed_from_node", PropertyInfo(Variant::OBJECT, "node"), PropertyInfo(Variant::STRING, "tag")));
}

void TagManager::_bind_dictionary_signals(TagDictionary *p_tag_dictionary)
{
	if (p_tag_dictionary == nullptr)
	{
		/// let's bind all signals
		p_tag_dictionary->connect("tag_added", Callable(this, "_handle_dictionary_tag_added"));
		p_tag_dictionary->connect("tag_already_exists", Callable(this, "_handle_dictionary_tag_already_exists"));
		p_tag_dictionary->connect("tag_removed", Callable(this, "_handle_dictionary_tag_removed"));
		p_tag_dictionary->connect("tag_replaced", Callable(this, "_handle_dictionary_tag_replaced"));
	}
}

void TagManager::_unbind_dictionary_signals(TagDictionary *p_tag_dictionary)
{
	if (p_tag_dictionary != nullptr)
	{
		/// let's unbind all signals
		p_tag_dictionary->disconnect("tag_added", Callable(this, "_handle_dictionary_tag_added"));
		p_tag_dictionary->disconnect("tag_already_exists", Callable(this, "_handle_dictionary_tag_already_exists"));
		p_tag_dictionary->disconnect("tag_removed", Callable(this, "_handle_dictionary_tag_removed"));
		p_tag_dictionary->disconnect("tag_replaced", Callable(this, "_handle_dictionary_tag_replaced"));
	}
}

void TagManager::_handle_dictionary_tag_added(const TagDictionary *p_tag_dictionary, const String &p_tag)
{
	if (p_tag_dictionary != nullptr)
	{
		emit_signal("dictionary_tag_added", p_tag_dictionary, p_tag);
	}
}

void TagManager::_handle_dictionary_tag_already_exists(const TagDictionary *p_tag_dictionary, const String &p_tag)
{
	if (p_tag_dictionary != nullptr)
	{
		emit_signal("dictionary_tag_already_exists", p_tag_dictionary, p_tag);
	}
}

void TagManager::_handle_dictionary_tag_removed(const TagDictionary *p_tag_dictionary, const String &p_tag)
{
	if (p_tag_dictionary != nullptr)
	{
		TypedArray<Node> tagged_nodes = get_all_tagged_nodes();

		for (int i = 0; i < tagged_nodes.size(); i++)
		{
			Node *tagged_node = cast_to<Node>(tagged_nodes[i]);

			if (has_tag(tagged_node, p_tag))
			{
				remove_tag(tagged_node, p_tag);
			}
		}

		emit_signal("dictionary_tag_removed", p_tag_dictionary, p_tag);
	}
}

void TagManager::_handle_dictionary_tag_replaced(const TagDictionary *p_tag_dictionary, const String &p_old_tag, const String &p_new_tag)
{
	if (p_tag_dictionary != nullptr)
	{
		TypedArray<Node> tagged_nodes = get_all_tagged_nodes();

		for (int i = 0; i < tagged_nodes.size(); i++)
		{
			Node *tagged_node = cast_to<Node>(tagged_nodes[i]);

			if (has_tag(tagged_node, p_old_tag))
			{
				remove_tag(tagged_node, p_old_tag);
				add_tag(tagged_node, p_new_tag);
			}
		}

		emit_signal("dictionary_tag_replaced", p_tag_dictionary, p_old_tag, p_new_tag);
	}
}

void TagManager::_handle_settings_changed()
{
}

void TagManager::load_dictionaries()
{
	/// let's retrieve the settings' value
	PackedStringArray resource_file_paths = TagProjectSettings::get_resource_file_paths();
	/// let's get the resource loader instance
	ResourceLoader *resource_loader = ResourceLoader::get_singleton();

	if (resource_loader != nullptr)
	{
		for (int i = 0; i < resource_file_paths.size(); i++)
		{
			String resource_file_path = resource_file_paths[i];
			Ref<Resource> resource = resource_loader->load(resource_file_path);

			if (resource.is_valid())
			{
				add_dictionary(cast_to<TagDictionary>(resource.ptr()));
			}
		}
	}
}

TagManager::TagManager()
{
	if (singleton == nullptr)
	{
		dictionaries = memnew(TypedArray<TagDictionary>);
		singleton = this;
	}
	else
	{
		dictionaries = singleton->dictionaries;
	}
}

TagManager::~TagManager()
{
	if (singleton == this)
	{
		singleton = nullptr;
	}
}

TagManager *TagManager::get_singleton()
{
	if (singleton == nullptr)
	{
		singleton = memnew(TagManager);
	}

	return singleton;
}

void TagManager::add_tag(Node *p_node, const String &p_tag)
{
	if (!has_tag(p_node, p_tag) && p_node != nullptr)
	{
		PackedStringArray tags = get_tags(p_node);

		tags.push_back(p_tag);

		p_node->add_to_group(GGS_TAG_MANAGER_TAGGED_GROUP_NAME, true);
		p_node->set_meta(GGS_TAG_MANAGER_TAGGED_NODE_META, tags);

		emit_signal("tag_added_to_node", p_node, p_tag);
	}
}

void TagManager::add_tags(Node *p_node, const PackedStringArray &p_tags)
{
	if (p_node != nullptr)
	{
		PackedStringArray tags = get_tags(p_node);

		for (uint32_t i = 0; i < p_tags.size(); i++)
		{
			if (!tags.has(p_tags[i]))
			{
				tags.push_back(p_tags[i]);
			}
		}

		p_node->add_to_group(GGS_TAG_MANAGER_TAGGED_GROUP_NAME, true);
		p_node->set_meta(GGS_TAG_MANAGER_TAGGED_NODE_META, tags);
	}
}

TypedArray<Node> TagManager::get_all_tagged_nodes() const
{
	return get_tree()->get_nodes_in_group(GGS_TAG_MANAGER_TAGGED_GROUP_NAME);
}

TypedArray<Node> TagManager::get_child_tagged_nodes(const Node *p_node) const
{
	TypedArray<Node> output = TypedArray<Node>();

	if (p_node != nullptr)
	{
		TypedArray<Node> children = p_node->get_children();

		for (int i = 0; i < children.size(); i++)
		{
			Node *child = cast_to<Node>(children[i]);

			if (child->is_in_group(GGS_TAG_MANAGER_TAGGED_GROUP_NAME))
			{
				output.push_back(child);
			}
		}
	}

	return output;
}

PackedStringArray TagManager::get_tags(const Node *p_node) const
{
	if (p_node != nullptr)
	{
		return p_node->get_meta(GGS_TAG_MANAGER_TAGGED_NODE_META, PackedStringArray());
	}

	return PackedStringArray();
}

int TagManager::add_dictionary(TagDictionary *p_dictionary)
{
	if (p_dictionary != nullptr && !has_dictionary(p_dictionary))
	{
		dictionaries->append(p_dictionary);

		emit_signal("dictionary_added", p_dictionary);

		_bind_dictionary_signals(p_dictionary);

		return dictionaries->size();
	}

	return dictionaries->size();
}

bool TagManager::has_dictionary(const TagDictionary *p_dictionary) const
{
	if (p_dictionary != nullptr)
	{
		return dictionaries->has(p_dictionary);
	}

	return false;
}

bool TagManager::has_tag(const Node *p_node, const String &p_tag) const
{
	return get_tags(p_node).has(p_tag);
}

bool TagManager::has_all_tags(const Node *p_node, const PackedStringArray &p_tags) const
{
	return has_tags(p_node, p_tags, TagManagerFilter::ALL);
}

bool TagManager::has_any_tag(const Node *p_node, const PackedStringArray &p_tags) const
{
	return has_tags(p_node, p_tags, TagManagerFilter::SOME);
}

bool TagManager::has_none_tag(const Node *p_node, const PackedStringArray &p_tags) const
{
	return has_tags(p_node, p_tags, TagManagerFilter::NONE);
}

bool TagManager::has_tags(const Node *p_node, const PackedStringArray &p_tags, TagManagerFilter p_filter = TagManagerFilter::ALL) const
{
	if (p_node != nullptr)
	{
		PackedStringArray tags = get_tags(p_node);

		if (p_filter == TagManagerFilter::ALL)
		{
			for (uint32_t i = 0; i < p_tags.size(); i++)
			{
				if (!tags.has(p_tags[i]))
				{
					return false;
				}
			}

			return true;
		}
		else if (p_filter == TagManagerFilter::SOME)
		{
			for (uint32_t i = 0; i < p_tags.size(); i++)
			{
				if (tags.has(p_tags[i]))
				{
					return true;
				}
			}

			return false;
		}
		else if (p_filter == TagManagerFilter::NONE)
		{
			for (uint32_t i = 0; i < p_tags.size(); i++)
			{
				if (tags.has(p_tags[i]))
				{
					return false;
				}
			}

			return true;
		}
	}

	return false;
}

void TagManager::remove_tag(Node *p_node, const String &p_tag)
{
	if (p_node != nullptr)
	{
		PackedStringArray tags = get_tags(p_node);

		int64_t index = tags.find(p_tag);

		if (index > -1)
		{
			tags.remove_at(index);

			if (tags.size() > 0)
			{
				p_node->set_meta(GGS_TAG_MANAGER_TAGGED_NODE_META, tags);
			}
			else
			{
				p_node->remove_from_group(GGS_TAG_MANAGER_TAGGED_GROUP_NAME);
				p_node->remove_meta(GGS_TAG_MANAGER_TAGGED_NODE_META);
			}

			emit_signal("tag_removed_from_node", p_node, p_tag);
		}
	}
}

void TagManager::remove_tags(Node *p_node, const PackedStringArray &p_tags)
{
	if (p_node != nullptr)
	{
		PackedStringArray tags = get_tags(p_node);

		for (uint32_t i = 0; i < p_tags.size(); i++)
		{
			int64_t index = tags.find(p_tags[i]);

			if (index > -1)
			{
				tags.remove_at(index);
			}
		}

		if (tags.size() > 0)
		{
			p_node->set_meta(GGS_TAG_MANAGER_TAGGED_NODE_META, tags);
		}
		else
		{
			p_node->remove_from_group(GGS_TAG_MANAGER_TAGGED_GROUP_NAME);
			p_node->remove_meta(GGS_TAG_MANAGER_TAGGED_NODE_META);
		}
	}
}

void TagManager::remove_dictionary(TagDictionary *p_dictionary)
{
	if (p_dictionary != nullptr)
	{
		for (int i = 0; i < dictionaries->size(); i++)
		{
			int64_t index = dictionaries->find(p_dictionary);

			if (index > -1)
			{
				dictionaries->remove_at(index);
				emit_signal("dictionary_removed", p_dictionary);
			}
		}
	}
}

void TagManager::_ready()
{
	/// let's retrieve the settings' value
	ProjectSettings *project_settings = ProjectSettings::get_singleton();

	if (project_settings != nullptr)
	{
		project_settings->connect("settings_changed", Callable(this, "_handle_settings_changed"));
		load_dictionaries();
	}
}
