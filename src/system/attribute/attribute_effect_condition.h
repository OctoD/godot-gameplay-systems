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
		/// @brief Returns whether or not this attribute effect condition is met.
		/// @param p_attribute The attribute to apply the effect to.
		/// @param p_attribute_effect The attribute effect to apply.
		/// @param p_attribute_container The attribute container to apply the effect to.
		/// @return
		virtual bool should_apply(Attribute *p_attribute, AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container);
	};
}
#endif
