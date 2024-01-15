#ifndef GGS_ABILITY_INSPECTOR_PLUGIN_EDITOR_H
#define GGS_ABILITY_INSPECTOR_PLUGIN_EDITOR_H

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include "system/ability/ability.h"
#include "system/tag/tag_tree.h"

using namespace godot;

namespace ggs::editor_plugin
{
	class AbilityInspectorPluginEditor : public VBoxContainer
	{
		GDCLASS(AbilityInspectorPluginEditor, VBoxContainer);

	private:
		void _handle_button_pressed();
		void _handle_tags_deselected(const PackedStringArray &p_tags);
		void _handle_tags_selected(const PackedStringArray &p_tags);

	protected:
		/// @brief Bindings for Godot.
		static void _bind_methods();
		/// @brief The ability that is being edited.
		Ability *ability;
		/// @brief The name of the property that is being edited.
		int property_name;
		/// @brief Gets the name of the property that is being edited.
		/// @return The name of the property that is being edited.
		String get_label_name() const;
		/// @brief Returns the ability's tags that are being edited.
		/// @return The ability's tags that are being edited.
		PackedStringArray get_edited_tags() const;
		/// @brief Sets the ability's tags that are being edited.
		/// @param p_tags The ability's tags that are being edited.
		void set_edited_tags(const PackedStringArray &p_tags);
		/// @brief The button that expands or collapses the tag tree.
		Button *button;
		/// @brief The tag tree.
		TagTree *tag_tree;

	public:
		/// @brief The properties that can be edited.
		enum EditedProperty
		{
			TAGS_ADDED_ON_COOLDOWN_END,
			TAGS_ADDED_ON_COOLDOWN_START,
			TAGS_ADDED_ON_GRANT,
			TAGS_ADDED_ON_ACTIVATION,
			TAGS_REMOVED_ON_COOLDOWN_END,
			TAGS_REMOVED_ON_COOLDOWN_START,
			TAGS_REMOVED_ON_ACTIVATION,
			TAGS_REMOVED_ON_BLOCK,
			TAGS_REMOVED_ON_CANCEL,
			TAGS_REQUIRED_TO_ACTIVATE,
			TAGS_REQUIRED_TO_BLOCK,
			TAGS_REQUIRED_TO_CANCEL,
			TAGS_REQUIRED_TO_GRANT,
		};

		void _ready() override;
		/// @brief Sets the ability that is being edited.
		/// @param ability The ability that is being edited.
		void set_ability(Ability *p_ability);
		/// @brief Sets the name of the property that is being edited.
		/// @param property_name The name of the property that is being edited.
		void set_edited_property(const EditedProperty &p_property_name);
	};
}

VARIANT_ENUM_CAST(ggs::editor_plugin::AbilityInspectorPluginEditor::EditedProperty);

#endif
