#ifndef GGS_ATTRIBUTE_MAIN_SCENE_H
#define GGS_ATTRIBUTE_MAIN_SCENE_H

#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/option_button.hpp>
#include <godot_cpp/classes/v_box_container.hpp>
#include <godot_cpp/classes/tree.hpp>

#include "system/tag/tag_dictionary.h"
#include "system/tag/tag_tree.h"

using namespace godot;
using namespace ggs;

namespace ggs::editor_plugin
{
	class AttributeMainScene : public VBoxContainer
	{
		GDCLASS(AttributeMainScene, VBoxContainer)

	protected:
		static void _bind_methods();

		OptionButton *tag_select;
		TagDictionary *tag_dictionary;
		TagTree *selected_tags_tree;

	public:
		AttributeMainScene();
		~AttributeMainScene();

		void _ready() override;
        void _handle_dictionary_selected(int p_item_index);
        void render();
	};
}

#endif