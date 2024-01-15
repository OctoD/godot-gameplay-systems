#ifndef GGS_ABILITY_ABILITY_CONTAINER_H
#define GGS_ABILITY_ABILITY_CONTAINER_H

#include <godot_cpp/classes/node.hpp>

#include "ability.h"
#include "ability_grant.h"
#include "ability_queue.h"
#include "system/tag/tag_dictionary.h"

using namespace godot;

namespace ggs
{
	class AbilityContainer : public Node
	{
		GDCLASS(AbilityContainer, Node);

	private:
		// note: doing this because the normal set_abilities must accept a TypedArray<RefCounted>
		TypedArray<Ability> _abilities;
		TypedArray<Ability> _get_abilities() const;
		void _set_abilities(TypedArray<Ability> p_abilities);
		void _handle_ability_enqueued(Ability *p_ability);
		void _handle_ability_dequeued(Ability *p_ability);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The ability queue.
		AbilityQueue *ability_queue;
		/// @brief The abilities that are contained.
		TypedArray<AbilityGrant> abilities;
		/// @brief The owner of the abilities.
		Node *ability_owner;
		/// @brief Gets the ability grant.
		/// @param p_ability The ability to get the grant for.
		/// @return The ability grant.
		AbilityGrant *get_ability_grant(const StringName &p_ability_name) const;
		/// @brief Gets the ability grant.
		/// @param p_ability The ability to get the grant for.
		/// @return The ability grant.
		AbilityGrant *get_ability_grant(Ability *p_ability) const;
		/// @brief Revokes an ability grant.
		/// @param p_ability_grant The ability grant to revoke.
		void revoke_ability_grant(AbilityGrant *p_ability_grant);
		/// @brief Gets the tag dictionary of the owner.
		void setup_tag_dictionary();
		/// @brief The tags that the owner has.
		TagDictionary tags;

	public:
		/// @brief Default constructor.
		AbilityContainer();
		/// @brief Default destructor.
		~AbilityContainer();
		/// @brief The process function from Godot.
		/// @param delta The time since the last frame.
		void _process(float delta);
		/// @brief Override of the ready function from Godot.
		void _ready() override;
		/// @brief Activates an ability.
		/// @param p_ability The ability to activate.
		void activate(Ability *p_ability);
		/// @brief Activates all abilities which meet their own requirements.
		void activate_many();
		/// @brief Activates an ability by name.
		/// @param p_ability_name The name of the ability to activate.
		void activate_by_name(const StringName &p_ability_name);
		/// @brief Adds an ability.
		/// @param p_ability The ability to add.
		void add_ability(Ability *p_ability);
		/// @brief Blocks an ability.
		/// @param p_ability The ability to block.
		void block(Ability *p_ability);
		/// @brief Blocks all abilities which meet their own requirements.
		void block_many();
		/// @brief Blocks an ability by name.
		/// @param p_ability_name The name of the ability to block.
		void block_by_name(const StringName &p_ability_name);
		/// @brief Returns if the container can activate an ability.
		/// @param p_ability The ability to check for.
		/// @return True if the container can activate the ability, false otherwise.
		bool can_activate(Ability *p_ability) const;
		/// @brief Returns if the container can activate an ability by name.
		/// @param p_ability_name The name of the ability to check for.
		/// @return True if the container can activate the ability, false otherwise.
		bool can_activate_by_name(const StringName &p_ability_name) const;
		/// @brief Returns if the container can block an ability.
		/// @param p_ability The ability to check for.
		/// @return True if the container can block the ability, false otherwise.
		bool can_block(Ability *p_ability) const;
		/// @brief Returns if the container can block an ability by name.
		/// @param p_ability_name The name of the ability to check for.
		/// @return True if the container can block the ability, false otherwise.
		bool can_block_by_name(const StringName &p_ability_name) const;
		/// @brief Returns if the container can cancel an ability.
		/// @param p_ability The ability to check for.
		/// @return True if the container can cancel the ability, false otherwise.
		bool can_cancel(Ability *p_ability) const;
		/// @brief Returns if the container can cancel an ability by name.
		/// @param p_ability_name The name of the ability to check for.
		/// @return True if the container can cancel the ability, false otherwise.
		bool can_cancel_by_name(const StringName &p_ability_name) const;
		/// @brief Returns if the container can grant an ability.
		/// @param p_ability The ability to check for.
		/// @return True if the container can grant the ability, false otherwise.
		bool can_grant(Ability *p_ability) const;
		/// @brief Returns if the container can revoke a granted ability.
		/// @param p_ability The ability to check for.
		/// @return True if the container can revoke the ability, false otherwise.
		bool can_revoke(Ability *p_ability) const;
		/// @brief Cancels an ability.
		/// @param p_ability The ability to cancel.
		void cancel(Ability *p_ability);
		/// @brief Cancels all abilities which meet their own requirements.
		void cancel_many();
		/// @brief Cancels an ability by name.
		/// @param p_ability_name The name of the ability to cancel.
		void cancel_by_name(const StringName &p_ability_name);
		/// @brief Checks if the container has an ability.
		/// @param p_ability The ability to check for.
		/// @return True if the container has the ability, false otherwise.
		bool has_ability(Ability *p_ability) const;
		/// @brief Returns if the container has an ability owner.
		/// @return True if the container has an ability owner, false otherwise.
		bool has_ability_owner() const;
		/// @brief Gets an ability by name.
		/// @param p_ability_name the name of the ability.
		/// @return The ability with the given name.
		Ref<Ability> get_ability(const StringName &p_ability_name) const;
		/// @brief Gets the abilities.
		/// @return The abilities.
		TypedArray<Ability> get_abilities() const;
		/// @brief Gets all the activatable abilities.
		/// @return The activatable abilities.
		TypedArray<Ability> get_activatable_abilities() const;
		/// @brief Gets the blockable abilities.
		/// @return The blockable abilities.
		TypedArray<Ability> get_blockable_abilities() const;
		/// @brief Gets the cancellable abilities.
		/// @return The cancellable abilities.
		TypedArray<Ability> get_cancellable_abilities() const;
		/// @brief Returns the owner of the abilities.
		/// @return The owner of the abilities.
		Node *get_ability_owner() const;
		/// @brief Grants an ability.
		/// @param p_ability
		void grant_ability(Ability *p_ability);
		/// @brief Grants the abilities owned by the container.
		void grant_abilities();
		/// @brief Revokes an ability.
		/// @param p_ability The ability to revoke.
		void revoke(Ability *p_ability);
		/// @brief Revokes an ability by name.
		/// @param p_ability_name The name of the ability to revoke.
		void revoke_by_name(const StringName &p_ability_name);
		/// @brief Revokes all abilities in the container if possible.
		void revoke_all();
		/// @brief Set the abilities.
		/// @param p_abilities The abilities.
		void set_abilities(TypedArray<Ability> p_abilities);
		/// @brief Sets the owner of the abilities.
		/// @param p_ability_owner The owner of the abilities.
		void set_ability_owner(Node *p_ability_owner);
	};
}

#endif