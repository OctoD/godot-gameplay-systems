#ifndef TAG_PROJECT_SETTINGS_H
#define TAG_PROJECT_SETTINGS_H

#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class TagProjectSettings : public RefCounted
{
	GDCLASS(TagProjectSettings, RefCounted)

public:
	/// @brief The tag project settings constructor.
	TagProjectSettings();
	/// @brief The tag project settings destructor.
	~TagProjectSettings();

	/// @brief Adds a resource file path to the project settings.
	/// @param p_file_path The resource file path to add.
	static void add_resource(const String &p_file_path);
	/// @brief Removes a resource file path from the project settings.
	/// @param p_file_path 
	static void remove_resource(const String &p_file_path);
	/// @brief Gets all resource file paths from the project settings.
	/// @return All resource file paths.
	static PackedStringArray get_resource_file_paths();
	/// @brief Sets up the project settings.
	static void setup();

protected:
	/// @brief Registers all methods that can be called from Godot.
	/// @param p_resource_file_paths The resource file paths to update.
	static void _bind_methods();

private:
	friend class GGSTagMainScene;
	/// @brief The settings paths key.
	static const char *RESOURCE_PATHS_KEY;
};

#endif
