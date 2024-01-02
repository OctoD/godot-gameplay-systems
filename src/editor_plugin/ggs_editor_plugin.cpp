#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/theme.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

#include "docks/tag/tag_docks.h"
#include "main_scene/ggs_main_scene.h"
#include "ggs_editor_plugin.h"

static GGSMainScene *ggs_tag_main_scene = nullptr;
static GGSTagDocks *ggs_tag_docks = nullptr;

GGSEditorPlugin::GGSEditorPlugin()
{

}

GGSEditorPlugin::~GGSEditorPlugin()
{
}

void GGSEditorPlugin::_enter_tree()
{
	ggs_tag_main_scene = memnew(GGSMainScene);
	ggs_tag_docks = memnew(GGSTagDocks);

	EditorInterface::get_singleton()->get_editor_main_screen()->add_child(ggs_tag_main_scene);

	add_control_to_dock(DOCK_SLOT_RIGHT_UL, ggs_tag_docks);

	ggs_tag_main_scene->set_visible(false);
}

void GGSEditorPlugin::_exit_tree()
{
	EditorInterface::get_singleton()->get_editor_main_screen()->remove_child(ggs_tag_main_scene);

	remove_control_from_docks(ggs_tag_docks);

	memdelete(ggs_tag_main_scene);
	memdelete(ggs_tag_docks);
}

bool GGSEditorPlugin::_has_main_screen() const
{
    return true;
}

void GGSEditorPlugin::_make_visible(bool p_visible)
{
	if (ggs_tag_main_scene != nullptr)
	{
		ggs_tag_main_scene->set_visible(p_visible);
	}
}

String GGSEditorPlugin::_get_plugin_name() const
{
	return "GGS";
}

void GGSEditorPlugin::_bind_methods()
{
}
