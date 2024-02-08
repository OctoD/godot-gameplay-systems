#include "ggs_item_pool_scene.h"

#include "resource_manager/resource_manager.h"
#include "system/item/items_pool.h"

#include <godot_cpp/classes/h_box_container.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/editor_interface.hpp>
#include <godot_cpp/classes/h_separator.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/scroll_container.hpp>

using namespace ggs;
using namespace ggs::editor_plugin;

void ItemPoolScene::_handle_add_button_pressed()
{
	new_resource_modal->set_size(get_size() / 2);
	new_resource_modal->popup_centered();
}

void ItemPoolScene::_handle_cell_selected()
{
	TreeItem *selected_item = item_pool_tree->get_selected();
	ResourceManager *resource_manager = ResourceManager::get_singleton();
	TypedArray<ItemsPool> pools = resource_manager->get_items_pool_resources();
	int index = selected_item->get_index();

	if (index < 0 || index > pools.size())
	{
		return;
	}

	Variant v = pools[index];
	Ref<Resource> pool = cast_to<Resource>(v);
	EditorInterface::get_singleton()->edit_resource(pool);

	Callable callable = Callable(this, "_handle_resource_pool_changed").bind(index);

	if (!pool->is_connected("changed", callable))
	{
		pool->connect("changed", callable, ConnectFlags::CONNECT_DEFERRED);
	}
}

void ItemPoolScene::_handle_create_requested(String p_resource_name)
{
	ResourceManager *resource_manager = ResourceManager::get_singleton();

	resource_manager->create_items_pool_resource(p_resource_name);
	resource_manager->save_resource(resource_manager->create_items_pool_resource(p_resource_name));

	render_tree();

	new_resource_modal->hide();
}

void ItemPoolScene::_handle_resource_pool_changed(int p_item_pool_index)
{
	TreeItem *item = item_pool_tree->get_selected();

	if (p_item_pool_index < 0 || p_item_pool_index >= item->get_index())
	{
		return;
	}

	TypedArray<ItemsPool> pools = ResourceManager::get_singleton()->get_items_pool_resources();

	if (p_item_pool_index < 0 || p_item_pool_index >= pools.size())
	{
		return;
	}

	Variant v = pools[p_item_pool_index];
	ItemsPool *pool = cast_to<ItemsPool>(v);

	if (pool)
	{
		item->set_text(1, String::num_int64(pool->get_items().size()));
	}
}

void ItemPoolScene::_handle_tree_button_pressed(TreeItem *p_item, int p_column, int p_id, int p_mouse_button_index)
{
	if (p_id == TreeButtonId::DELETE)
	{
		ResourceManager *resource_manager = ResourceManager::get_singleton();
		TypedArray<ItemsPool> pools = resource_manager->get_items_pool_resources();

		ItemsPool *pool = nullptr;

		for (int i = 0; i < pools.size(); i++)
		{
			ItemsPool *pool_ptr = cast_to<ItemsPool>(pools[i]);

			if (pool_ptr && pool_ptr->get_pool_name() == p_item->get_text(0))
			{
				pool = pool_ptr;
				break;
			}
		}

		if (pool)
		{
			resource_manager->remove_resource(pool);
			render_tree();
		}
	}
}

void ItemPoolScene::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("_handle_add_button_pressed"), &ItemPoolScene::_handle_add_button_pressed);
	ClassDB::bind_method(D_METHOD("_handle_cell_selected"), &ItemPoolScene::_handle_cell_selected);
	ClassDB::bind_method(D_METHOD("_handle_create_requested", "p_resource_name"), &ItemPoolScene::_handle_create_requested);
	ClassDB::bind_method(D_METHOD("_handle_resource_pool_changed", "p_item_pool_index"), &ItemPoolScene::_handle_resource_pool_changed);
	ClassDB::bind_method(D_METHOD("_handle_tree_button_pressed", "p_item", "p_column", "p_id", "p_mouse_button_index"), &ItemPoolScene::_handle_tree_button_pressed);
	ClassDB::bind_method(D_METHOD("render_tree"), &ItemPoolScene::render_tree);
}

void ItemPoolScene::render_tree()
{
	item_pool_tree->clear();

	TypedArray<ItemsPool> pools = ResourceManager::get_singleton()->get_items_pool_resources();
	TreeItem *root = item_pool_tree->create_item();

	for (int i = 0; i < pools.size(); i++)
	{
		ItemsPool *pool_ptr = cast_to<ItemsPool>(pools[i]);
		TreeItem *item = root->create_child();

		item->set_text(0, pool_ptr->get_pool_name());
		item->set_text(1, String::num_int64(pool_ptr->get_items().size()));
		item->set_text_alignment(1, HorizontalAlignment::HORIZONTAL_ALIGNMENT_CENTER);
		item->add_button(2, get_theme_icon("Remove", "EditorIcons"), TreeButtonId::DELETE);
	}
}

void ItemPoolScene::_ready()
{
	set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	set_h_size_flags(SIZE_EXPAND_FILL);
	set_v_size_flags(SIZE_EXPAND_FILL);

	item_pool_tree = memnew(Tree);
	item_pool_tree->connect("button_clicked", Callable(this, "_handle_tree_button_pressed"));
	item_pool_tree->connect("cell_selected", Callable(this, "_handle_cell_selected"));
	item_pool_tree->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	item_pool_tree->set_columns(3);
	item_pool_tree->set_column_title(0, "Name");
	item_pool_tree->set_column_title(1, "Items stored");
	item_pool_tree->set_column_title_alignment(1, HorizontalAlignment::HORIZONTAL_ALIGNMENT_CENTER);
	item_pool_tree->set_column_titles_visible(true);
	item_pool_tree->set_hide_root(true);
	item_pool_tree->set_h_size_flags(SIZE_EXPAND_FILL);
	item_pool_tree->set_v_size_flags(SIZE_EXPAND_FILL);

	Label *item_pool_label = memnew(Label);
	item_pool_label->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	item_pool_label->set_h_size_flags(SIZE_EXPAND_FILL);
	item_pool_label->set_text("Items pools");

	Button *refresh_button = memnew(Button);
	refresh_button->connect("pressed", Callable(this, "render_tree"));
	refresh_button->set_button_icon(get_theme_icon("Reload", "EditorIcons"));
	refresh_button->set_text(tr("Refresh"));

	Button *add_button = memnew(Button);
	add_button->connect("pressed", Callable(this, "_handle_add_button_pressed"));
	add_button->set_button_icon(get_theme_icon("Add", "EditorIcons"));
	add_button->set_text(tr("Add items pool"));

	HSeparator *separator = memnew(HSeparator);
	separator->set_custom_minimum_size(Size2(4, 8));

	HBoxContainer *header = memnew(HBoxContainer);
	header->add_child(item_pool_label);
	header->add_child(refresh_button);
	header->add_child(separator);
	header->add_child(add_button);
	header->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	header->set_h_size_flags(SIZE_EXPAND_FILL);

	add_child(header);

	ScrollContainer *scroll_container = memnew(ScrollContainer);
	scroll_container->set_anchors_and_offsets_preset(PRESET_FULL_RECT);
	scroll_container->set_h_size_flags(SIZE_EXPAND_FILL);
	scroll_container->set_v_size_flags(SIZE_EXPAND_FILL);
	scroll_container->add_child(item_pool_tree);

	add_child(scroll_container);

	render_tree();

	new_resource_modal = memnew(NewResourceModal);
	new_resource_modal->connect("create_requested", Callable(this, "_handle_create_requested"));

	add_child(new_resource_modal);
}
