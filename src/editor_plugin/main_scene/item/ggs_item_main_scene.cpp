#include "ggs_item_main_scene.h"

#include "ggs_equipment_slot_scene.h"
#include "ggs_item_equipment_settings_scene.h"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/panel.hpp>

using namespace ggs;
using namespace ggs::editor_plugin;

void ItemMainScene::_handle_tab_pressed(int tab_id)
{
	Control *control = cast_to<Control>(tabs_container->get_child(tab_id));

	if (control)
	{
		for (int i = 0; i < tabs_container->get_child_count(); i++)
		{
			Control *child = cast_to<Control>(tabs_container->get_child(i));

			if (child)
			{
				child->hide();
			}
		}

		control->show();
	} else {
		ERR_PRINT("ItemMainScene::_handle_tab_pressed control is null.");
	}
}

void ItemMainScene::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("_handle_tab_pressed", "tab_id"), &ItemMainScene::_handle_tab_pressed);
}

void ItemMainScene::_ready()
{
	Button *settings_button = memnew(Button);
	Button *equipment_button = memnew(Button);
	Button *items_button = memnew(Button);
	VBoxContainer *tab_buttons = memnew(VBoxContainer);
	Panel *tabs_panel = memnew(Panel);
	Panel *items_panel = memnew(Panel);
	Panel *equipment_panel = memnew(Panel);
	EquipmentSlotScene *equipment_slot_scene = memnew(EquipmentSlotScene);
	ItemEquipmentSettingsScene *item_equipment_settings = memnew(ItemEquipmentSettingsScene);

	equipment_slot_scene->hide();

	tabs_container = memnew(VBoxContainer);

	settings_button->connect("pressed", Callable(this, "_handle_tab_pressed").bind(0));
	settings_button->set_text(tr("Settings"));

	equipment_button->connect("pressed", Callable(this, "_handle_tab_pressed").bind(1));
	equipment_button->set_text(tr("Equipment"));

	equipment_panel->add_child(equipment_slot_scene);
	equipment_panel->set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	items_button->connect("pressed", Callable(this, "_handle_tab_pressed").bind(2));
	items_button->set_text(tr("Items"));

	items_panel->set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	tab_buttons->add_child(settings_button);
	tab_buttons->add_child(equipment_button);
	tab_buttons->add_child(items_button);

	tabs_container->add_child(item_equipment_settings);
	tabs_container->add_child(equipment_panel);
	tabs_container->add_child(items_panel);
	tabs_container->set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	tabs_panel->add_child(tabs_container);
	tabs_panel->set_v_size_flags(SIZE_EXPAND_FILL);
	tabs_panel->set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	add_child(tab_buttons);
	add_child(tabs_panel);

	set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	_handle_tab_pressed(0);
}
