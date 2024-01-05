#include "gameplay_effect.h"

using namespace ggs;

void GameplayEffect::_bind_methods()
{
    /// binds methods
    ClassDB::bind_method(D_METHOD("get_attribute_effects_applied"), &GameplayEffect::get_attribute_effects_applied);
    ClassDB::bind_method(D_METHOD("get_stacking_behaviors"), &GameplayEffect::get_stacking_behaviors);
    ClassDB::bind_method(D_METHOD("set_attribute_effects_applied", "attribute_effects_applied"), &GameplayEffect::set_attribute_effects_applied);
    ClassDB::bind_method(D_METHOD("set_stacking_behaviors", "stacking_behaviors"), &GameplayEffect::set_stacking_behaviors);
    
    /// property bindings
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "attribute_effects_applied", PROPERTY_HINT_NONE, "17/17:AttributeEffect", PROPERTY_USAGE_DEFAULT, "AttributeEffect"), "set_attribute_effects_applied", "get_attribute_effects_applied");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "stacking_behaviors", PROPERTY_HINT_NONE, "17/17:GameplayEffectStackingBehavior", PROPERTY_USAGE_DEFAULT, "GameplayEffectStackingBehavior"), "set_stacking_behaviors", "get_stacking_behaviors");
}

GameplayEffect::GameplayEffect()
{
    attribute_effects_applied = TypedArray<AttributeEffect>();
    stacking_behaviors = TypedArray<GameplayEffectStackingBehavior>();
}

GameplayEffect::~GameplayEffect()
{
}

TypedArray<AttributeEffect> GameplayEffect::get_attribute_effects_applied() const
{
    return attribute_effects_applied;
}

TypedArray<GameplayEffectStackingBehavior> GameplayEffect::get_stacking_behaviors() const
{
    return stacking_behaviors;
}

void GameplayEffect::set_attribute_effects_applied(TypedArray<AttributeEffect> p_attribute_effects_applied)
{
    attribute_effects_applied = p_attribute_effects_applied;
}

void GameplayEffect::set_stacking_behaviors(TypedArray<GameplayEffectStackingBehavior> p_stacking_behaviors)
{
    stacking_behaviors = p_stacking_behaviors;
}
