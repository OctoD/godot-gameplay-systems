#ifndef GGS_ITEMS_POOL_H
#define GGS_ITEMS_POOL_H

#include <godot_cpp/classes/resource.hpp>

#include "item.h"

using namespace godot;

namespace ggs
{
	class ItemsPool : public Resource
	{
		GDCLASS(ItemsPool, Resource)

	protected:
		static void _bind_methods();
		TypedArray<Item> items;
		StringName pool_name;

	public:
		TypedArray<Item> get_items() const;
		StringName get_pool_name() const;
		void set_items(const TypedArray<Item> &p_items);
		void set_pool_name(const StringName &p_pool_name);
	};
}

#endif