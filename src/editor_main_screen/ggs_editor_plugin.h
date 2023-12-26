#ifndef GGS_EDITOR_TAB_H
#define GGS_EDITOR_TAB_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/editor_plugin.hpp>
#include <godot_cpp/classes/ref.hpp>

using namespace godot;

class GGSEditorPlugin : public EditorPlugin
{
	GDCLASS(GGSEditorPlugin, EditorPlugin);

public:
	GGSEditorPlugin();
	~GGSEditorPlugin();

	void _enter_tree() override;
	void _exit_tree() override;
	bool _has_main_screen() const override;
	void _make_visible(bool p_visible) override;
	String _get_plugin_name() const override;

protected:
	static void _bind_methods();
};

#endif