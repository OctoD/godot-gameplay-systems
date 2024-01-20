#ifndef GGS_ITEM_MANAGER_H
#define GGS_ITEM_MANAGER_H

#include <godot_cpp/classes/node.hpp>

#include "item.h"
#include "items_pool.h"

using namespace godot;

namespace ggs
{
	class ItemManager : public Node
	{
		GDCLASS(ItemManager, Node)

	private:
		/// @brief Loads the items pools.
		void load_items_pools();

	protected:
		/// @brief The singleton instance.
		static ItemManager *singleton;
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The items pools.
		TypedArray<ItemsPool> items_pools;
		/// @brief Adds an items pool to the items pools.
		/// @param p_items_pool The items pool to add.
		void add_items_pool(ItemsPool *p_items_pool);
		/// @brief Checks if the items pools contains the specified items pool.
		/// @param p_items_pool The items pool to check.
		/// @return True if the items pools contains the specified items pool, false otherwise.
		bool has_items_pool_resource(ItemsPool *p_items_pool);
		/// @brief Removes an items pool from the items pools.
		/// @param p_items_pool The items pool to remove.
		void remove_items_pool(ItemsPool *p_items_pool);
		/// @brief Updates an items pool in the items pools.
		/// @param p_items_pool The items pool to update.
		void update_items_pool(ItemsPool *p_items_pool);

	public:
		/// @brief Default constructor.
		ItemManager();
		/// @brief Called when the node enters the scene tree for the first time.
		void _ready() override;
		/// @brief Gets the singleton instance.
		/// @return The singleton instance.
		static ItemManager *get_singleton();
		/// @brief Gets the specified items pool.
		/// @param p_item_pool_name The name of the items pool to get.
		/// @return The specified items pool.
		Ref<ItemsPool> get_items_pool(StringName p_item_pool_name) const;
		/// @brief Checks if the specified items pool exists.
		/// @param p_item_pool_name The name of the items pool to check.
		/// @return True if the specified items pool exists, false otherwise.
		bool has_items_pool(StringName p_item_pool_name) const;
		/// @brief Gets all the items.
		/// @return The items.
		TypedArray<Item> get_items() const;
		/// @brief Gets all the items from the specified items pool.
		/// @param p_item_pool_name The name of the items pool to get the items from.
		/// @return The items from the specified items pool.
		TypedArray<Item> get_items_from_pool(StringName p_item_pool_name) const;
		/// @brief Gets all the items pools.
		/// @return The items pools.
		TypedArray<ItemsPool> get_items_pools() const;
	};
}

#endif
