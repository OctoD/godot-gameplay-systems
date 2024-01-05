#ifndef GGS_ATTRIBUTE_PROJECT_SETTINGS_H
#define GGS_ATTRIBUTE_PROJECT_SETTINGS_H

#include <godot_cpp/classes/ref_counted.hpp>

using namespace godot;

namespace ggs
{
	class AttributeProjectSettings : public RefCounted
	{
		GDCLASS(AttributeProjectSettings, RefCounted);

	private:
		/// @brief The settings paths key.
		static const char *RESOURCE_PATH_KEY;

	protected:
		/// @brief Binds methods to the Godot engine.
		static void _bind_methods();

	public:
		/// @brief Adds the attributes tag dictionary resource path to the project settings.
		/// @param p_tag
		static void set_attribute_resource_path(const String &p_tag_dictionary_path);
		/// @brief Gets the attributes tag dictionary resource path from the project settings.
		/// @return 
		static String get_attribute_resource_path();
        /// @brief Removes the attributes tag dictionary resource path from the project settings.
        static void remove_attribute_resource_path();
        /// @brief Sets up the project settings.
        static void setup();
	};
}

#endif // GGS_ATTRIBUTE_PROJECT_SETTINGS_H
