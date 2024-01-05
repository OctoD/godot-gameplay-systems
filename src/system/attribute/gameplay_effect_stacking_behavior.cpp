#include "gameplay_effect_stacking_behavior.h"

using namespace ggs;

void GameplayEffectStackingBehavior::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("apply_stack", "attribute_effect", "attribute_container"), &GameplayEffectStackingBehavior::apply_stack);
	ClassDB::bind_method(D_METHOD("can_stack", "attribute_effect", "attribute_container"), &GameplayEffectStackingBehavior::can_stack);
}

void GameplayEffectStackingBehavior::apply_stack(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container) const
{
}

bool GameplayEffectStackingBehavior::can_stack(AttributeEffect *p_attribute_effect, AttributeContainer *p_attribute_container) const
{
    return false;
}
