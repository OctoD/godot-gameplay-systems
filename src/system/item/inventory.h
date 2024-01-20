#ifndef GGS_INVENTORY_H
#define GGS_INVENTORY_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref_counted.hpp>

#include "item.h"

using namespace godot;

namespace ggs
{
	class Equipment;

	class InventoryItem : public RefCounted
	{
		GDCLASS(InventoryItem, RefCounted);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The item reference.
		Ref<Item> item_ref;
		/// @brief The quantity of the item.
		int quantity;

	public:
		/// @brief  Default constructor.
		InventoryItem();
		/// @brief Constructor with item.
		/// @param p_item The item.
		InventoryItem(Item *p_item);
		/// @brief Constructor with item and quantity.
		/// @param p_item The item.
		/// @param p_quantity The quantity of the item.
		InventoryItem(Item *p_item, int p_quantity);
		/// @brief Destructor.
		~InventoryItem();
		/// @brief Returns a duplicate of the item.
		/// @return The duplicate of the item.
		Ref<InventoryItem> duplicate() const;
		/// @brief Get the item reference.
		/// @return The item reference.
		Ref<Item> get_item() const;
		/// @brief Get the quantity of the item.
		/// @return The quantity of the item.
		int get_quantity() const;
		/// @brief Set the item reference.
		/// @param p_item The item reference.
		void set_item(Ref<Item> p_item);
		/// @brief Set the quantity of the item.
		/// @param p_quantity The quantity of the item.
		void set_quantity(int p_quantity);
	};

	/// @brief The inventory node.
	class Inventory : public Node
	{
		GDCLASS(Inventory, Node)

		friend class Equipment;

	protected:
		/// @brief Bind methods to Godot.
		static void _bind_methods();
		/// @brief The related equipment to this inventory.
		Equipment *equipment;
		/// @brief The owner of the inventory.
		Node *inventory_owner;
		/// @brief The items in the inventory.
		TypedArray<InventoryItem> items;

	public:
		enum SplitError
		{
			ERROR,
			ITEM_NOT_FOUND,
			ITEM_IS_NULL,
			OK,
			QUANTITY_IS_GREATER_THAN_ITEM_QUANTITY,
			QUANTITY_IS_NEGATIVE,
			QUANTITY_IS_ZERO,
		};
	
		/// @brief Activates the item if possible. Also calls "on_activate" from gdscript's item if defined.
		/// @param p_item The item to activate.
		/// @return True if the item has been activated, false otherwise.
		bool activate(Item *p_item);
		/// @brief Adds an item to this inventory. Also calls "on_add" from gdscript's item if defined.
		/// @param p_item The item to add.
		/// @return True if the item has been added, false otherwise.
		bool add_item(Item *p_item);
		/// @brief Check if the item can be activated. Also calls "can_activate" from gdscript's item if defined. If it's defined, it will be "override" the inventory's method.
		/// @param p_item The item to check.
		/// @return True if the item can be activated, false otherwise.
		bool can_activate(Item *p_item) const;
		/// @brief Check if the item can be added. Also calls "can_add" from gdscript's item if defined. If it's defined, it will be "override" the inventory's method.
		/// @param p_item The item to check.
		/// @return True if the item can be added, false otherwise.
		bool can_add(Item *p_item) const;
		/// @brief Check if the item can be dropped. Also calls "can_drop" from gdscript's item if defined. If it's defined, it will be "override" the inventory's method.
		/// @param p_item The item to check.
		/// @return True if the item can be dropped, false otherwise.
		bool can_drop(Item *p_item) const;
		/// @brief Check if the item can be equipped.
		/// @param p_item The item to check.
		/// @param p_slot The slot to check.
		/// @return True if the item can be equipped, false otherwise.
		bool can_equip(Item *p_item, String p_slot) const;
		/// @brief Drops an item from the inventory. Also calls "on_drop" from gdscript's item if defined.
		/// @param p_item The item to drop.
		/// @return True if the item has been dropped, false otherwise.
		bool drop_item(Item *p_item);
		/// @brief Equips an item to the related equipment node.
		/// @param p_item The item to equip.
		/// @param p_slot The slot to equip the item.
		/// @return True if the item has been equipped, false otherwise.
		bool equip_item(Item *p_item, String p_slot);
		/// @brief Gets the related equipment node.
		/// @return The related equipment node.
		Equipment *get_equipment() const;
		/// @brief Get the owner of the inventory.
		/// @return The owner of the inventory.
		Node *get_inventory_owner() const;
		/// @brief Checks if the inventory has an equipment.
		/// @return True if the inventory has an equipment, false otherwise.
		bool has_equipment() const;
		/// @brief Checks if the Inventory has an inventory owner.
		/// @return True if the inventory owner is set, false otherwise.
		bool has_inventory_owner() const;
		/// @brief Sets the related equipment node.
		/// @param p_equipment The related equipment node.
		void set_equipment(Equipment *p_equipment);
		/// @brief Set the owner of the inventory.
		/// @param owner The owner of the inventory.
		void set_inventory_owner(Node *p_owner);
		/// @brief Splits the quantity of an item in two separated items.
		/// @param p_item The item to split.
		/// @param p_quantity_a The resulting quantity.
		SplitError split_quantity(InventoryItem *p_item, int p_quantity);
	};
}

VARIANT_ENUM_CAST(ggs::Inventory::SplitError);

#endif
