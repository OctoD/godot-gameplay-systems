#include "equipment_project_settings.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/project_settings.hpp>

using namespace ggs;

const char *EquipmentProjectSettings::RESOURCES_PATH_KEY = "application/gameplay_systems/item_system/equipment_slots_paths";

void EquipmentProjectSettings::_bind_methods()
{
}

void EquipmentProjectSettings::add_resource(const String &p_file_path)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		ProjectSettings *project_settings = ProjectSettings::get_singleton();

		if (project_settings != nullptr)
		{
			PackedStringArray settings = project_settings->get_setting(RESOURCES_PATH_KEY, PackedStringArray());

			if (!settings.has(p_file_path))
			{
				settings.append(p_file_path);
			}

			project_settings->set_setting(RESOURCES_PATH_KEY, settings);
			project_settings->save();
		}
	}
}

void EquipmentProjectSettings::remove_resource(const String &p_file_path)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		ProjectSettings *project_settings = ProjectSettings::get_singleton();

		if (project_settings != nullptr)
		{
			PackedStringArray settings = project_settings->get_setting(RESOURCES_PATH_KEY, PackedStringArray());

			int index = settings.find(p_file_path);

			if (index > -1)
			{
				settings.remove_at(index);
			}

			project_settings->set_setting(RESOURCES_PATH_KEY, settings);
			project_settings->save();
		}
	}
}

PackedStringArray EquipmentProjectSettings::get_resource_file_paths()
{
	if (ProjectSettings::get_singleton() != nullptr)
	{
		return ProjectSettings::get_singleton()->get_setting(RESOURCES_PATH_KEY, PackedStringArray());
	}

	return PackedStringArray();
}

void EquipmentProjectSettings::setup()
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		ProjectSettings *project_settings = ProjectSettings::get_singleton();

		if (project_settings != nullptr)
		{
			PackedStringArray value;

			if (!project_settings->has_setting(RESOURCES_PATH_KEY))
			{
				project_settings->set_setting(RESOURCES_PATH_KEY, value);
			}

			Dictionary dictionary;

			dictionary["name"] = RESOURCES_PATH_KEY;
			dictionary["default_value"] = Variant(value).get_type();
			dictionary["hint"] = PropertyHint::PROPERTY_HINT_ARRAY_TYPE;
			dictionary["hint_string"] = "*.tres,*.res,*.csv";

			project_settings->add_property_info(dictionary);
			project_settings->set_initial_value(RESOURCES_PATH_KEY, value);
			project_settings->set_restart_if_changed(RESOURCES_PATH_KEY, false);
			project_settings->save();
		}
	}
}
