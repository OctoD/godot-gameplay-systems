#include "ggs_main_scene.h"

#include "attribute/ggs_attribute_main_scene.h"
#include "tag/ggs_tag_main_scene.h"
#include "item/ggs_item_main_scene.h"

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/tab_container.hpp>

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
	Panel *ability_panel = memnew(Panel);
	Panel *attributes_panel = memnew(Panel);
	Panel *item_panel = memnew(Panel);
	TabContainer *tab_container = memnew(TabContainer);
	Panel *tag_manager_panel = memnew(Panel);

	tab_container->set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);

	add_child(tab_container);

	tab_container->add_child(tag_manager_panel);
	tab_container->add_child(attributes_panel);
	tab_container->add_child(item_panel);
	// commented. Will come with a visual ability designer in the future.
	// tab_container->add_child(ability_panel);

	tag_manager_panel->set_name(tag_manager_panel->tr("Tag Manager"));
	attributes_panel->set_name(attributes_panel->tr("Attributes"));
	item_panel->set_name(item_panel->tr("Items & Equipment"));
	// commented. Will come with a visual ability designer in the future.
	// ability_panel->set_name(ability_panel->tr("Ability"));

	AttributeMainScene *attribute_main_scene = memnew(AttributeMainScene);
	TagMainScene *tag_main_scene = memnew(TagMainScene);
	ItemMainScene *item_main_scene = memnew(ItemMainScene);

	attributes_panel->add_child(attribute_main_scene);
	tag_manager_panel->add_child(tag_main_scene);
	item_panel->add_child(item_main_scene);
}

void MainScene::_bind_methods()
{
	/// BANANA SPLITS HERE
}
