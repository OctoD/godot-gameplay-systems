#include <godot_cpp/classes/accept_dialog.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/option_button.hpp>
#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/label.hpp>

#include "ggs_attribute_main_scene.h"
#include "system/attribute/attribute_manager.h"
#include "system/attribute/attribute_project_settings.h"
#include "system/tag/tag_manager.h"

using namespace ggs;

void GGSAttributeMainScene::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("_handle_dictionary_selected", "p_item_index"), &GGSAttributeMainScene::_handle_dictionary_selected);
	ClassDB::bind_method(D_METHOD("render"), &GGSAttributeMainScene::render);
}

GGSAttributeMainScene::GGSAttributeMainScene()
{
	tag_dictionary = memnew(TagDictionary);
}

GGSAttributeMainScene::~GGSAttributeMainScene()
{
}

void GGSAttributeMainScene::_ready()
{
	set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	HBoxContainer *toolbar = memnew(HBoxContainer);
	toolbar->set_anchors_and_offsets_preset(PRESET_LEFT_WIDE);

	tag_select = memnew(OptionButton);
	tag_select->connect("item_selected", Callable(this, "_handle_dictionary_selected"));
	tag_select->set_anchors_and_offsets_preset(PRESET_LEFT_WIDE);
	tag_select->set_visible(false);

	Label *label = memnew(Label);
	label->set_text(tr("Attributes management"));

	toolbar->add_child(label);
	toolbar->add_child(tag_select);

	add_child(toolbar);

	selected_tags_tree = memnew(TagTree);
	selected_tags_tree->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	selected_tags_tree->set_custom_minimum_size(Size2(0, 500));
	selected_tags_tree->set_h_size_flags(Control::SIZE_EXPAND_FILL);
	selected_tags_tree->set_tag_dictionary(tag_dictionary);
	selected_tags_tree->set_v_size_flags(Control::SIZE_EXPAND_FILL);

	TagManager::get_singleton()->connect("dictionaries_loaded", Callable(this, "render"));
	AttributeManager::get_singleton()->connect("attributes_changed", Callable(this, "_handle_attributes_changed"));
	AttributeManager::get_singleton()->load_attributes();

	add_child(selected_tags_tree);
}

void GGSAttributeMainScene::_handle_dictionary_selected(int p_item_index)
{
	TypedArray<TagDictionary> *items = TagManager::get_singleton()->dictionaries;
	Variant variant = items->operator[](p_item_index);
	TagDictionary *tag_dictionary = cast_to<TagDictionary>(variant);

	if (tag_dictionary != nullptr)
	{
		selected_tags_tree->set_tag_dictionary(tag_dictionary);
		selected_tags_tree->render();

		AttributeProjectSettings::set_attribute_resource_path(tag_dictionary->get_path());
		AttributeManager::get_singleton()->set_tag_dictionary(tag_dictionary);
		AttributeManager::get_singleton()->set_attributes(tag_dictionary->get_tags());
	}
}

void GGSAttributeMainScene::render()
{
	TypedArray<TagDictionary> *items = TagManager::get_singleton()->dictionaries;
	String current_value = AttributeProjectSettings::get_attribute_resource_path();

	int preselect_index = -1;
	int size = items->size();

	tag_select->clear();

	for (int i = 0; i < size; i++)
	{
		Variant item = items->operator[](i);
		TagDictionary *tag_dictionary = cast_to<TagDictionary>(item);

		tag_select->add_item(tag_dictionary->get_path());

		if (tag_dictionary->get_path() == current_value)
		{
			preselect_index = i;
		}
	}

	tag_select->set_visible(size > 0);
	tag_select->select(preselect_index);

	if (preselect_index >= 0)
	{
		_handle_dictionary_selected(preselect_index);
	}
}
