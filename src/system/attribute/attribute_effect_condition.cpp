#include "attribute_effect_condition.h"

using namespace ggs;

void AttributeEffectCondition::_bind_methods()
{
	/// TODO: these will stay commented out until godot-cpp supports virtual methods properly.
	// ClassDB::bind_method(D_METHOD("get_break_type", "attribute_effect", "attribute_container"), &AttributeEffectCondition::get_break_type);
	// ClassDB::bind_method(D_METHOD("should_apply_effect", "attribute_effect", "attribute_container"), &AttributeEffectCondition::should_apply_effect);

	BIND_ENUM_CONSTANT(NO_BREAK);
	BIND_ENUM_CONSTANT(BREAK);
	BIND_ENUM_CONSTANT(BREAK_REMOVE_ATTRIBUTE_EFFECT);
	BIND_ENUM_CONSTANT(BREAK_REMOVE_ATTRIBUTE_EFFECT_OF_THIS_TYPE);
	BIND_ENUM_CONSTANT(BREAK_REMOVE_ANY_ATTRIBUTE_EFFECT);
}

AttributeEffectCondition::BreakType AttributeEffectCondition::_get_break_type(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container)
{
	if (p_attribute_container == nullptr || p_attribute_effect == nullptr)
	{
		return BreakType::BREAK;
	}

	if (!p_attribute_container->has_attribute(p_attribute_effect->get_affected_attribute()))
	{
		return BreakType::BREAK_REMOVE_ATTRIBUTE_EFFECT;
	}

	if (has_method("get_break_type"))
	{
		int i_return_value = call("get_break_type", p_attribute_effect, p_attribute_container);
		return (BreakType)i_return_value;
	}

	return BreakType::NO_BREAK;
}

bool AttributeEffectCondition::_should_apply_effect(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container)
{
	if (p_attribute_container == nullptr || p_attribute_effect == nullptr)
	{
		return false;
	}

	if (!p_attribute_container->has_attribute(p_attribute_effect->get_affected_attribute()))
	{
		return false;
	}

	if (has_method("should_apply_effect"))
	{
		return call("should_apply_effect", p_attribute_effect, p_attribute_container);
	}

	return true;
}
