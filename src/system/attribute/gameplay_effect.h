#ifndef GGS_GAMEPLAY_EFFECT_H
#define GGS_GAMEPLAY_EFFECT_H

#include <godot_cpp/classes/node.hpp>

#include "attribute_container.h"
#include "attribute_effect.h"
#include "gameplay_effect_stacking_behavior.h"

using namespace godot;

namespace ggs
{
	class AttributeContainer;
	class AttributeEffect;
	class GameplayEffectStackingBehavior;

	class GameplayEffect : public Node
	{
		GDCLASS(GameplayEffect, Node);

	protected:
		static void _bind_methods();

		/// @brief The attributes affected by this gameplay effect.
		TypedArray<AttributeEffect> attribute_effects_applied;
		/// @brief The stacking behaviors of this gameplay effect.
		TypedArray<GameplayEffectStackingBehavior> stacking_behaviors;

	public:
		GameplayEffect();
		~GameplayEffect();

		/// @brief Returns the attributes effects applied by this gameplay effect.
		/// @return The attributes effects applied by this gameplay effect.
		TypedArray<AttributeEffect> get_attribute_effects_applied() const;
		/// @brief Returns the stacking behaviors of this gameplay effect.
		/// @return The stacking behaviors of this gameplay effect.
		TypedArray<GameplayEffectStackingBehavior> get_stacking_behaviors() const;
		/// @brief Sets the attributes affected by this gameplay effect.
		/// @param p_attribute_effects_applied The attributes affected by this gameplay effect.
		void set_attribute_effects_applied(TypedArray<AttributeEffect> p_attribute_effects_applied);
		/// @brief Sets the stacking behaviors of this gameplay effect.
		/// @param p_stacking_behaviors The stacking behaviors of this gameplay effect.
		void set_stacking_behaviors(TypedArray<GameplayEffectStackingBehavior> p_stacking_behaviors);
	};
}

#endif
