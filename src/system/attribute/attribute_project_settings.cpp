#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/project_settings.hpp>

#include "attribute_project_settings.h"

using namespace ggs;

const char *AttributeProjectSettings::RESOURCE_PATH_KEY = "application/gameplay_systems/attribute_system/attribute_dictionary";

void AttributeProjectSettings::_bind_methods()
{
	/// binds signals
}

void AttributeProjectSettings::set_attribute_resource_path(const String &p_file_path)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		ProjectSettings *project_settings = ProjectSettings::get_singleton();

		if (project_settings != nullptr)
		{
			project_settings->set_setting(RESOURCE_PATH_KEY, p_file_path);
			project_settings->save();
		}
	}
}

String AttributeProjectSettings::get_attribute_resource_path()
{
	if (ProjectSettings::get_singleton() != nullptr)
	{
		return ProjectSettings::get_singleton()->get_setting(RESOURCE_PATH_KEY, "");
	}

	return "";
}

void AttributeProjectSettings::remove_attribute_resource_path()
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		ProjectSettings *project_settings = ProjectSettings::get_singleton();

		if (project_settings != nullptr)
		{
			project_settings->set_setting(RESOURCE_PATH_KEY, "");
			project_settings->save();
		}
	}
}

void AttributeProjectSettings::setup()
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		ProjectSettings *project_settings = ProjectSettings::get_singleton();

		if (project_settings != nullptr)
		{
			String value;

			if (!project_settings->has_setting(RESOURCE_PATH_KEY))
			{
				project_settings->set_setting(RESOURCE_PATH_KEY, "");
			}

			Dictionary resource_path_dictionary;

			resource_path_dictionary["name"] = RESOURCE_PATH_KEY;
			resource_path_dictionary["default_value"] = Variant("").get_type();
			resource_path_dictionary["hint"] = PropertyHint::PROPERTY_HINT_TYPE_STRING;
			resource_path_dictionary["hint_string"] = "*.tres,*.res,*.csv";

			project_settings->add_property_info(resource_path_dictionary);
			project_settings->set_initial_value(RESOURCE_PATH_KEY, value);
			project_settings->set_restart_if_changed(RESOURCE_PATH_KEY, false);
			project_settings->save();
		}
	}
}
