#ifndef GGSE_GAMEPLAY_EFFECT_STACKING_BEHAVIOR_H
#define GGSE_GAMEPLAY_EFFECT_STACKING_BEHAVIOR_H

#include <godot_cpp/classes/resource.hpp>

#include "attribute_container.h"
#include "attribute_effect.h"

using namespace godot;

namespace ggs
{
	class AttributeEffect;
	class AttributeContainer;

	class GameplayEffectStackingBehavior : public Resource
	{
		GDCLASS(GameplayEffectStackingBehavior, Resource);

	protected:
		static void _bind_methods();

	public:
		/// @brief Determines how the given attribute effect should stack with the given attribute container.
		/// @param p_attribute_effect The attribute effect to stack.
		/// @param p_attribute_container The attribute container to stack.
		virtual void apply_stack(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container) const;
		/// @brief Returns whether or not the given attribute effect can stack with the given attribute container.
		/// @param p_attribute_effect The attribute effect to check.
		/// @param p_attribute_container The attribute container to check.
		/// @return True if the given attribute effect can stack with the given attribute container, false otherwise.
		virtual bool can_stack(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container) const;
	};
}

#endif
