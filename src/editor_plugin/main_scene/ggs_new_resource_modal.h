#ifndef GGS_NEW_RESOURCE_MODAL_H
#define GGS_NEW_RESOURCE_MODAL_H

#include <godot_cpp/classes/window.hpp>

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/line_edit.hpp>

using namespace godot;

namespace ggs::editor_plugin
{
	class NewResourceModal : public Window
	{
		GDCLASS(NewResourceModal, Window);

	protected:
		static void _bind_methods();
		void _handle_close_button_pressed();
		void _handle_create_button_pressed();
		void _handle_line_edit_text_changed(String text);
		Button *create_button;
		Label *resource_name_label;
		LineEdit *resource_name_line_edit;

	public:
		void _ready() override;
	};
}

#endif
