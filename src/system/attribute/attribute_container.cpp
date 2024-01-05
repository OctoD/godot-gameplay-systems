#include <godot_cpp/classes/engine.hpp>

#include "attribute_container.h"
#include "attribute_manager.h"

using namespace ggs;

void AttributeContainer::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("ensure_attributes", "attributes"), &AttributeContainer::ensure_attributes);
	ClassDB::bind_method(D_METHOD("get_attribute", "attribute_name"), &AttributeContainer::get_attribute);
	ClassDB::bind_method(D_METHOD("get_attributes"), &AttributeContainer::get_attributes);
	ClassDB::bind_method(D_METHOD("has_attribute", "attribute_name"), &AttributeContainer::has_attribute);
	ClassDB::bind_method(D_METHOD("set_attributes", "attributes"), &AttributeContainer::set_attributes);

	/// properties binding
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attributes", PROPERTY_HINT_RESOURCE_TYPE, "24/17:Attribute"), "set_attributes", "get_attributes");
}

AttributeContainer::AttributeContainer()
{
}

AttributeContainer::AttributeContainer(TypedArray<Attribute> p_attributes)
{
	attributes = p_attributes;
}

AttributeContainer::~AttributeContainer()
{
}

void AttributeContainer::_ready()
{
}

void AttributeContainer::ensure_attributes(PackedStringArray p_attributes)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		for (StringName tagname : p_attributes)
		{
			if (!has_attribute(tagname))
			{
				Attribute *attribute = memnew(Attribute);

				attribute->set_tag_name(tagname);
				attributes.push_back(attribute);
			}
		}
	}
}

bool AttributeContainer::has_attribute(StringName p_attribute_name) const
{
	for (int i = 0; i < attributes.size(); i++)
	{
		Variant attribute_variant = attributes[i];
		Attribute *attribute = cast_to<Attribute>(attribute_variant);

		if (attribute != nullptr && attribute->has_tag_name(p_attribute_name))
		{
			return true;
		}
	}

	return false;
}

Attribute *AttributeContainer::get_attribute(StringName p_attribute_name) const
{
	for (int i = 0; i < attributes.size(); i++)
	{
		Variant attribute_variant = attributes.operator[](i);
		Attribute *attribute = cast_to<Attribute>(attribute_variant);

		if (attribute != nullptr && attribute->has_tag_name(p_attribute_name))
		{
			return attribute;
		}
	}

	return nullptr;
}

TypedArray<Attribute> AttributeContainer::get_attributes() const
{
	return attributes;
}

void AttributeContainer::set_attributes(const TypedArray<Attribute> &attributes)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		this->attributes = attributes;
	}
}
