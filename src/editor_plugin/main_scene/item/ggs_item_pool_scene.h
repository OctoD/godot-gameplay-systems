#ifndef GGS_ITEM_POOL_SCENE_H
#define GGS_ITEM_POOL_SCENE_H

#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/tree.hpp>

#include "editor_plugin/main_scene/ggs_new_resource_modal.h"
#include "system/item/items_pool.h"

using namespace godot;

namespace ggs::editor_plugin
{
	class ItemPoolScene : public VBoxContainer
	{
		GDCLASS(ItemPoolScene, VBoxContainer);

	private:
		enum TreeButtonId
		{
			DELETE = 0,
		};
	
		void _handle_add_button_pressed();
		void _handle_create_requested(String p_resource_name);
		void _handle_tree_button_pressed(TreeItem *p_item, int p_column, int p_id, int p_mouse_button_index);

	protected:
		static void _bind_methods();

		NewResourceModal *new_resource_modal;
		Tree *item_pool_tree;

		void render_tree();

	public:
		void _ready() override;
	};
}

#endif // GGS_ITEM_POOL_SCENE_H
