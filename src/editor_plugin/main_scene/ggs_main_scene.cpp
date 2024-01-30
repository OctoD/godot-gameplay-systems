#include "ggs_main_scene.h"

#include "attribute/ggs_attribute_main_scene.h"
#include "tag/ggs_tag_main_scene.h"
#include "item/ggs_item_main_scene.h"

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/tab_container.hpp>
#include <godot_cpp/classes/scroll_container.hpp>

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
	set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);
	set_h_size_flags(Control::SIZE_EXPAND_FILL);
	set_v_size_flags(Control::SIZE_EXPAND_FILL);

	Panel *ability_panel = memnew(Panel);
	Panel *item_panel = memnew(Panel);

	ScrollContainer *attributes_panel = memnew(ScrollContainer);
	attributes_panel->set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);
	attributes_panel->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	attributes_panel->set_v_size_flags(Control::SIZE_EXPAND_FILL);

	TabContainer *tab_container = memnew(TabContainer);
	tab_container->set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);
	tab_container->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	tab_container->set_v_size_flags(Control::SIZE_EXPAND_FILL);

	ScrollContainer *tag_manager_panel = memnew(ScrollContainer);
	tag_manager_panel->set_anchors_and_offsets_preset(LayoutPreset::PRESET_FULL_RECT);
	tag_manager_panel->set_follow_focus(true);
	tag_manager_panel->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	tag_manager_panel->set_v_size_flags(Control::SIZE_EXPAND_FILL);

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
	attributes_panel->add_child(attribute_main_scene);

	ItemMainScene *item_main_scene = memnew(ItemMainScene);
	item_panel->add_child(item_main_scene);

	TagMainScene *tag_main_scene = memnew(TagMainScene);
	tag_manager_panel->add_child(tag_main_scene);
}

void MainScene::_bind_methods()
{
	/// BANANA SPLITS HERE
}
