#include "equipment_manager.h"
#include "equipment_project_settings.h"
#include "system/tag/tag_dictionary.h"

#include <godot_cpp/classes/resource_loader.hpp>

using namespace ggs;

EquipmentManager *EquipmentManager::singleton = nullptr;

void EquipmentManager::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("get_slots"), &EquipmentManager::get_slots);

	/// signals bindings
	ADD_SIGNAL(MethodInfo("slot_added", PropertyInfo(Variant::STRING, "slot")));
	ADD_SIGNAL(MethodInfo("slot_removed", PropertyInfo(Variant::STRING, "slot")));
	ADD_SIGNAL(MethodInfo("slot_renamed", PropertyInfo(Variant::STRING, "slot"), PropertyInfo(Variant::STRING, "new_slot")));
}

void EquipmentManager::add_slot(EquipmentSlot *p_slot)
{
	if (!has_slot_by_instance(p_slot))
	{
		slots.append(p_slot);
		emit_signal("slot_added", p_slot->get_slot_name());
	}
}

bool EquipmentManager::has_slot_by_instance(EquipmentSlot *p_slot) const
{
	if (p_slot == nullptr)
	{
		return false;
	}

	return has_slot(p_slot->get_slot_name());
}

void EquipmentManager::remove_slot(EquipmentSlot *p_slot)
{
	if (has_slot_by_instance(p_slot))
	{
		int index = -1;

		for (int i = 0; i < slots.size(); i++)
		{
			Variant slot_variant = slots[i];
			Ref<EquipmentSlot> slot_ptr = cast_to<EquipmentSlot>(slot_variant);

			if (slot_ptr.is_valid())
			{
				if (slot_ptr->get_slot_name() == p_slot->get_slot_name())
				{
					index = i;
					break;
				}
			}
		}

		if (index > -1)
		{
			slots.remove_at(index);
			emit_signal("slot_removed", p_slot->get_slot_name());
		}
	}
}

void EquipmentManager::load_slots()
{
	PackedStringArray slots_paths = EquipmentProjectSettings::get_resource_file_paths();
	ResourceLoader *resource_loader = ResourceLoader::get_singleton();

	if (resource_loader != nullptr)
	{
		for (StringName slot_path : slots_paths)
		{
			Ref<Resource> resource = resource_loader->load(slot_path);

			if (resource.is_valid())
			{
				EquipmentSlot *slots_ptr = cast_to<EquipmentSlot>(resource.ptr());

				if (slots_ptr != nullptr)
				{
					slots.append(slots_ptr);
				}
			}
		}
	}
}

EquipmentManager::EquipmentManager()
{
	if (singleton == nullptr)
	{
		singleton = this;
	}
	else
	{
		slots = singleton->slots;
	}
}

EquipmentManager::~EquipmentManager()
{
	if (singleton == this)
	{
		memdelete(singleton);
		singleton = nullptr;
	}
}

void EquipmentManager::_ready()
{
	load_slots();
}

bool EquipmentManager::can_accept(Item *p_item) const
{
	return false;
}

bool EquipmentManager::has_slot(StringName p_slot_name) const
{
	for (int i = 0; i < slots.size(); i++)
	{
		Variant slot_variant = slots[i];
		EquipmentSlot *slot_ptr = cast_to<EquipmentSlot>(slot_variant);

		if (slot_ptr != nullptr)
		{
			if (slot_ptr->get_slot_name() == p_slot_name)
			{
				return true;
			}
		}
	}
	
    return false;
}

EquipmentManager *EquipmentManager::get_singleton()
{
	if (singleton == nullptr)
	{
		singleton = memnew(EquipmentManager);
	}

	return singleton;
}

PackedStringArray EquipmentManager::get_slots() const
{
	PackedStringArray slot_names = PackedStringArray();

	for (int i = 0; i < slots.size(); i++)
	{
		Variant slot_variant = slots[i];
		EquipmentSlot *slot_ptr = cast_to<EquipmentSlot>(slot_variant);

		if (slot_ptr != nullptr)
		{
			slot_names.append(slot_ptr->get_slot_name());
		}
	}

	return slot_names;
}