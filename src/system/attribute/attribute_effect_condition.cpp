#include "attribute_effect_condition.h"

using namespace ggs;

void AttributeEffectCondition::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("should_apply", "attribute", "attribute_effect", "attribute_container"), &AttributeEffectCondition::should_apply);
}

bool AttributeEffectCondition::should_apply(Attribute *p_attribute, AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container)
{
    return false;
}
