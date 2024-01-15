#include "attribute_container_inspector_editor.h"
#include "system/attribute/attribute_manager.h"

using namespace ggs;
using namespace ggs::editor_plugin;

void AttributeContainerInspectorEditor::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_handle_item_edited"), &AttributeContainerInspectorEditor::_handle_item_edited);
	ClassDB::bind_method(D_METHOD("_handle_dictionary_changed", "previous", "current"), &AttributeContainerInspectorEditor::_handle_dictionary_changed);
}

void AttributeContainerInspectorEditor::_handle_item_edited()
{
	TreeItem *item = get_edited();

	if (item != nullptr)
	{
		Ref<Attribute> attribute = attribute_container->get_attribute(item->get_text(0));

		ERR_FAIL_COND_MSG(attribute == nullptr, "Attribute \"" + item->get_text(0) + "\" not found, this is a bug so please report it. https://github.com/octoD/godot-gameplay-systems/issues/new?title=%5Bbug%5D%20attribute-container%20+%20GGSAttributeContainerInspectorEditor::_handle_item_edited");

		if (attribute != nullptr)
		{
			attribute->set_initial_value(item->get_text(1).to_float());
			attribute->set_min_value(item->get_text(2).to_float());
			attribute->set_max_value(item->get_text(3).to_float());
		}
	}
}

void AttributeContainerInspectorEditor::_handle_dictionary_changed(TagDictionary *previous, TagDictionary *current)
{
	clear();
	_ready();
}

void AttributeContainerInspectorEditor::_ready()
{
	if (attribute_container == nullptr)
	{
		return;
	}

	TypedArray<Attribute> attributes = attribute_container->get_attributes();

	if (!AttributeManager::get_singleton()->is_connected("attributes_dictionary_changed", Callable(this, "_handle_dictionary_changed")))
	{
		AttributeManager::get_singleton()->connect("attributes_dictionary_changed", Callable(this, "_handle_dictionary_changed"));
	}

	attribute_container->ensure_attributes(AttributeManager::get_singleton()->get_attributes());

	connect("item_edited", Callable(this, "_handle_item_edited"));

	set_columns(4);
	set_hide_root(true);

	set_column_title_alignment(0, HorizontalAlignment::HORIZONTAL_ALIGNMENT_LEFT);
	set_column_title_alignment(1, HorizontalAlignment::HORIZONTAL_ALIGNMENT_RIGHT);
	set_column_title_alignment(2, HorizontalAlignment::HORIZONTAL_ALIGNMENT_RIGHT);
	set_column_title_alignment(3, HorizontalAlignment::HORIZONTAL_ALIGNMENT_RIGHT);
	set_column_title(0, tr("Tag Name"));
	set_column_title(1, tr("Initial Value"));
	set_column_title(2, tr("Minimum Value"));
	set_column_title(3, tr("Maximum Value"));
	set_column_titles_visible(true);
	set_custom_minimum_size(Size2(0, 400));

	for (int i = 0; i < attributes.size(); i++)
	{
		Variant attribute_variant = attributes[i];
		Attribute *attribute = cast_to<Attribute>(attribute_variant);

		if (attribute != nullptr)
		{
			TreeItem *item = create_item();

			item->set_editable(0, false);
			item->set_editable(1, true);
			item->set_editable(2, true);
			item->set_editable(3, true);
			item->set_text_alignment(0, HorizontalAlignment::HORIZONTAL_ALIGNMENT_LEFT);
			item->set_text_alignment(1, HorizontalAlignment::HORIZONTAL_ALIGNMENT_RIGHT);
			item->set_text_alignment(2, HorizontalAlignment::HORIZONTAL_ALIGNMENT_RIGHT);
			item->set_text_alignment(3, HorizontalAlignment::HORIZONTAL_ALIGNMENT_RIGHT);
			item->set_text(0, attribute->get_tag_name());
			item->set_text(1, String::num(attribute->get_initial_value()));
			item->set_text(2, String::num(attribute->get_min_value()));
			item->set_text(3, String::num(attribute->get_max_value()));
		}
	}
}

void AttributeContainerInspectorEditor::set_attribute_container(AttributeContainer *p_attribute_container)
{
	attribute_container = p_attribute_container;
}
