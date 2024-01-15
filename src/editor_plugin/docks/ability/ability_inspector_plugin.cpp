#include "ability_inspector_plugin.h"

#include "ability_inspector_plugin_editor.h"
#include "system/ability/ability.h"

using namespace ggs;
using namespace ggs::editor_plugin;

void AbilityInspectorPlugin::_bind_methods()
{
}

bool AbilityInspectorPlugin::_create_ability_tag_control(Object *p_object, const AbilityInspectorPluginEditor::EditedProperty &p_property)
{
	AbilityInspectorPluginEditor *editor = memnew(AbilityInspectorPluginEditor);

	editor->set_ability(static_cast<Ability *>(p_object));
	editor->set_edited_property(p_property);

	add_custom_control(editor);

	return true;
}

bool AbilityInspectorPlugin::_can_handle(Object *p_object) const
{
	if (p_object == nullptr)
	{
		return false;
	}

	return Ability::get_class_static() == p_object->get_class();
}

bool AbilityInspectorPlugin::_parse_property(Object *object, Variant::Type type, const String &name, PropertyHint hint_type, const String &hint_string, BitField<PropertyUsageFlags> usage_flags, bool wide)
{
	if (object != nullptr && object->get_class() == Ability::get_class_static())
	{
		if (name == "tags_added_on_cooldown_end")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_ADDED_ON_COOLDOWN_END);
		}
		else if (name == "tags_added_on_cooldown_start")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_ADDED_ON_COOLDOWN_START);
		}
		else if (name == "tags_added_on_grant")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_ADDED_ON_GRANT);
		}
		else if (name == "tags_added_on_activation")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_ADDED_ON_ACTIVATION);
		}
		else if (name == "tags_removed_on_cooldown_end")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_REMOVED_ON_COOLDOWN_END);
		}
		else if (name == "tags_removed_on_cooldown_start")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_REMOVED_ON_COOLDOWN_START);
		}
		else if (name == "tags_removed_on_activation")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_REMOVED_ON_ACTIVATION);
		}
		else if (name == "tags_removed_on_block")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_REMOVED_ON_BLOCK);
		}
		else if (name == "tags_removed_on_cancel")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_REMOVED_ON_CANCEL);
		}
		else if (name == "tags_required_to_activate")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_REQUIRED_TO_ACTIVATE);
		}
		else if (name == "tags_required_to_block")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_REQUIRED_TO_BLOCK);
		}
		else if (name == "tags_required_to_cancel")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_REQUIRED_TO_CANCEL);
		}
		else if (name == "tags_required_to_grant")
		{
			return _create_ability_tag_control(object, AbilityInspectorPluginEditor::EditedProperty::TAGS_REQUIRED_TO_GRANT);
		}
	}
	return false;
}
