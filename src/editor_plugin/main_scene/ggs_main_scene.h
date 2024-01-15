#ifndef GGS_MAIN_SCENE_H
#define GGS_MAIN_SCENE_H

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/tab_container.hpp>

using namespace godot;

namespace ggs::editor_plugin
{
	class MainScene : public Control
	{
		enum GGSMainSceneTab
		{
			ABILITY,
			ATTRIBUTES,
			TAG_MANAGER,
		};

		GDCLASS(MainScene, Control);

	public:
		MainScene();
		~MainScene();

		void _ready() override;

	protected:
		static void _bind_methods();
		TabContainer *tab_container;
		Panel *ability_panel;
		Panel *attributes_panel;
		Panel *tag_manager_panel;
	};
}

#endif