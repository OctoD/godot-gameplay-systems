#ifndef GGS_ITEM_EQUIPMENT_SETTINGS_H
#define GGS_ITEM_EQUIPMENT_SETTINGS_H

#include <godot_cpp/classes/v_box_container.hpp>

using namespace godot;

namespace ggs::editor_plugin
{
	class ItemEquipmentSettingsScene : public VBoxContainer
	{
		GDCLASS(ItemEquipmentSettingsScene, VBoxContainer);

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();
		/// @brief Handles the file selected as the equipment project settings.
		/// @param p_path The path to the file selected.
		void _handle_equipment_file_selected(String p_path);
		/// @brief Handles the file selected as the items project settings.
		/// @param p_path The path to the file selected.
		void _handle_items_tag_dictionary_file_selected(String p_path);

	public:
		void _ready() override;
	};
}

#endif
