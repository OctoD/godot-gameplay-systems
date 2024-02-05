#include "ggs_item_main_scene.h"

#include "ggs_equipment_slot_scene.h"
#include "ggs_item_pool_scene.h"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/v_separator.hpp>

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
	}
	else
	{
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
	Button *equipment_button = memnew(Button);
	Button *items_button = memnew(Button);
	VBoxContainer *tab_buttons = memnew(VBoxContainer);
	Panel *tabs_panel = memnew(Panel);
	EquipmentSlotScene *equipment_slot_scene = memnew(EquipmentSlotScene);
	ItemPoolScene *items_pool_scene = memnew(ItemPoolScene);

	equipment_slot_scene->hide();

	tabs_container = memnew(VBoxContainer);

	equipment_button->connect("pressed", Callable(this, "_handle_tab_pressed").bind(0));
	equipment_button->set_text(tr("Equipment"));

	items_button->connect("pressed", Callable(this, "_handle_tab_pressed").bind(1));
	items_button->set_text(tr("Items"));

	tab_buttons->add_child(equipment_button);
	tab_buttons->add_child(items_button);

	tabs_container->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	tabs_container->set_h_size_flags(SIZE_EXPAND_FILL);
	tabs_container->set_v_size_flags(SIZE_EXPAND_FILL);
	tabs_container->add_child(equipment_slot_scene);
	tabs_container->add_child(items_pool_scene);

	tabs_panel->add_child(tabs_container);
	tabs_panel->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	tabs_panel->set_h_size_flags(SIZE_EXPAND_FILL);
	tabs_panel->set_v_size_flags(SIZE_EXPAND_FILL);

	add_child(tab_buttons);

	VSeparator *separator = memnew(VSeparator);
	separator->set_v_size_flags(SIZE_EXPAND_FILL);

	add_child(separator);

	add_child(tabs_panel);

	set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	_handle_tab_pressed(0);
}
