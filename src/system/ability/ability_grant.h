#ifndef GGS_ABILITY_GRANT_H
#define GGS_ABILITY_GRANT_H

#include <godot_cpp/classes/ref_counted.hpp>

#include "ability.h"

using namespace godot;

namespace ggs
{
	class AbilityGrant : public RefCounted
	{
		GDCLASS(AbilityGrant, RefCounted);

	protected:
		static void _bind_methods();
		/// @brief The ability that was granted. True if the ability was granted, false otherwise.
		bool granted;
		/// @brief The ability that is contained.
		Ref<Ability> ability;

	public:
		operator Variant() const { return Variant((Object *)this); }
	
		/// @brief Default constructor.
		AbilityGrant();
		/// @brief Default destructor.
		~AbilityGrant();
		/// @brief Gets the ability.
		/// @return The ability.
		Ref<Ability> get_ability() const;
		/// @brief Gets the ability grant.
		/// @return True if the ability was granted, false otherwise.
		bool get_grant() const;
		/// @brief Sets the ability grant.
		/// @param p_grant True if the ability was granted, false otherwise.
		void set_grant(bool p_grant);
		/// @brief Gets the ability.
		/// @param p_ability The ability.
		void set_ability(Ref<Ability> p_ability);
	};
}

#endif
