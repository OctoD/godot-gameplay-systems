#include "attribute_effect.h"

using namespace ggs;

void AttributeEffect::_bind_methods()
{
    /// binds methods
    ClassDB::bind_method(D_METHOD("get_affected_amount"), &AttributeEffect::get_affected_amount);
    ClassDB::bind_method(D_METHOD("get_affected_attribute"), &AttributeEffect::get_affected_attribute);
    ClassDB::bind_method(D_METHOD("get_application_type"), &AttributeEffect::get_application_type);
    ClassDB::bind_method(D_METHOD("get_applications_count"), &AttributeEffect::get_applications_count);
    ClassDB::bind_method(D_METHOD("get_applications"), &AttributeEffect::get_applications);
    ClassDB::bind_method(D_METHOD("get_conditions"), &AttributeEffect::get_conditions);
    ClassDB::bind_method(D_METHOD("get_duration"), &AttributeEffect::get_duration);
    ClassDB::bind_method(D_METHOD("get_life_cycle"), &AttributeEffect::get_life_cycle);
    ClassDB::bind_method(D_METHOD("set_affected_amount", "affected_amount"), &AttributeEffect::set_affected_amount);
    ClassDB::bind_method(D_METHOD("set_affected_attribute", "affected_attribute"), &AttributeEffect::set_affected_attribute);
    ClassDB::bind_method(D_METHOD("set_application_type", "application_type"), &AttributeEffect::set_application_type);
    ClassDB::bind_method(D_METHOD("set_conditions", "conditions"), &AttributeEffect::set_conditions);
    ClassDB::bind_method(D_METHOD("set_duration", "duration"), &AttributeEffect::set_duration);
    ClassDB::bind_method(D_METHOD("set_life_cycle", "life_cycle"), &AttributeEffect::set_life_cycle);
    ClassDB::bind_method(D_METHOD("should_apply", "attribute_effect", "attribute_container"), &AttributeEffect::should_apply);

    /// binds properties
    ADD_PROPERTY(PropertyInfo(Variant::INT, "application_type", PROPERTY_HINT_ENUM, "Instant,Time scaled"), "set_application_type", "get_application_type");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "affected_amount"), "set_affected_amount", "get_affected_amount");
    ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "affected_attribute"), "set_affected_attribute", "get_affected_attribute");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "duration", PROPERTY_HINT_NONE), "set_duration", "get_duration");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "life_cycle", PROPERTY_HINT_ENUM, "One time,Time based"), "set_life_cycle", "get_life_cycle");
    ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "conditions", PROPERTY_HINT_RESOURCE_TYPE, vformat("%s/%s:%s", Variant::OBJECT, PROPERTY_HINT_RESOURCE_TYPE, "AttributeEffectCondition")), "set_conditions", "get_conditions");
}

AttributeEffect::AttributeEffect()
{
    conditions = TypedArray<AttributeEffectCondition>();
    affected_amount = 0.0f;
    affected_attribute = "";
    application_type = INSTANT;
    duration = 0.0f;
    life_cycle = ONE_TIME;
}

AttributeEffect::~AttributeEffect()
{
}

PackedFloat32Array AttributeEffect::get_applications() const
{
    PackedFloat32Array applications = PackedFloat32Array();

    if (application_type == INSTANT)
    {
        applications.push_back(affected_amount);
    }
    else if (application_type == TIME_SCALED)
    {
        ERR_FAIL_COND_V(duration == 0, applications);

        // divides the affected amount by the duration and adds the remainder to the last application
        int applications_count = duration < 1.0f ? 1 : (int)duration;
        float remainder = std::fmod(affected_amount, applications_count);
        float amount_per_application = affected_amount / applications_count;

        for (int i = 0; i < applications_count; i++)
        {
            applications.push_back(amount_per_application);
        }

        applications[applications_count - 1] += remainder;

        ERR_FAIL_COND_V(applications.size() != applications_count, applications);
    }

    return applications;
}

float AttributeEffect::get_affected_amount() const
{
    return affected_amount;
}

StringName AttributeEffect::get_affected_attribute() const
{
    return affected_attribute;
}

AttributeEffect::ApplicationType AttributeEffect::get_application_type() const
{
    return (AttributeEffect::ApplicationType)application_type;
}

int AttributeEffect::get_applications_count() const
{
    if (application_type == INSTANT)
    {
        return 1;
    }
    else
    {
        return (int)duration;
    }
}

TypedArray<AttributeEffectCondition> AttributeEffect::get_conditions() const
{
    return conditions;
}

float AttributeEffect::get_duration() const
{
    return duration;
}

AttributeEffect::LifeCycle AttributeEffect::get_life_cycle() const
{
    return (AttributeEffect::LifeCycle)life_cycle;
}

void AttributeEffect::set_affected_amount(float p_affected_amount)
{
    affected_amount = p_affected_amount;
}

void AttributeEffect::set_affected_attribute(StringName p_affected_attribute)
{
    affected_attribute = p_affected_attribute;
}

void AttributeEffect::set_application_type(ApplicationType p_application_type)
{
    application_type = p_application_type;
}

void AttributeEffect::set_conditions(TypedArray<AttributeEffectCondition> p_conditions)
{
    conditions = p_conditions;
}

void AttributeEffect::set_duration(float p_duration)
{
    duration = p_duration;
}

void AttributeEffect::set_life_cycle(LifeCycle p_life_cycle)
{
    life_cycle = p_life_cycle;
}

bool AttributeEffect::should_apply(GameplayEffect *p_attribute_effect, AttributeContainer *p_attribute_container)
{
    return false;
}
