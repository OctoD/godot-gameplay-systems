#ifndef GGS_ITEM_H
#define GGS_ITEM_H

#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/resource.hpp>

using namespace godot;

namespace ggs
{
	class Item;
	
	class ItemStack : public RefCounted
	{
		GDCLASS(ItemStack, RefCounted);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The item of the stack.
		Item *item;
		/// @brief The maximum quantity of the item.
		int max_quantity;
		/// @brief The quantity of the item.
		int quantity;

	public:
		/// @brief Gets the item of the stack.
		/// @return The item of the stack.
		Ref<Item> get_item() const;
		/// @brief Gets the maximum quantity of the item.
		/// @return The maximum quantity of the item.
		int get_max_quantity() const;
		/// @brief Gets the quantity of the item.
		/// @return The quantity of the item.
		int get_quantity() const;
		/// @brief Sets the item of the stack.
		/// @param p_item The item of the stack.
		void set_item(Item *p_item);
		/// @brief Sets the maximum quantity of the item.
		/// @param p_max_quantity The maximum quantity of the item.
		void set_max_quantity(int p_max_quantity);
		/// @brief Sets the quantity of the item.
		/// @param p_quantity The quantity of the item.
		void set_quantity(int p_quantity);
	};

	class ItemStackSetting : public Resource
	{
		GDCLASS(ItemStackSetting, Resource);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The maximum stack size.
		int maximum_stack_size;
		/// @brief The stacking type.
		int stacking_type;

	public:
		enum StackingType
		{
			FINITE,
			INFINITE
		};

		/// @brief Gets the maximum stack size.
		/// @return The maximum stack size.
		int get_maximum_stack_size() const;
		/// @brief Gets the stacking type.
		/// @return The stacking type.
		StackingType get_stacking_type() const;
		/// @brief Sets the maximum stack size.
		/// @param p_maximum_stack_size The maximum stack size.
		void set_maximum_stack_size(int p_maximum_stack_size);
		/// @brief Sets the stacking type.
		/// @param p_stacking_type The stacking type.
		void set_stacking_type(StackingType p_stacking_type);
	};

	class Item : public Resource
	{
		GDCLASS(Item, Resource);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The stack setting of the item.
		ItemStackSetting *stack_setting;

	public:
		/// @brief Gets the stack setting of the item.
		/// @return The stack setting of the item.
		ItemStackSetting *get_stack_setting() const;
		/// @brief Sets the stack setting of the item.
		/// @param p_stack_setting The stack setting of the item.
		void set_stack_setting(ItemStackSetting *p_stack_setting);
	};
}

VARIANT_ENUM_CAST(ggs::ItemStackSetting::StackingType);

#endif
