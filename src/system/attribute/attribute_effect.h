#ifndef GGS_ATTRIBUTE_EFFECT_H
#define GGS_ATTRIBUTE_EFFECT_H

#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include "attribute.h"
#include "attribute_container.h"
#include "attribute_effect_condition.h"
#include "gameplay_effect.h"

using namespace godot;

namespace ggs
{
	class AttributeEffectCondition;
	class AttributeContainer;
	class GameplayEffect;

	class AttributeEffect : public Resource
	{
		GDCLASS(AttributeEffect, Resource);

		friend class AttributeEffectCondition;

	protected:
		static void
		_bind_methods();

		/// @brief The type of application for this attribute effect.
		int application_type;
		/// @brief The amount of the attribute effect.
		float affected_amount;
		/// @brief The attribute that will be affected by this attribute effect
		StringName affected_attribute;
		/// @brief The duration of the attribute effect.
		float duration;
		/// @brief The life cycle of the attribute effect.
		int life_cycle;
		/// @brief The conditions that must be met for this attribute effect to be applied.
		TypedArray<AttributeEffectCondition> conditions;

	public:
		/// @brief Default constructor.
		AttributeEffect();
		/// @brief Default destructor.
		~AttributeEffect();

		enum ApplicationType
		{
			ADD_BUFF,
			ADD_VALUE,
			ADD_VALUE_OR_BUFF,
			SUBTRACT_BUFF,
			SUBTRACT_VALUE,
			SET_BUFF,
			SET_VALUE,
		};

		/// @brief The life cycle of the attribute effect.
		enum LifeCycle
		{
			ONE_TIME,
			TIME_BASED,
			INFINITE_TIME_BASED,
		};

		/// @brief Returns whether or not this attribute effect should be removed from the container.
		/// @param p_attribute_container The attribute container to check.
		/// @return Returns true if the attribute effect can be applied, false otherwise.
		virtual bool are_conditions_met(AttributeContainer *p_attribute_container);
		/// @brief Calculates the affected amount of the attribute effect.
		virtual float calculate_affected_amount();
		/// @brief Returns the applications of this attribute effect. Each item in the array is how the attribute effect will be applied.
		/// @return
		PackedFloat32Array get_applications() const;
		/// @brief Gets how much the attribute will be affected by this attribute effect.
		/// @return
		float get_affected_amount();
		/// @brief Gets the attribute that will be affected by this attribute effect.
		/// @return
		StringName get_affected_attribute() const;
		/// @brief Gets the application type of this attribute effect.
		/// @return
		AttributeEffect::ApplicationType get_application_type() const;
		/// @brief Returns how many times this attribute effect will be applied
		/// @return
		int get_applications_count() const;
		/// @brief Returns whether or not this attribute effect should break.
		/// @param p_attribute_effect The attribute effect to check.
		/// @param p_attribute_container The attribute container to check.
		/// @return The break type.
		virtual int get_break(AttributeContainer *p_attribute_container);
		/// @brief Gets the application type of this attribute effect.
		/// @return
		TypedArray<AttributeEffectCondition> get_conditions() const;
		/// @brief Returns the duration of this attribute effect.
		/// @return
		float get_duration() const;
		/// @brief Gets the life cycle of this attribute effect.
		/// @return
		LifeCycle get_life_cycle() const;
		/// @brief Sets how much the attribute will be affected by this attribute effect.
		/// @param p_affected_amount The amount to set.
		void set_affected_amount(float p_affected_amount);
		/// @brief Sets the attribute that will be affected by this attribute effect.
		/// @param p_affected_attribute The attribute to set.
		void set_affected_attribute(StringName p_affected_attribute);
		/// @brief Sets the application type of this attribute effect.
		/// @param p_application_type The application type to set.
		void set_application_type(ApplicationType p_application_type);
		/// @brief Sets the conditions that must be met for this attribute effect to be applied.
		/// @param p_conditions The conditions to set.
		void set_conditions(TypedArray<AttributeEffectCondition> p_conditions);
		/// @brief Sets the duration of this attribute effect.
		/// @param p_duration
		void set_duration(float p_duration);
		/// @brief Sets the life cycle of this attribute effect.
		/// @param p_life_cycle The life cycle to set.
		void set_life_cycle(LifeCycle p_life_cycle);
	};
}

VARIANT_ENUM_CAST(ggs::AttributeEffect::ApplicationType);
VARIANT_ENUM_CAST(ggs::AttributeEffect::LifeCycle);

#endif
