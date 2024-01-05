#ifndef GGS_ATTRIBUTE_CONTAINER_INSPECTOR_EDITOR_H
#define GGS_ATTRIBUTE_CONTAINER_INSPECTOR_EDITOR_H

#include <godot_cpp/classes/tree.hpp>

#include "system/attribute/attribute_container.h"

using namespace godot;

namespace ggs
{
	class GGSAttributeContainerInspectorEditor : public Tree
	{
		GDCLASS(GGSAttributeContainerInspectorEditor, Tree);

	private:
		AttributeContainer *attribute_container;
		void _handle_item_edited();

	protected:
		static void _bind_methods();

	public:
		void _ready() override;
		void set_attribute_container(AttributeContainer *p_attribute_container);
	};
}

#endif