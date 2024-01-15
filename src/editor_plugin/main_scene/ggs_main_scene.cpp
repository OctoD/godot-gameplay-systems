#include "attribute/ggs_attribute_main_scene.h"
#include "tag/ggs_tag_main_scene.h"
#include "ggs_main_scene.h"

using namespace ggs;
using namespace ggs::editor_plugin;

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::_ready()
{
	ability_panel = memnew(Panel);
	attributes_panel = memnew(Panel);
	tab_container = memnew(TabContainer);
	tag_manager_panel = memnew(Panel);

	tab_container->set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);

	add_child(tab_container);

	tab_container->add_child(tag_manager_panel);
	tab_container->add_child(attributes_panel);
	// commented. Will come with a visual ability designer in the future.
	// tab_container->add_child(ability_panel);

	tag_manager_panel->set_name(tag_manager_panel->tr("Tag Manager"));
	attributes_panel->set_name(attributes_panel->tr("Attributes"));
	// commented. Will come with a visual ability designer in the future.
	// ability_panel->set_name(ability_panel->tr("Ability"));

	AttributeMainScene *attribute_main_scene = memnew(AttributeMainScene);
	TagMainScene *tag_main_scene = memnew(TagMainScene);

	attributes_panel->add_child(attribute_main_scene);
	tag_manager_panel->add_child(tag_main_scene);
}

void MainScene::_bind_methods()
{
}
