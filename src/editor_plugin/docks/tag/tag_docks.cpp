#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/editor_selection.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

#include "tag_docks.h"
#include "system/attribute/attribute_manager.h"
#include "system/tag/tag_tree.h"
#include "system/tag/tag_manager.h"

using namespace ggs;

GGSTagDocks::GGSTagDocks()
{
}

GGSTagDocks::~GGSTagDocks()
{
}

void GGSTagDocks::_ready()
{
	/// the hardest part:
	set_name("Tag Manager");
	set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);

	EditorInterface::get_singleton()->get_selection()->connect("selection_changed", Callable(this, "_on_selection_changed"));

	Label *label = memnew(Label);
	label->set_text("Tags");

	tag_trees_container = memnew(VBoxContainer);
	tag_trees_container->set_anchors_and_offsets_preset(Control::PRESET_FULL_RECT);

	add_child(label);
	add_child(tag_trees_container);
	render();
}

void GGSTagDocks::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_on_selection_changed"), &GGSTagDocks::_on_selection_changed);
	ClassDB::bind_method(D_METHOD("_handle_tags_deselected"), &GGSTagDocks::_handle_tags_deselected);
	ClassDB::bind_method(D_METHOD("_handle_tags_selected"), &GGSTagDocks::_handle_tags_selected);
}

void GGSTagDocks::render()
{
	for (int i = 0; i < tag_trees_container->get_child_count(); i++)
	{
		tag_trees_container->get_child(i)->queue_free();
	}

	TypedArray<Node> selected_nodes = EditorInterface::get_singleton()->get_selection()->get_selected_nodes();
	TagDictionary *all_tags = memnew(TagDictionary);
	AttributeManager *attribute_manager = AttributeManager::get_singleton();

	all_tags->from_many(TagManager::get_singleton()->dictionaries);
	all_tags->remove_tags(attribute_manager->get_attributes());

	for (int i = 0; i < selected_nodes.size(); i++)
	{
		Variant v = selected_nodes[i];
		Node *node = cast_to<Node>(v);

		tag_trees_container->add_child(render_node_tags(node, all_tags));
	}
}

VBoxContainer *GGSTagDocks::render_node_tags(Node *p_node, TagDictionary *p_all_tags)
{
	VBoxContainer *container = memnew(VBoxContainer);
	PackedStringArray tags_used_by = TagManager::get_singleton()->get_tags(p_node);
	Label *selected_node_name_label = memnew(Label);
	TagTree *tree = memnew(TagTree);

	selected_node_name_label->set_text(p_node->get_name());

	tree->select_many(tags_used_by);
	tree->set_can_be_checked(true);
	tree->set_custom_minimum_size(Size2(0, 300));
	tree->set_tag_dictionary(p_all_tags);
	tree->connect("tags_deselected", Callable(this, "_handle_tags_deselected"));
	tree->connect("tags_selected", Callable(this, "_handle_tags_selected"));

	container->add_child(selected_node_name_label);
	container->add_child(tree);

	container->set_anchors_preset(Control::PRESET_TOP_WIDE);

	return container;
}

void GGSTagDocks::_handle_tags_deselected(PackedStringArray p_tags)
{
	_set_tags_selected(p_tags, false);
}

void GGSTagDocks::_handle_tags_selected(PackedStringArray p_tags)
{
	_set_tags_selected(p_tags, true);
}

void GGSTagDocks::_on_selection_changed()
{
	render();
}

void GGSTagDocks::_set_tags_selected(PackedStringArray p_tags, bool selected)
{
	TypedArray<Node> selected_nodes = EditorInterface::get_singleton()->get_selection()->get_selected_nodes();
	EditorInterface *editor_interface = EditorInterface::get_singleton();

	for (int i = 0; i < selected_nodes.size(); i++)
	{
		Variant v = selected_nodes[i];
		Node *node = cast_to<Node>(v);

		if (selected)
		{
			TagManager::get_singleton()->add_tags(node, p_tags);
		}
		else
		{
			TagManager::get_singleton()->remove_tags(node, p_tags);
		}
	}

	editor_interface->save_scene();
}

void GGSTagDocks::_handle_check_propagated_to_item(TreeItem *p_tree_item, int column)
{
	WARN_PRINT("GGSTagDocks::_handle_check_propagated_to_item() is not implemented yet.");
}