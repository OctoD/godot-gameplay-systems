#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/theme.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

#include "docks/ability/ability_inspector_plugin.h"
#include "docks/attribute/attribute_container_inspector.h"
#include "docks/tag/tag_docks.h"
#include "main_scene/ggs_main_scene.h"
#include "ggs_editor_plugin.h"
#include "resource_manager/resource_manager.h"

using namespace ggs;
using namespace ggs::editor_plugin;

static MainScene *ggs_tag_main_scene = nullptr;
static TagDocks *ggs_tag_docks = nullptr;
static AbilityInspectorPlugin *ggs_ability_inspector_plugin = nullptr;
static AttributeContainerInspector *ggs_attribute_container_inspector = nullptr;

GGSEditorPlugin::GGSEditorPlugin()
{
}

GGSEditorPlugin::~GGSEditorPlugin()
{
}

void GGSEditorPlugin::_enter_tree()
{
	ggs_tag_main_scene = memnew(MainScene);
	ggs_tag_docks = memnew(TagDocks);
	ggs_ability_inspector_plugin = memnew(AbilityInspectorPlugin);
	ggs_attribute_container_inspector = memnew(AttributeContainerInspector);

	EditorInterface::get_singleton()->get_editor_main_screen()->add_child(ggs_tag_main_scene);

	add_control_to_dock(DOCK_SLOT_RIGHT_UL, ggs_tag_docks);
	add_inspector_plugin(ggs_ability_inspector_plugin);
	add_inspector_plugin(ggs_attribute_container_inspector);

	ggs_tag_main_scene->set_visible(false);

	ResourceManager::get_singleton()->ensure_directories();
}

void GGSEditorPlugin::_exit_tree()
{
	EditorInterface::get_singleton()->get_editor_main_screen()->remove_child(ggs_tag_main_scene);

	remove_control_from_docks(ggs_tag_docks);
	remove_inspector_plugin(ggs_ability_inspector_plugin);
	remove_inspector_plugin(ggs_attribute_container_inspector);

	memdelete(ggs_tag_docks);
	memdelete(ggs_tag_main_scene);
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
