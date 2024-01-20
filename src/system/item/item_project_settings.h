#ifndef GGS_ITEMS_SETTINGS_H
#define GGS_ITEMS_SETTINGS_H

#include <godot_cpp/classes/ref_counted.hpp>

#include "items_pool.h"

using namespace godot;

namespace ggs
{
	class ItemProjectSettings : public RefCounted
	{
		GDCLASS(ItemProjectSettings, RefCounted)

		static const char *RESOURCES_PATH_KEY;

	protected:
		static void _bind_methods();

	public:
		/// @brief Adds a resource file path to the project settings.
		/// @param p_file_path The resource file path to add.
		static void add_resource(const String &p_file_path);
		/// @brief Removes a resource file path from the project settings.
		/// @param p_file_path The resource file path to remove.
		static void remove_resource(const String &p_file_path);
		/// @brief Gets all resource file paths from the project settings.
		/// @return The resource file paths.
		static PackedStringArray get_resource_file_paths();
		/// @brief Sets up the project settings.
		static void setup();
	};
}

#endif
