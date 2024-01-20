#include "items_pool.h"

#include <godot_cpp/classes/engine.hpp>

using namespace ggs;

void ItemsPool::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("get_items"), &ItemsPool::get_items);
	ClassDB::bind_method(D_METHOD("get_pool_name"), &ItemsPool::get_pool_name);
	ClassDB::bind_method(D_METHOD("set_items", "p_items"), &ItemsPool::set_items);
	ClassDB::bind_method(D_METHOD("set_pool_name", "p_pool_name"), &ItemsPool::set_pool_name);

	/// binds properties
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "items"), "set_items", "get_items");
	ADD_PROPERTY(PropertyInfo(Variant::STRING, "pool_name"), "set_pool_name", "get_pool_name");
}

TypedArray<Item> ItemsPool::get_items() const
{
    return items;
}

StringName ItemsPool::get_pool_name() const
{
    return pool_name;
}

void ItemsPool::set_items(const TypedArray<Item> &p_items)
{
	items = p_items;
	
	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemsPool::set_pool_name(const StringName &p_pool_name)
{
	pool_name = p_pool_name;
	
	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}
