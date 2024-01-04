#ifndef GGS_TAG_DOCKS_H
#define GGS_TAG_DOCKS_H

#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/tree_item.hpp>

#include "system/tag/tag_dictionary.h"

using namespace godot;

namespace ggs
{
	class GGSTagDocks : public VBoxContainer
	{
		GDCLASS(GGSTagDocks, VBoxContainer);

	public:
		GGSTagDocks();
		~GGSTagDocks();

		void _ready() override;

	protected:
		static void _bind_methods();

	private:
		void render();
		VBoxContainer *tag_trees_container;
		VBoxContainer *render_node_tags(Node *p_node, TagDictionary *p_all_tags);
		void _handle_tags_deselected(PackedStringArray p_tags);
		void _handle_tags_selected(PackedStringArray p_tags);
		void _on_selection_changed();
		void _set_tags_selected(PackedStringArray p_tags, bool selected);
		void _handle_check_propagated_to_item(TreeItem *p_tree_item, int column);
	};
}

#endif