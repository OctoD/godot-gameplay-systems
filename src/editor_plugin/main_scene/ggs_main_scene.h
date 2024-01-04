#ifndef GGS_MAIN_SCENE_H
#define GGS_MAIN_SCENE_H

#include <godot_cpp/classes/panel.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/tab_container.hpp>

using namespace godot;

namespace ggs
{
	class GGSMainScene : public Control
	{
		enum GGSMainSceneTab
		{
			ABILITY,
			ATTRIBUTES,
			TAG_MANAGER,
		};

		GDCLASS(GGSMainScene, Control);

	public:
		GGSMainScene();
		~GGSMainScene();

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