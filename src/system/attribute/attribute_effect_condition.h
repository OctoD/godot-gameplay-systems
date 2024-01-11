#ifndef GGS_ATTRIBUTE_EFFECT_CONDITION_H
#define GGS_ATTRIBUTE_EFFECT_CONDITION_H

#include <godot_cpp/classes/resource.hpp>

#include "attribute_container.h"
#include "attribute_effect.h"
#include "attribute.h"

using namespace godot;

namespace ggs
{

	class Attribute;
	class AttributeContainer;
	class AttributeEffect;

	class AttributeEffectCondition : public Resource
	{
		GDCLASS(AttributeEffectCondition, Resource);

	protected:
		static void _bind_methods();

	public:
		enum BreakType
		{
			NO_BREAK,
			BREAK,
			BREAK_REMOVE_ATTRIBUTE_EFFECT,
			BREAK_REMOVE_ATTRIBUTE_EFFECT_OF_THIS_TYPE,
			BREAK_REMOVE_ANY_ATTRIBUTE_EFFECT,
		};

		/// @brief Gets the break type of this attribute effect condition.
		/// @param p_attribute_effect The attribute effect to apply.
		/// @param p_attribute_container The attribute container to apply the effect to.
		/// @return The break type of this attribute effect condition.
		virtual AttributeEffectCondition::BreakType _get_break_type(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container);
		/// @brief Returns whether or not this attribute effect condition is met.
		/// @param p_attribute_effect The attribute effect to apply.
		/// @param p_attribute_container The attribute container to apply the effect to.
		/// @return
		virtual bool _should_apply_effect(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container);
	};
}

VARIANT_ENUM_CAST(ggs::AttributeEffectCondition::BreakType);

#endif
