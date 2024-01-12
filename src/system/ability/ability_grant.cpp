#include "ability_grant.h"

using namespace ggs;

void AbilityGrant::_bind_methods()
{
    /// binds methods
    ClassDB::bind_method(D_METHOD("get_grant"), &AbilityGrant::get_grant);
    ClassDB::bind_method(D_METHOD("get_ability"), &AbilityGrant::get_ability);
    ClassDB::bind_method(D_METHOD("set_grant", "grant"), &AbilityGrant::set_grant);
    ClassDB::bind_method(D_METHOD("set_ability", "ability"), &AbilityGrant::set_ability);

    /// binds properties
    ADD_PROPERTY(PropertyInfo(Variant::BOOL, "grant"), "set_grant", "get_grant");
    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability"), "set_ability", "get_ability");
}

AbilityGrant::AbilityGrant()
{
}

AbilityGrant::~AbilityGrant()
{
}

Ref<Ability> AbilityGrant::get_ability() const
{
    return ability;
}

bool AbilityGrant::get_grant() const
{
    return granted;
}

void AbilityGrant::set_grant(bool p_grant)
{
    granted = p_grant;
}

void AbilityGrant::set_ability(Ref<Ability> p_ability)
{
    ability = p_ability;
}
