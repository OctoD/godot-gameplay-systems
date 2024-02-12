#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/label.hpp>

#include "ability_inspector_plugin_editor.h"
#include "system/attribute/attribute_manager.h"
#include "system/tag/tag_dictionary.h"
#include "system/tag/tag_tree.h"
#include "system/tag/tag_manager.h"

using namespace ggs::editor_plugin;

void AbilityInspectorPluginEditor::_handle_button_pressed()
{
	if (tag_tree->is_visible())
	{
		tag_tree->set_visible(false);
		button->set_text(tr("Expand"));
	}
	else
	{
		tag_tree->set_visible(true);
		button->set_text(tr("Collapse"));
	}
}

void AbilityInspectorPluginEditor::_handle_tags_deselected(const PackedStringArray &p_tags)
{
	set_edited_tags(p_tags);
}

void AbilityInspectorPluginEditor::_handle_tags_selected(const PackedStringArray &p_tags)
{
	set_edited_tags(p_tags);
}

void AbilityInspectorPluginEditor::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("_handle_button_pressed"), &AbilityInspectorPluginEditor::_handle_button_pressed);
	ClassDB::bind_method(D_METHOD("_handle_tags_deselected"), &AbilityInspectorPluginEditor::_handle_tags_deselected);
	ClassDB::bind_method(D_METHOD("_handle_tags_selected"), &AbilityInspectorPluginEditor::_handle_tags_selected);

	/// binds enum constants
	BIND_ENUM_CONSTANT(TAGS_ADDED_ON_COOLDOWN_END);
	BIND_ENUM_CONSTANT(TAGS_ADDED_ON_COOLDOWN_START);
	BIND_ENUM_CONSTANT(TAGS_ADDED_ON_GRANT);
	BIND_ENUM_CONSTANT(TAGS_ADDED_ON_ACTIVATION);
	BIND_ENUM_CONSTANT(TAGS_REMOVED_ON_COOLDOWN_END);
	BIND_ENUM_CONSTANT(TAGS_REMOVED_ON_COOLDOWN_START);
	BIND_ENUM_CONSTANT(TAGS_REMOVED_ON_ACTIVATION);
	BIND_ENUM_CONSTANT(TAGS_REMOVED_ON_BLOCK);
	BIND_ENUM_CONSTANT(TAGS_REMOVED_ON_CANCEL);
	BIND_ENUM_CONSTANT(TAGS_REQUIRED_TO_ACTIVATE);
	BIND_ENUM_CONSTANT(TAGS_REQUIRED_TO_BLOCK);
	BIND_ENUM_CONSTANT(TAGS_REQUIRED_TO_CANCEL);
	BIND_ENUM_CONSTANT(TAGS_REQUIRED_TO_GRANT);
}

String AbilityInspectorPluginEditor::get_label_name() const
{
	switch (property_name)
	{
	case EditedProperty::TAGS_ADDED_ON_ACTIVATION:
		return tr("Tags Added On Activation");
	case EditedProperty::TAGS_ADDED_ON_COOLDOWN_END:
		return tr("Tags Added On Cooldown End");
	case EditedProperty::TAGS_ADDED_ON_COOLDOWN_START:
		return tr("Tags Added On Cooldown Start");
	case EditedProperty::TAGS_ADDED_ON_GRANT:
		return tr("Tags Added On Grant");
	case EditedProperty::TAGS_REMOVED_ON_ACTIVATION:
		return tr("Tags Removed On Activation");
	case EditedProperty::TAGS_REMOVED_ON_BLOCK:
		return tr("Tags Removed On Block");
	case EditedProperty::TAGS_REMOVED_ON_CANCEL:
		return tr("Tags Removed On Cancel");
	case EditedProperty::TAGS_REMOVED_ON_COOLDOWN_END:
		return tr("Tags Removed On Cooldown End");
	case EditedProperty::TAGS_REMOVED_ON_COOLDOWN_START:
		return tr("Tags Removed On Cooldown Start");
	case EditedProperty::TAGS_REQUIRED_TO_ACTIVATE:
		return tr("Tags Required To Activate");
	case EditedProperty::TAGS_REQUIRED_TO_BLOCK:
		return tr("Tags Required To Block");
	case EditedProperty::TAGS_REQUIRED_TO_CANCEL:
		return tr("Tags Required To Cancel");
	case EditedProperty::TAGS_REQUIRED_TO_GRANT:
		return tr("Tags Required To Grant");
	}
	return String();
}

PackedStringArray AbilityInspectorPluginEditor::get_edited_tags() const
{
	switch (property_name)
	{
	case EditedProperty::TAGS_ADDED_ON_ACTIVATION:
		return ability->get_tags_added_on_activation();
	case EditedProperty::TAGS_ADDED_ON_COOLDOWN_END:
		return ability->get_tags_added_on_cooldown_end();
	case EditedProperty::TAGS_ADDED_ON_COOLDOWN_START:
		return ability->get_tags_added_on_cooldown_start();
	case EditedProperty::TAGS_ADDED_ON_GRANT:
		return ability->get_tags_added_on_grant();
	case EditedProperty::TAGS_REMOVED_ON_ACTIVATION:
		return ability->get_tags_removed_on_activation();
	case EditedProperty::TAGS_REMOVED_ON_BLOCK:
		return ability->get_tags_removed_on_block();
	case EditedProperty::TAGS_REMOVED_ON_CANCEL:
		return ability->get_tags_removed_on_cancel();
	case EditedProperty::TAGS_REMOVED_ON_COOLDOWN_END:
		return ability->get_tags_removed_on_cooldown_end();
	case EditedProperty::TAGS_REMOVED_ON_COOLDOWN_START:
		return ability->get_tags_removed_on_cooldown_start();
	case EditedProperty::TAGS_REQUIRED_TO_ACTIVATE:
		return ability->get_tags_required_to_activate();
	case EditedProperty::TAGS_REQUIRED_TO_BLOCK:
		return ability->get_tags_required_to_block();
	case EditedProperty::TAGS_REQUIRED_TO_CANCEL:
		return ability->get_tags_required_to_cancel();
	case EditedProperty::TAGS_REQUIRED_TO_GRANT:
		return ability->get_tags_required_to_grant();
	}

	return PackedStringArray();
}

void AbilityInspectorPluginEditor::set_edited_tags(const PackedStringArray &p_tags)
{
	switch (property_name)
	{
	case EditedProperty::TAGS_ADDED_ON_ACTIVATION:
		ability->set_tags_added_on_activation(p_tags);
		break;
	case EditedProperty::TAGS_ADDED_ON_COOLDOWN_END:
		ability->set_tags_added_on_cooldown_end(p_tags);
		break;
	case EditedProperty::TAGS_ADDED_ON_COOLDOWN_START:
		ability->set_tags_added_on_cooldown_start(p_tags);
		break;
	case EditedProperty::TAGS_ADDED_ON_GRANT:
		ability->set_tags_added_on_grant(p_tags);
		break;
	case EditedProperty::TAGS_REMOVED_ON_ACTIVATION:
		ability->set_tags_removed_on_activation(p_tags);
		break;
	case EditedProperty::TAGS_REMOVED_ON_BLOCK:
		ability->set_tags_removed_on_block(p_tags);
		break;
	case EditedProperty::TAGS_REMOVED_ON_CANCEL:
		ability->set_tags_removed_on_cancel(p_tags);
		break;
	case EditedProperty::TAGS_REMOVED_ON_COOLDOWN_END:
		ability->set_tags_removed_on_cooldown_end(p_tags);
		break;
	case EditedProperty::TAGS_REMOVED_ON_COOLDOWN_START:
		ability->set_tags_removed_on_cooldown_start(p_tags);
		break;
	case EditedProperty::TAGS_REQUIRED_TO_ACTIVATE:
		ability->set_tags_required_to_activate(p_tags);
		break;
	case EditedProperty::TAGS_REQUIRED_TO_BLOCK:
		ability->set_tags_required_to_block(p_tags);
		break;
	case EditedProperty::TAGS_REQUIRED_TO_CANCEL:
		ability->set_tags_required_to_cancel(p_tags);
		break;
	case EditedProperty::TAGS_REQUIRED_TO_GRANT:
		ability->set_tags_required_to_grant(p_tags);
		break;
	}
}

void AbilityInspectorPluginEditor::_ready()
{
	set_anchors_and_offsets_preset(PRESET_FULL_RECT);

	HBoxContainer *hbox_container = memnew(HBoxContainer);
	TagDictionary *tag_dictionary = memnew(TagDictionary);
	TagManager *tag_manager = TagManager::get_singleton();
	AttributeManager *attribute_manager = AttributeManager::get_singleton();
	Label *label = memnew(Label);

	button = memnew(Button);
	tag_tree = memnew(TagTree);

	TypedArray<TagDictionary> dictionaries = tag_manager->get_dictionaries();

	for (int i = 0; i < dictionaries.size(); i++)
	{
		Variant variant = dictionaries[i];
		TagDictionary *dictionary = cast_to<TagDictionary>(variant);

		if (dictionary != nullptr)
		{
			tag_dictionary->add_tags(dictionary->get_tags());
		}
	}

	tag_dictionary->remove_tags(attribute_manager->get_attributes());

	button->connect("pressed", Callable(this, "_handle_button_pressed"));
	button->set_text(tr("Expand"));
	hbox_container->add_child(button);
	hbox_container->add_child(label);
	hbox_container->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	label->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	label->set_text(get_label_name());
	tag_tree->connect("tags_deselected", Callable(this, "_handle_tags_deselected"));
	tag_tree->connect("tags_selected", Callable(this, "_handle_tags_selected"));
	tag_tree->select_many(get_edited_tags());
	tag_tree->set_can_be_checked(true);
	tag_tree->set_custom_minimum_size(Size2(0, 200));
	tag_tree->set_tag_dictionary(tag_dictionary);
	tag_tree->set_visible(false);

	add_child(hbox_container);
	add_child(tag_tree);
}

void AbilityInspectorPluginEditor::set_ability(Ability *p_ability)
{
	ability = p_ability;
}

void AbilityInspectorPluginEditor::set_edited_property(const EditedProperty &p_property_name)
{
	property_name = p_property_name;
}
