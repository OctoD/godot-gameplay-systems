#ifndef GGS_ITEM_MAIN_SCENE_H
#define GGS_ITEM_MAIN_SCENE_H

#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

using namespace godot;

namespace ggs::editor_plugin
{
	class ItemMainScene : public HBoxContainer
	{
		GDCLASS(ItemMainScene, HBoxContainer);
		/// @brief Handles the tab button being pressed.
		/// @param tab_id The tab id of the button that was pressed.
		void _handle_tab_pressed(int tab_id);

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();
		/// @brief The container for the "tabs".
		VBoxContainer *tabs_container;

	public:
		void _ready() override;
	};
}

#endif
