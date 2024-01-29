#include "ggs_new_resource_modal.h"

#include "resource_manager/resource_manager.h"

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/button_group.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

using namespace ggs;
using namespace ggs::editor_plugin;

void NewResourceModal::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("_handle_close_button_pressed"), &NewResourceModal::_handle_close_button_pressed);
	ClassDB::bind_method(D_METHOD("_handle_create_button_pressed"), &NewResourceModal::_handle_create_button_pressed);
	ClassDB::bind_method(D_METHOD("_handle_line_edit_text_changed"), &NewResourceModal::_handle_line_edit_text_changed);
	/// signals binding
	ADD_SIGNAL(MethodInfo("create_requested", PropertyInfo(Variant::STRING, "resource_name")));
}

void NewResourceModal::_handle_close_button_pressed()
{
	resource_name_label->set_text("");
	resource_name_line_edit->set_text("");
	hide();
}

void NewResourceModal::_handle_create_button_pressed()
{
	emit_signal("create_requested", resource_name_label->get_text());
	_handle_close_button_pressed();
}

void NewResourceModal::_handle_line_edit_text_changed(String text)
{
	resource_name_label->set_text(text.replace(" ", "_").to_lower() + ".tres");
}

void NewResourceModal::_ready()
{
	hide();

	Button *close_button = memnew(Button);
	Button *create_button = memnew(Button);
	Label *title_label = memnew(Label);

	resource_name_label = memnew(Label);
	resource_name_line_edit = memnew(LineEdit);

	HBoxContainer *h_box_container = memnew(HBoxContainer);
	VBoxContainer *v_box_container = memnew(VBoxContainer);

	GGSResourceManager *resource_manager = GGSResourceManager::get_singleton();

	add_child(v_box_container);

	v_box_container->set_alignment(BoxContainer::ALIGNMENT_CENTER);

	v_box_container->add_child(title_label);
	v_box_container->add_child(resource_name_label);
	v_box_container->add_child(resource_name_line_edit);

	h_box_container->add_child(close_button);
	h_box_container->add_child(create_button);

	v_box_container->add_child(h_box_container);

	title_label->set_text(tr("New Resource"));
	resource_name_line_edit->set_placeholder(tr("New Resource"));

	close_button->set_text(tr("Close"));
	create_button->set_text(tr("Create"));

	close_button->connect("pressed", Callable(this, "_handle_close_button_pressed"));
	create_button->connect("pressed", Callable(this, "_handle_create_button_pressed"));
	resource_name_line_edit->connect("text_changed", Callable(this, "_handle_line_edit_text_changed"));

	connect("close_requested", Callable(this, "_handle_close_button_pressed"));

	set_min_size(Size2(320, 240));
}
