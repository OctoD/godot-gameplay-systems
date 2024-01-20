#ifndef GGS_ITEM_H
#define GGS_ITEM_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

namespace ggs
{
	/// @brief The settings of an item.
	class ItemSettings : public Resource
	{
		GDCLASS(ItemSettings, Resource);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The item decreases in quantity when used.
		bool decrease_quantity_on_activate;
		/// @brief Whether the item is stackable.
		bool is_stackable;
		/// @brief The maximum quantity of the item.
		int max_quantity;

	public:
		/// @brief Gets whether the item decreases in quantity when used.
		/// @return True if the item decreases in quantity when used, false otherwise.
		bool get_decrease_quantity_on_activate() const;
		/// @brief Gets whether the item is stackable.
		/// @return True if the item is stackable, false otherwise.
		bool get_is_stackable() const;
		/// @brief Gets the maximum quantity of the item.
		/// @return The maximum quantity of the item.
		int get_max_quantity() const;
		/// @brief Sets whether the item decreases in quantity when used.
		/// @param p_decrease_quantity_on_use True if the item decreases in quantity when used, false otherwise.
		void set_decrease_quantity_on_activate(bool p_decrease_quantity_on_activate);
		/// @brief Sets the maximum quantity of the item.
		/// @param p_max_quantity The maximum quantity of the item.
		void set_max_quantity(int p_max_quantity);
		/// @brief Sets whether the item is stackable.
		/// @param p_is_stackable True if the item is stackable, false otherwise.
		void set_is_stackable(bool p_is_stackable);
	};

	/// @brief An item resource.
	class ItemTags : public Resource
	{
		GDCLASS(ItemTags, Resource);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The tags which are added when the item is activated.
		PackedStringArray tags_added_on_activation;
		/// @brief The tags which are added when the item is added.
		PackedStringArray tags_added_on_add;
		/// @brief The tags which are added when the item is removed.
		PackedStringArray tags_added_on_drop;
		/// @brief The tags which are added when the item is equipped.
		PackedStringArray tags_added_on_equip;
		/// @brief The tags which are added when the item is unequipped.
		PackedStringArray tags_added_on_unequip;
		/// @brief The tags which are required to activate the item.
		PackedStringArray tags_required_to_activate;
		/// @brief The tags which are required to add the item.
		PackedStringArray tags_required_to_add;
		/// @brief The tags which are required to equip the item.
		PackedStringArray tags_required_to_equip;
		/// @brief The tags which are required to remove the item.
		PackedStringArray tags_required_to_remove;
		/// @brief The tags which are required to unequip the item.
		PackedStringArray tags_required_to_unequip;
		/// @brief The tags which are removed when the item is activated.
		PackedStringArray tags_removed_on_activation;
		/// @brief The tags which are removed when the item is added.
		PackedStringArray tags_removed_on_add;
		/// @brief The tags which are removed when the item is equipped.
		PackedStringArray tags_removed_on_equip;
		/// @brief The tags which are removed when the item is removed.
		PackedStringArray tags_removed_on_drop;
		/// @brief The tags which are removed when the item is unequipped.
		PackedStringArray tags_removed_on_unequip;

	public:
		/// @brief Gets the tags which are added when the item is activated.
		/// @return the tags which are added when the item is activated.
		PackedStringArray get_tags_added_on_activation() const;
		/// @brief Gets the tags which are added when the item is added.
		/// @return The tags which are added when the item is added.
		PackedStringArray get_tags_added_on_add() const;
		/// @brief Gets the tags which are added when the item is removed.
		/// @return The tags which are added when the item is removed.
		PackedStringArray get_tags_added_on_drop() const;
		/// @brief Gets the tags which are added when the item is equipped.
		/// @return The tags which are added when the item is equipped.
		PackedStringArray get_tags_added_on_equip() const;
		/// @brief Gets the tags which are added when the item is unequipped.
		/// @return The tags which are added when the item is unequipped.
		PackedStringArray get_tags_added_on_unequip() const;
		/// @brief 	Gets the tags which are required to activate the item.
		/// @return The tags which are required to activate the item.
		PackedStringArray get_tags_required_to_activate() const;
		/// @brief Gets the tags which are required to add the item.
		/// @return The tags which are required to add the item.
		PackedStringArray get_tags_required_to_add() const;
		/// @brief Gets the tags which are required to equip the item.
		/// @return The tags which are required to equip the item.
		PackedStringArray get_tags_required_to_equip() const;
		/// @brief Gets the tags which are required to remove the item.
		/// @return The tags which are required to remove the item.
		PackedStringArray get_tags_required_to_remove() const;
		/// @brief Gets the tags which are required to unequip the item.
		/// @return The tags which are required to unequip the item.
		PackedStringArray get_tags_required_to_unequip() const;
		/// @brief Gets the tags which are removed when the item is activated.
		/// @return The tags which are removed when the item is activated.
		PackedStringArray get_tags_removed_on_activation() const;
		/// @brief Gets the tags which are removed when the item is added.
		/// @return The tags which are removed when the item is added.
		PackedStringArray get_tags_removed_on_add() const;
		/// @brief Gets the tags which are removed when the item is removed.
		/// @return The tags which are removed when the item is removed.
		PackedStringArray get_tags_removed_on_drop() const;
		/// @brief Gets the tags which are removed when the item is equipped.
		/// @return The tags which are removed when the item is equipped.
		PackedStringArray get_tags_removed_on_equip() const;
		/// @brief Gets the tags which are removed when the item is unequipped.
		/// @return The tags which are removed when the item is unequipped.
		PackedStringArray get_tags_removed_on_unequip() const;
		/// @brief Sets the tags which are added when the item is activated.
		/// @param p_tags The tags which are added when the item is activated.
		void set_tags_added_on_activation(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are added when the item is added.
		/// @param p_tags The tags which are added when the item is added.
		void set_tags_added_on_add(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are added when the item is removed.
		/// @param p_tags The tags which are added when the item is removed.
		void set_tags_added_on_drop(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are added when the item is equipped.
		/// @param p_tags The tags which are added when the item is equipped.
		void set_tags_added_on_equip(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are added when the item is unequipped.
		/// @param p_tags The tags which are added when the item is unequipped.
		void set_tags_added_on_unequip(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are required to activate the item.
		/// @param p_tags The tags which are required to activate the item.
		void set_tags_required_to_activate(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are required to add the item.
		/// @param p_tags The tags which are required to add the item.
		void set_tags_required_to_add(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are required to equip the item.
		/// @param p_tags The tags which are required to equip the item.
		void set_tags_required_to_equip(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are required to remove the item.
		/// @param p_tags The tags which are required to remove the item.
		void set_tags_required_to_remove(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are required to unequip the item.
		/// @param p_tags The tags which are required to unequip the item.
		void set_tags_required_to_unequip(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are removed when the item is activated.
		/// @param p_tags The tags which are removed when the item is activated.
		void set_tags_removed_on_activation(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are removed when the item is added.
		/// @param p_tags The tags which are removed when the item is added.
		void set_tags_removed_on_add(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are removed when the item is removed.
		/// @param p_tags The tags which are removed when the item is removed.
		void set_tags_removed_on_drop(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are removed when the item is equipped.
		/// @param p_tags The tags which are removed when the item is equipped.
		void set_tags_removed_on_equip(const PackedStringArray &p_tags);
		/// @brief Sets the tags which are removed when the item is unequipped.
		/// @param p_tags The tags which are removed when the item is unequipped.
		void set_tags_removed_on_unequip(const PackedStringArray &p_tags);
	};

	class Item : public Resource
	{
		GDCLASS(Item, Resource);

	protected:
		static void _bind_methods();

		/// @brief The name of the item.
		StringName item_name;
		/// @brief The settings of the item.
		ItemSettings *item_settings;
		/// @brief The item's tags.
		PackedStringArray tags;
		/// @brief The tags of the item.
		ItemTags *item_tags;

	public:
		/// @brief The name of the item.
		StringName get_item_name() const;
		/// @brief Gets the settings of the item.
		/// @return The settings of the item.
		ItemSettings *get_item_settings() const;
		/// @brief Gets the tags of the item.
		/// @return The tags of the item.
		ItemTags *get_item_tags() const;
		/// @brief Gets the tags of the item.
		/// @return The tags of the item.
		PackedStringArray get_tags() const;
		/// @brief Sets the name of the item.
		void set_item_name(StringName p_item_name);
		/// @brief Sets the settings of the item.
		/// @param p_item_settings The settings of the item.
		void set_item_settings(ItemSettings *p_item_settings);
		/// @brief Sets the tags of the item.
		/// @param p_item_tags The tags of the item.
		void set_item_tags(ItemTags *p_item_tags);
		/// @brief Sets the tags of the item.
		/// @param p_tags The tags of the item.
		void set_tags(const PackedStringArray &p_tags);
	};
}

#endif
