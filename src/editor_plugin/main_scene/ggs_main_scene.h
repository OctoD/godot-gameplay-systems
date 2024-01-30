#ifndef GGS_MAIN_SCENE_H
#define GGS_MAIN_SCENE_H

#include <godot_cpp/classes/v_box_container.hpp>

using namespace godot;

namespace ggs::editor_plugin
{
	class MainScene : public VBoxContainer
	{
		enum GGSMainSceneTab
		{
			ABILITY,
			ATTRIBUTES,
			TAG_MANAGER,
		};

		GDCLASS(MainScene, VBoxContainer);

	public:
		MainScene();
		~MainScene();

		void _ready() override;

	protected:
		static void _bind_methods();
	};
}

#endif