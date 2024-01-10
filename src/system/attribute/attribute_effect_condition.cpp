#include "attribute_effect_condition.h"

using namespace ggs;

void AttributeEffectCondition::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("get_break_type", "attribute_effect", "attribute_container"), &AttributeEffectCondition::get_break_type);
	ClassDB::bind_method(D_METHOD("should_apply_effect", "attribute_effect", "attribute_container"), &AttributeEffectCondition::should_apply_effect);
}

AttributeEffectCondition::BreakType AttributeEffectCondition::get_break_type(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container)
{
	if (p_attribute_container == nullptr || p_attribute_effect == nullptr)
	{	
		return BreakType::BREAK;
	}

	if (!p_attribute_container->has_attribute(p_attribute_effect->get_affected_attribute()))
	{
		return BreakType::BREAK_REMOVE_ATTRIBUTE_EFFECT;
	}
	
    return BreakType::NO_BREAK;
}

bool AttributeEffectCondition::should_apply_effect(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container)
{
	if (p_attribute_container == nullptr || p_attribute_effect == nullptr)
	{
		return false;
	}

	return p_attribute_container->has_attribute(p_attribute_effect->get_affected_attribute());
}

