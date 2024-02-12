#include "item_manager.h"
#include "item_project_settings.h"

#include <godot_cpp/classes/resource_loader.hpp>

using namespace ggs;

ItemManager *ItemManager::singleton = nullptr;

void ItemManager::load_items_pools()
{
	/// let's retrieve the settings' value
	PackedStringArray resource_file_paths = ItemProjectSettings::get_resource_file_paths();
	/// let's get the resource loader instance
	ResourceLoader *resource_loader = ResourceLoader::get_singleton();

	if (resource_loader != nullptr)
	{
		for (int i = 0; i < resource_file_paths.size(); i++)
		{
			String resource_file_path = resource_file_paths[i];
			Ref<ItemsPool> resource = resource_loader->load(resource_file_path);

			if (resource.is_valid())
			{
				add_items_pool(resource.ptr());
			}
		}
	}
}

void ItemManager::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("get_items"), &ItemManager::get_items);
	ClassDB::bind_method(D_METHOD("get_items_from_pool", "item_pool_name"), &ItemManager::get_items_from_pool);
	ClassDB::bind_method(D_METHOD("get_items_pools"), &ItemManager::get_items_pools);
	ClassDB::bind_method(D_METHOD("has_items_pool", "item_pool_name"), &ItemManager::has_items_pool);

	/// binds signals
	ADD_SIGNAL(MethodInfo("items_pool_added", PropertyInfo(Variant::OBJECT, "items_pool", PROPERTY_HINT_RESOURCE_TYPE, "ItemsPool")));
	ADD_SIGNAL(MethodInfo("items_pool_removed", PropertyInfo(Variant::OBJECT, "items_pool", PROPERTY_HINT_RESOURCE_TYPE, "ItemsPool")));
	ADD_SIGNAL(MethodInfo("items_pool_updated", PropertyInfo(Variant::OBJECT, "items_pool", PROPERTY_HINT_RESOURCE_TYPE, "ItemsPool")));
}

void ItemManager::add_items_pool(ItemsPool *p_items_pool)
{
	if (p_items_pool == nullptr)
	{
		return;
	}

	if (has_items_pool_resource(p_items_pool))
	{
		return;
	}
	
	items_pools.append(p_items_pool);
	emit_signal("items_pool_added", p_items_pool);

	ItemProjectSettings::add_resource(p_items_pool->get_path());
}

bool ItemManager::has_items_pool_resource(ItemsPool *p_items_pool)
{
	if (p_items_pool == nullptr)
	{
		return false;
	}

	for (int i = 0; i < items_pools.size(); i++)
	{
		Variant variant = items_pools[i];
		ItemsPool *items_pool = cast_to<ItemsPool>(variant);

		if (items_pool->get_path() == p_items_pool->get_path() || items_pool->get_pool_name() == p_items_pool->get_pool_name())
		{
			return true;
		}
	}
	
    return false;
}

void ItemManager::remove_items_pool(ItemsPool *p_items_pool)
{
	if (!has_items_pool_resource(p_items_pool))
	{
		return;
	}

	int index = items_pools.find(p_items_pool);

	if (index != -1)
	{
		ItemProjectSettings::remove_resource(p_items_pool->get_path());

		items_pools.remove_at(index);
		emit_signal("items_pool_removed", p_items_pool);
	}
}

void ItemManager::update_items_pool(ItemsPool *p_items_pool)
{
	if (!has_items_pool_resource(p_items_pool))
	{
		add_items_pool(p_items_pool);
		return;
	}

	int index = items_pools.find(p_items_pool);

	if (index != -1)
	{
		items_pools[index] = p_items_pool;
		emit_signal("items_pool_updated", p_items_pool);
	}
}

ItemManager::ItemManager()
{
	if (singleton == nullptr)
	{
		singleton = this;
	}
	else
	{
		items_pools = singleton->items_pools;
	}
}

void ItemManager::_ready()
{
	load_items_pools();
}

ItemManager *ItemManager::get_singleton()
{
	if (singleton == nullptr)
	{
		return memnew(ItemManager);
	}

	return singleton;
}

Ref<ItemsPool> ItemManager::get_items_pool(StringName p_item_pool_name) const
{
	for (int i = 0; i < items_pools.size(); i++)
	{
		Variant variant = items_pools[i];
		ItemsPool *items_pool = cast_to<ItemsPool>(variant);

		if (items_pool->get_pool_name() == p_item_pool_name)
		{
			return items_pool->duplicate();
		}
	}

	return Ref<ItemsPool>();
}

bool ItemManager::has_items_pool(StringName p_item_pool_name) const
{
	for (int i = 0; i < items_pools.size(); i++)
	{
		Variant variant = items_pools[i];
		ItemsPool *items_pool = cast_to<ItemsPool>(variant);

		if (items_pool->get_pool_name() == p_item_pool_name)
		{
			return true;
		}
	}

	return false;
}

TypedArray<Item> ItemManager::get_items() const
{
	TypedArray<Item> items = TypedArray<Item>();

	for (int i = 0; i < items_pools.size(); i++)
	{
		Variant variant = items_pools[i];
		ItemsPool *items_pool = cast_to<ItemsPool>(variant);

		if (items_pool == nullptr)
		{
			continue;
		}

		items.append_array(items_pool->get_items());
	}

	return TypedArray<Item>();
}

TypedArray<Item> ItemManager::get_items_from_pool(StringName p_item_pool_name) const
{
	Ref<ItemsPool> pool = get_items_pool(p_item_pool_name);

	if (pool != nullptr)
	{
		return pool->get_items();
	}

	return TypedArray<Item>();
}

TypedArray<ItemsPool> ItemManager::get_items_pools() const
{
	return TypedArray<ItemsPool>(items_pools);
}
