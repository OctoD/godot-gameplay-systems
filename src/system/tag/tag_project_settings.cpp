#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include "tag_project_settings.h"

using namespace godot;

const char *TagProjectSettings::RESOURCE_PATHS_KEY = "gameplay_systems/tagging_system/tag_dictionaries";

// No bound methods. This class is only used to register settings and has to be used internally by the addon.
void TagProjectSettings::_bind_methods()
{
}

TagProjectSettings::TagProjectSettings()
{
}

TagProjectSettings::~TagProjectSettings()
{
}

void TagProjectSettings::add_resource(const String &p_file_path)
{
	ProjectSettings *project_settings = ProjectSettings::get_singleton();

	if (project_settings != nullptr)
	{
		PackedStringArray settings = project_settings->get_setting(RESOURCE_PATHS_KEY, PackedStringArray());

		if (!settings.has(p_file_path))
		{
			settings.append(p_file_path);
		}

		project_settings->set_setting(RESOURCE_PATHS_KEY, settings);
		project_settings->save();
	}
}

void TagProjectSettings::remove_resource(const String &p_file_path)
{
	ProjectSettings *project_settings = ProjectSettings::get_singleton();

	if (project_settings != nullptr)
	{
		PackedStringArray settings = project_settings->get_setting(RESOURCE_PATHS_KEY, PackedStringArray());

		int index = settings.find(p_file_path);

		if (index > -1)
		{
			settings.remove_at(index);
		}

		project_settings->set_setting(RESOURCE_PATHS_KEY, settings);
		project_settings->save();
	}
}

PackedStringArray TagProjectSettings::get_resource_file_paths()
{
	if (ProjectSettings::get_singleton() != nullptr)
	{
		return ProjectSettings::get_singleton()->get_setting(RESOURCE_PATHS_KEY, PackedStringArray());
	}

	return PackedStringArray();
}

void TagProjectSettings::setup()
{
	ProjectSettings *project_settings = ProjectSettings::get_singleton();

	if (project_settings != nullptr)
	{
		PackedStringArray value;

		if (!project_settings->has_setting(RESOURCE_PATHS_KEY))
		{
			project_settings->set_setting(RESOURCE_PATHS_KEY, value);
		}

		Dictionary dictionary;

		dictionary["name"] = RESOURCE_PATHS_KEY;
		dictionary["default_value"] = Variant(value).get_type();
		dictionary["hint"] = PropertyHint::PROPERTY_HINT_ARRAY_TYPE;
		dictionary["hint_string"] = "*.tres,*.res,*.csv";

		project_settings->add_property_info(dictionary);
		project_settings->set_initial_value(RESOURCE_PATHS_KEY, value);
		project_settings->set_restart_if_changed(RESOURCE_PATHS_KEY, false);
		project_settings->save();
	}
}
