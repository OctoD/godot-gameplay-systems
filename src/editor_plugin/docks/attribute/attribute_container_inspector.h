#ifndef GG_ATTRIBUTE_CONTAINER_INSPECTOR_H
#define GG_ATTRIBUTE_CONTAINER_INSPECTOR_H

#include <godot_cpp/classes/editor_inspector_plugin.hpp>

using namespace godot;

namespace ggs::editor_plugin
{
	class AttributeContainerInspector : public EditorInspectorPlugin
	{
		GDCLASS(AttributeContainerInspector, EditorInspectorPlugin);

	protected:
		static void _bind_methods();

	public:
		bool _can_handle(Object *p_object) const override;
		bool _parse_property(Object *object, Variant::Type type, const String &name, PropertyHint hint_type, const String &hint_string, BitField<PropertyUsageFlags> usage_flags, bool wide) override;
	};
}

#endif