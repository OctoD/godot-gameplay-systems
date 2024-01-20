#include "ggs_item_main_scene.h"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/panel.hpp>

using namespace ggs;
using namespace ggs::editor_plugin;

void ItemMainScene::_handle_tab_pressed(int tab_id)
{
}

void ItemMainScene::_bind_methods()
{
}

void ItemMainScene::_ready()
{
	Button *equipment_button = memnew(Button);
	Button *items_button = memnew(Button);
	VBoxContainer *tab_buttons = memnew(VBoxContainer);
	VBoxContainer *tabs_container = memnew(VBoxContainer);
	Panel *tabs_panel = memnew(Panel);
	Panel *items_panel = memnew(Panel);
	Panel *equipment_panel = memnew(Panel);

	equipment_button->set_text(tr("Equipment"));
	items_button->set_text(tr("Items"));

	tab_buttons->set_name("GGS_ITEMS_TabButtons");

	tab_buttons->add_child(equipment_button);
	tab_buttons->add_child(items_button);

	tabs_container->add_child(equipment_panel);
	tabs_container->add_child(items_panel);
	tabs_container->set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	tabs_panel->add_child(tabs_container);

	add_child(tab_buttons);
	add_child(tabs_panel);

	set_anchors_and_offsets_preset(PRESET_FULL_RECT);
}
