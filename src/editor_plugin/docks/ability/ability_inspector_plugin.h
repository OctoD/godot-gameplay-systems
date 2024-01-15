#ifndef GGS_ABILITY_INSPECTOR_PLUGIN_H
#define GGS_ABILITY_INSPECTOR_PLUGIN_H

#include <godot_cpp/classes/editor_inspector_plugin.hpp>
#include "ability_inspector_plugin_editor.h"

using namespace godot;

namespace ggs::editor_plugin
{
	class AbilityInspectorPlugin : public EditorInspectorPlugin
	{
		GDCLASS(AbilityInspectorPlugin, EditorInspectorPlugin);

	protected:
		static void _bind_methods();
		bool _create_ability_tag_control(Object *p_object, const AbilityInspectorPluginEditor::EditedProperty &p_property);

	public:
		bool _can_handle(Object *p_object) const override;
		bool _parse_property(Object *object, Variant::Type type, const String &name, PropertyHint hint_type, const String &hint_string, BitField<PropertyUsageFlags> usage_flags, bool wide) override;
	};
}

#endif