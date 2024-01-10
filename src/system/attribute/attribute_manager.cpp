#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

#include "attribute_manager.h"
#include "system/attribute/attribute_manager.h"
#include "system/attribute/attribute_project_settings.h"
#include "system/tag/tag_manager.h"

using namespace ggs;

AttributeManager *AttributeManager::_singleton = nullptr;

void AttributeManager::_handle_tag_dictionary_changed()
{
	if (tag_dictionary != nullptr)
	{
		PackedStringArray previous_attributes = attributes.duplicate();

		attributes = tag_dictionary->get_tags();

		emit_signal("attributes_changed", previous_attributes, attributes);
	}
}

void AttributeManager::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("_handle_tag_dictionary_changed"), &AttributeManager::_handle_tag_dictionary_changed);
	ClassDB::bind_method(D_METHOD("get_attributes"), &AttributeManager::get_attributes);
	ClassDB::bind_method(D_METHOD("load_attributes"), &AttributeManager::load_attributes);
	ClassDB::bind_method(D_METHOD("set_attributes", "attributes"), &AttributeManager::set_attributes);

	/// signals binding
	ADD_SIGNAL(MethodInfo("attributes_changed", PropertyInfo(Variant::PACKED_STRING_ARRAY, "previous_attributes"), PropertyInfo(Variant::PACKED_STRING_ARRAY, "current_attributes")));
	ADD_SIGNAL(MethodInfo("attributes_dictionary_changed", PropertyInfo(Variant::OBJECT, "previous_dictionary"), PropertyInfo(Variant::OBJECT, "current_dictionary")));
}

AttributeManager::AttributeManager()
{
	if (_singleton == nullptr)
	{
		_singleton = this;
	}
	else
	{
		attributes = _singleton->attributes;
	}
}

AttributeManager::~AttributeManager()
{
	if (_singleton == this)
	{
		_singleton = nullptr;
	}
}

AttributeManager *AttributeManager::get_singleton()
{
	if (_singleton == nullptr)
	{
		_singleton = memnew(AttributeManager);
	}
	
	return _singleton;
}

PackedStringArray AttributeManager::get_attributes()
{
	return attributes;
}

TagDictionary *AttributeManager::get_tag_dictionary() const
{
	return tag_dictionary;
}

void AttributeManager::_ready()
{
	load_attributes();
}

TagDictionary *AttributeManager::load_attributes()
{
	String p_tag_dictionary_path = AttributeProjectSettings::get_attribute_resource_path();
	ResourceLoader *resource_loader = ResourceLoader::get_singleton();

	if (resource_loader != nullptr)
	{
		Ref<Resource> resource = resource_loader->load(p_tag_dictionary_path);
		tag_dictionary = cast_to<TagDictionary>((Variant)resource);

		if (tag_dictionary != nullptr)
		{
			attributes = tag_dictionary->get_tags();

			if (!tag_dictionary->is_connected("changed", Callable(this, "_handle_tag_dictionary_changed")))
			{
				tag_dictionary->connect("changed", Callable(this, "_handle_tag_dictionary_changed"));
			}

			return tag_dictionary;
		}
	}

	return nullptr;
}

void AttributeManager::set_attributes(const PackedStringArray &p_attributes)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		PackedStringArray previous = attributes.duplicate();
		attributes = p_attributes;
		emit_signal("attributes_changed", previous, attributes);
	}
}

void AttributeManager::set_tag_dictionary(TagDictionary *p_tag_dictionary)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		TagDictionary *previous = tag_dictionary;
		tag_dictionary = p_tag_dictionary;
		emit_signal("attributes_dictionary_changed", previous, tag_dictionary);
	}
}
