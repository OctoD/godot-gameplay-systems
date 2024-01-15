#ifndef GGS_ABILITY_H
#define GGS_ABILITY_H

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

namespace ggs
{
	/// @brief The Ability class.
	/// @details This class is used to represent an ability. 
	/// It contains all the information needed to use an ability.
	/// You can set (in gdscript) the methods:
	///		- can_activate(ability_owner, ability_container) -> bool;
	///		- can_block(ability_owner, ability_container) -> bool;
	///		- can_cancel(ability_owner, ability_container) -> bool;
	///		- can_grant(ability_owner, ability_container) -> bool;
	///		- on_activate(ability_owner, ability_container) -> void;
	///		- on_block(ability_owner, ability_container) -> void;
	///		- on_cancel(ability_owner, ability_container) -> void;
	class Ability : public Resource
	{
		GDCLASS(Ability, Resource);

	protected:
		static void _bind_methods();
		/// @brief The name of the ability.
		StringName ability_name;
		/// @brief The ability cooldown. Set to 0 to disable.
		float cooldown;
		/// @brief Tags that are added to the user when the ability's cooldown ends.
		PackedStringArray tags_added_on_cooldown_end;
		/// @brief Tags that are added to the user when the ability's cooldown starts.
		PackedStringArray tags_added_on_cooldown_start;
		/// @brief The tags that are added to the user when this ability is granted.
		PackedStringArray tags_added_on_grant;
		/// @brief The tags that are added to the user when this ability is activated.
		PackedStringArray tags_added_on_activation;
		/// @brief The tags that are removed from the user when this ability's cooldown ends.
		PackedStringArray tags_removed_on_cooldown_end;
		/// @brief The tags that are removed from the user when this ability's cooldown starts.
		PackedStringArray tags_removed_on_cooldown_start;
		/// @brief The tags that are removed from the user when this ability is activated.
		PackedStringArray tags_removed_on_activation;
		/// @brief The tags that are removed from the user when this ability is blocked.
		PackedStringArray tags_removed_on_block;
		/// @brief The tags that are removed from the user when this ability is cancelled.
		PackedStringArray tags_removed_on_cancel;
		/// @brief The tags that are required for this ability to be activated.
		PackedStringArray tags_required_to_activate;
		/// @brief The tags which will block this ability from being activated.
		PackedStringArray tags_required_to_block;
		/// @brief The tags that are required for this ability to be cancelled.
		PackedStringArray tags_required_to_cancel;
		/// @brief The tags that are required for this ability to be granted.
		PackedStringArray tags_required_to_grant;

	public:
		/// @brief Default constructor.
		Ability();
		/// @brief Default destructor.
		~Ability();
		/// @brief Returns if the ability has a cooldown.
		/// @return True if the ability has a cooldown, false otherwise.
		bool has_cooldown() const;
		/// @brief Gets the ability name.
		/// @return The ability name.
		StringName get_ability_name() const;
		/// @brief Gets the ability cooldown.
		/// @return The ability cooldown.
		float get_cooldown() const;
		/// @brief Gets the tags that are added to the user when the ability's cooldown ends.
		/// @return The tags that are added to the user when the ability's cooldown ends.
		PackedStringArray get_tags_added_on_cooldown_end() const;
		/// @brief Gets the tags that are added to the user when the ability's cooldown starts.
		/// @return The tags that are added to the user when the ability's cooldown starts.
		PackedStringArray get_tags_added_on_cooldown_start() const;
		/// @brief Gets the tags that are added to the user when this ability is granted.
		/// @return The tags that are added to the user when this ability is granted.
		PackedStringArray get_tags_added_on_grant() const;
		/// @brief Gets the tags that are added to the user when this ability is activated.
		/// @return The tags that are added to the user when this ability is activated.
		PackedStringArray get_tags_added_on_activation() const;
		/// @brief Gets the tags that are removed from the user when this ability's cooldown ends.
		/// @return The tags that are removed from the user when this ability's cooldown ends.
		PackedStringArray get_tags_removed_on_cooldown_end() const;
		/// @brief Gets the tags that are removed from the user when this ability's cooldown starts.
		/// @return The tags that are removed from the user when this ability's cooldown starts.
		PackedStringArray get_tags_removed_on_cooldown_start() const;
		/// @brief Gets the tags that are removed from the user when this ability is activated.
		/// @return The tags that are removed from the user when this ability is activated.
		PackedStringArray get_tags_removed_on_activation() const;
		/// @brief Gets the tags that are removed from the user when this ability is blocked.
		/// @return The tags that are removed from the user when this ability is blocked.
		PackedStringArray get_tags_removed_on_block() const;
		/// @brief Gets the tags that are removed from the user when this ability is cancelled.
		/// @return The tags that are removed from the user when this ability is cancelled.
		PackedStringArray get_tags_removed_on_cancel() const;
		/// @brief Gets the tags that are required for this ability to be activated.
		/// @return The tags that are required for this ability to be activated.
		PackedStringArray get_tags_required_to_activate() const;
		/// @brief Gets the tags which will block this ability from being activated.
		/// @return The tags which will block this ability from being activated.
		PackedStringArray get_tags_required_to_block() const;
		/// @brief Gets the tags that are required for this ability to be cancelled.
		/// @return The tags that are required for this ability to be cancelled.
		PackedStringArray get_tags_required_to_cancel() const;
		/// @brief Gets the tags that are required for this ability to be granted.
		/// @return The tags that are required for this ability to be granted.
		PackedStringArray get_tags_required_to_grant() const;
		/// @brief Sets the tags that are required for this ability to be activated.
		/// @param p_name The name of the ability.
		void set_ability_name(const StringName &p_name);
		/// @brief Sets the ability cooldown.
		/// @param p_cooldown The ability cooldown.
		void set_cooldown(const float p_cooldown);
		/// @brief Sets the tags that are added to the user when the ability's cooldown ends.
		/// @param p_tags The tags that are added to the user when the ability's cooldown ends.
		void set_tags_added_on_cooldown_end(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are added to the user when the ability's cooldown starts.
		/// @param p_tags The tags that are added to the user when the ability's cooldown starts.
		void set_tags_added_on_cooldown_start(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are added to the user when this ability is granted.
		/// @param p_tags The tags that are added to the user when this ability is granted.
		void set_tags_added_on_grant(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are added to the user when this ability is activated.
		/// @param p_tags The tags that are added to the user when this ability is activated.
		void set_tags_added_on_activation(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are removed from the user when this ability's cooldown ends.
		/// @param p_tags The tags that are removed from the user when this ability's cooldown ends.
		void set_tags_removed_on_cooldown_end(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are removed from the user when this ability's cooldown starts.
		/// @param p_tags The tags that are removed from the user when this ability's cooldown starts.
		void set_tags_removed_on_cooldown_start(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are removed from the user when this ability is activated.
		/// @param p_tags The tags that are removed from the user when this ability is activated.
		void set_tags_removed_on_activation(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are removed from the user when this ability is blocked.
		/// @param p_tags The tags that are removed from the user when this ability is blocked.
		void set_tags_removed_on_block(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are removed from the user when this ability is cancelled.
		/// @param p_tags The tags that are removed from the user when this ability is cancelled.
		void set_tags_removed_on_cancel(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are required for this ability to be activated.
		/// @param p_tags The tags that are required for this ability to be activated.
		void set_tags_required_to_activate(const PackedStringArray &p_tags);
		/// @brief Sets the tags which will block this ability from being activated.
		/// @param p_tags The tags which will block this ability from being activated.
		void set_tags_required_to_block(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are required for this ability to be cancelled.
		/// @param p_tags The tags that are required for this ability to be cancelled.
		void set_tags_required_to_cancel(const PackedStringArray &p_tags);
		/// @brief Sets the tags that are required for this ability to be granted.
		/// @param p_tags The tags that are required for this ability to be granted.
		void set_tags_required_to_grant(const PackedStringArray &p_tags);
	};
}

#endif