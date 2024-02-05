#include "resource_manager.h"
#include "system/item/equipment_slot.h"
#include "system/item/items_pool.h"
#include "system/tag/tag_dictionary.h"

#include <godot_cpp/classes/dir_access.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/resource_saver.hpp>

using namespace ggs;

GGSResourceManager *GGSResourceManager::instance = nullptr;

const char *GGSResourceManager::EQUIPMENT_DIR = "res://.ggs/1.0.0/equipment";
const char *GGSResourceManager::ITEMS_DIR = "res://.ggs/1.0.0/items";
const char *GGSResourceManager::TAGS_DIR = "res://.ggs/1.0.0/tags";

void GGSResourceManager::_bind_methods()
{
}

Ref<EquipmentSlot> GGSResourceManager::create_equipment_slot_resource(String p_file_name) const
{
	Ref<EquipmentSlot> resource = memnew(EquipmentSlot);
	resource->set_name(p_file_name);
	resource->set_slot_name(p_file_name.replace(".tres", ""));
	resource->set_path(String(EQUIPMENT_DIR) + "/" + p_file_name);
	return resource;
}

Ref<ItemsPool> GGSResourceManager::create_items_pool_resource(String p_file_name) const
{
	Ref<ItemsPool> resource = memnew(ItemsPool);
	resource->set_name(p_file_name.replace(".tres", ""));
	resource->set_path(String(ITEMS_DIR) + "/" + p_file_name);
	resource->set_pool_name(p_file_name.replace(".tres", ""));
	return resource;
}

Ref<TagDictionary> GGSResourceManager::create_tag_resource(String p_file_name) const
{
	Ref<TagDictionary> resource = memnew(TagDictionary);
	resource->set_name(p_file_name.replace(".tres", ""));
	resource->set_path(String(TAGS_DIR) + "/" + p_file_name);
	return resource;
}

void GGSResourceManager::ensure_directory(const String &p_dir) const
{
	if (Engine::get_singleton()->is_editor_hint() && !DirAccess::dir_exists_absolute(p_dir))
	{
		WARN_PRINT("Creating directory: " + p_dir);
		Error err = DirAccess::make_dir_recursive_absolute(p_dir);

		if (err != Error::OK)
		{
			ERR_PRINT("Error creating directory: " + p_dir + " Error: " + String::num_int64(err));
		}
	}
}

void GGSResourceManager::ensure_directories() const
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		ensure_directory(EQUIPMENT_DIR);
		ensure_directory(ITEMS_DIR);
		ensure_directory(TAGS_DIR);
	}
}

Error GGSResourceManager::remove_resource(Ref<Resource> p_ref) const
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		return DirAccess::remove_absolute(p_ref->get_path());
	}

	return Error::ERR_UNAVAILABLE;
}

bool GGSResourceManager::save_resource(Ref<EquipmentSlot> p_ref) const
{
	return save_resource(String(EQUIPMENT_DIR), p_ref) == Error::OK;
}

bool GGSResourceManager::save_resource(Ref<ItemsPool> p_ref) const
{
	return save_resource(String(ITEMS_DIR), p_ref) == Error::OK;
}

bool GGSResourceManager::save_resource(Ref<TagDictionary> p_ref) const
{
	return save_resource(String(TAGS_DIR), p_ref) == Error::OK;
}

Error GGSResourceManager::save_resource(const String &p_dirname, Ref<Resource> p_ref) const
{
	if (!Engine::get_singleton()->is_editor_hint())
	{
		return Error::ERR_UNAVAILABLE;
	}

	if (DirAccess::dir_exists_absolute(p_dirname) && p_ref.is_valid() && !p_ref.is_null())
	{
		WARN_PRINT("Saving resource to path: " + p_ref->get_path());
		return ResourceSaver::get_singleton()->save(p_ref, p_ref->get_path());
	}

	return Error::ERR_DOES_NOT_EXIST;
}

GGSResourceManager::GGSResourceManager()
{
	if (instance == nullptr)
	{
		instance = this;
	}
}

TypedArray<Resource> GGSResourceManager::get_resources(const String &p_dir) const
{
	TypedArray<Resource> returnvalue = TypedArray<Resource>();

	if (DirAccess::dir_exists_absolute(p_dir))
	{
		PackedStringArray files = DirAccess::open(p_dir)->get_files();
		ResourceLoader *loader = ResourceLoader::get_singleton();

		for (StringName file : files)
		{
			returnvalue.append(loader->load(p_dir + String("/") + file));
		}
	}

	return returnvalue;
}

GGSResourceManager::~GGSResourceManager()
{
	if (instance == this)
	{
		instance = nullptr;
	}
}

GGSResourceManager *GGSResourceManager::get_singleton()
{
	if (instance == nullptr)
	{
		instance = memnew(GGSResourceManager);
	}

	return instance;
}

String GGSResourceManager::get_resource_name_from_name(const String &p_string)
{
	String normalized = p_string.replace(" ", "_").to_lower();

	if (normalized.ends_with(".tres"))
	{
		return normalized;
	}

	return normalized + ".tres";
}

TypedArray<EquipmentSlot> GGSResourceManager::get_equipment_slot_resources() const
{
	return get_resources(EQUIPMENT_DIR);
}

TypedArray<ItemsPool> GGSResourceManager::get_items_pool_resources() const
{
	return get_resources(ITEMS_DIR);
}

TypedArray<TagDictionary> GGSResourceManager::get_tag_resources() const
{
	return get_resources(TAGS_DIR);
}
