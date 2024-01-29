#include "ggs_item_equipment_settings_scene.h"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/file_dialog.hpp>
#include <godot_cpp/classes/h_box_container.hpp>

using namespace ggs;
using namespace ggs::editor_plugin;

void ItemEquipmentSettingsScene::_bind_methods()
{
}

void ItemEquipmentSettingsScene::_handle_equipment_file_selected(String p_path)
{
}

void ItemEquipmentSettingsScene::_handle_items_tag_dictionary_file_selected(String p_path)
{
}

void ItemEquipmentSettingsScene::_ready()
{
	HBoxContainer *equipment_settings_container = memnew(HBoxContainer);
	HBoxContainer *items_tag_dictionary_container = memnew(HBoxContainer);
	VBoxContainer *equipment_settings_vbox_container = memnew(VBoxContainer);
	VBoxContainer *items_tag_dictionary_vbox_container = memnew(VBoxContainer);
	Button *equipment_project_settings_button = memnew(Button);
	Button *items_tag_dictionary_button = memnew(Button);
	Label *equipment_project_settings_label = memnew(Label);
	Label *items_tag_dictionary_label = memnew(Label);
	Label *equipment_project_settings_path_label = memnew(Label);
	Label *items_tag_dictionary_path_label = memnew(Label);

	equipment_project_settings_button->connect("pressed", Callable(this, "_handle_equipment_file_selected"));
	equipment_project_settings_button->set_text(tr("Equipment Project Settings"));

	items_tag_dictionary_button->connect("pressed", Callable(this, "_handle_items_tag_dictionary_file_selected"));
	items_tag_dictionary_button->set_text(tr("Items Tag Dictionary"));

	equipment_settings_vbox_container->add_child(equipment_project_settings_label);
	equipment_settings_vbox_container->add_child(equipment_project_settings_path_label);

	items_tag_dictionary_vbox_container->add_child(items_tag_dictionary_label);
	items_tag_dictionary_vbox_container->add_child(items_tag_dictionary_path_label);

	equipment_settings_container->add_child(equipment_settings_vbox_container);
	equipment_settings_container->add_child(equipment_project_settings_button);

	items_tag_dictionary_container->add_child(items_tag_dictionary_vbox_container);
	items_tag_dictionary_container->add_child(items_tag_dictionary_button);

	add_child(equipment_settings_container);
	add_child(items_tag_dictionary_container);
}
