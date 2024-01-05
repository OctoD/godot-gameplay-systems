#include <godot_cpp/classes/button.hpp>

#include "attribute_container_inspector_editor.h"
#include "attribute_container_inspector.h"
#include "system/attribute/attribute_container.h"

using namespace ggs;

void GGSAttributeContainerInspector::_bind_methods()
{

}

bool GGSAttributeContainerInspector::_can_handle(Object *p_object) const
{
	if (p_object == nullptr)
	{
		return false;
	}

	return AttributeContainer::get_class_static() == p_object->get_class();
}

bool GGSAttributeContainerInspector::_parse_property(Object *object, Variant::Type type, const String &name, PropertyHint hint_type, const String &hint_string, BitField<PropertyUsageFlags> usage_flags, bool wide)
{
	if (name == "attributes" && object->get_class() == AttributeContainer::get_class_static())
	{
		GGSAttributeContainerInspectorEditor *editor = memnew(GGSAttributeContainerInspectorEditor);

		editor->set_attribute_container(static_cast<AttributeContainer *>(object));
		
		add_custom_control(editor);

		return true;
	}

	return false;
}
