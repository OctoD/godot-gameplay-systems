#include "inventory.h"
#include "equipment.h"

#include "system/tag/tag_manager.h"

using namespace ggs;

void InventoryItem::_bind_methods()
{
}

InventoryItem::InventoryItem()
{
	item_ref = Ref<Item>();
}

InventoryItem::InventoryItem(Item *p_item)
{
	item_ref = Ref<Item>(p_item);
}

InventoryItem::InventoryItem(Item *p_item, int p_quantity)
{
	item_ref = Ref<Item>(p_item);
	quantity = p_quantity;
}

InventoryItem::~InventoryItem()
{
}

Ref<InventoryItem> InventoryItem::duplicate() const
{
	if (item_ref.is_valid())
	{
		Ref<InventoryItem> duplicate = memnew(InventoryItem);

		duplicate->set_item(item_ref);
		duplicate->set_quantity(quantity);

		return duplicate;
	}

	return Ref<InventoryItem>();
}

Ref<Item> InventoryItem::get_item() const
{
	return item_ref;
}

int InventoryItem::get_quantity() const
{
	return quantity;
}

void InventoryItem::set_item(Ref<Item> p_item)
{
	item_ref = p_item;
}

void InventoryItem::set_quantity(int p_quantity)
{
	quantity = p_quantity;
}

void Inventory::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("activate", "item"), &Inventory::activate);
	ClassDB::bind_method(D_METHOD("add_item", "item"), &Inventory::add_item);
	ClassDB::bind_method(D_METHOD("can_activate", "item"), &Inventory::can_activate);
	ClassDB::bind_method(D_METHOD("can_add", "item"), &Inventory::can_add);
	ClassDB::bind_method(D_METHOD("can_drop", "item"), &Inventory::can_drop);
	ClassDB::bind_method(D_METHOD("can_equip", "item", "slot"), &Inventory::can_equip);
	ClassDB::bind_method(D_METHOD("drop_item", "item"), &Inventory::drop_item);
	ClassDB::bind_method(D_METHOD("equip_item", "item", "slot"), &Inventory::equip_item);
	ClassDB::bind_method(D_METHOD("get_equipment"), &Inventory::get_equipment);
	ClassDB::bind_method(D_METHOD("get_inventory_owner"), &Inventory::get_inventory_owner);
	ClassDB::bind_method(D_METHOD("has_equipment"), &Inventory::has_equipment);
	ClassDB::bind_method(D_METHOD("has_inventory_owner"), &Inventory::has_inventory_owner);
	ClassDB::bind_method(D_METHOD("set_equipment", "equipment"), &Inventory::set_equipment);
	ClassDB::bind_method(D_METHOD("set_inventory_owner", "owner"), &Inventory::set_inventory_owner);
	ClassDB::bind_method(D_METHOD("split_quantity", "item", "quantity"), &Inventory::split_quantity);

	/// binds properties
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "equipment", PROPERTY_HINT_RESOURCE_TYPE, "Equipment"), "set_equipment", "get_equipment");
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "inventory_owner", PROPERTY_HINT_RESOURCE_TYPE, "Node"), "set_inventory_owner", "get_inventory_owner");

	/// binds signals
	ADD_SIGNAL(MethodInfo("item_activated", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "Item")));
	ADD_SIGNAL(MethodInfo("item_added", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "Item")));
	ADD_SIGNAL(MethodInfo("item_dropped", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "Item")));
	ADD_SIGNAL(MethodInfo("item_equipped", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "Item"), PropertyInfo(Variant::STRING, "slot")));
	ADD_SIGNAL(MethodInfo("item_splitted", PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "Item"), PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "Item")));

	/// binds enum constants
	BIND_ENUM_CONSTANT(ERROR);
	BIND_ENUM_CONSTANT(ITEM_NOT_FOUND);
	BIND_ENUM_CONSTANT(ITEM_IS_NULL);
	BIND_ENUM_CONSTANT(OK);
	BIND_ENUM_CONSTANT(QUANTITY_IS_GREATER_THAN_ITEM_QUANTITY);
	BIND_ENUM_CONSTANT(QUANTITY_IS_NEGATIVE);
	BIND_ENUM_CONSTANT(QUANTITY_IS_ZERO);
}

bool Inventory::activate(Item *p_item)
{
	if (can_activate(p_item))
	{
		TagManager::get_singleton()->add_tags(this, p_item->get_item_tags()->get_tags_added_on_activation());
		TagManager::get_singleton()->remove_tags(this, p_item->get_item_tags()->get_tags_removed_on_activation());

		if (p_item->has_method("on_activate"))
		{
			p_item->call("on_activate", this);
		}

		return true;
	}

	return false;
}

bool Inventory::add_item(Item *p_item)
{
	if (can_add(p_item))
	{
		TagManager::get_singleton()->add_tags(this, p_item->get_item_tags()->get_tags_added_on_add());
		TagManager::get_singleton()->remove_tags(this, p_item->get_item_tags()->get_tags_removed_on_add());

		if (p_item->has_method("on_add"))
		{
			p_item->call("on_add", this);
		}

		items.append(p_item);
		emit_signal("item_added", p_item);

		return true;
	}

	return false;
}

bool Inventory::can_activate(Item *p_item) const
{
	if (p_item == nullptr)
	{
		return false;
	}

	if (p_item->has_method("can_activate"))
	{
		return p_item->call("can_activate", this);
	}

	return TagManager::get_singleton()->has_all_tags(this, p_item->get_item_tags()->get_tags_required_to_activate());
}

bool Inventory::can_add(Item *item) const
{
	if (item == nullptr)
	{
		return false;
	}

	if (item->has_method("can_add"))
	{
		return item->call("can_add", this);
	}

	return TagManager::get_singleton()->has_all_tags(this, item->get_item_tags()->get_tags_required_to_add());
}

bool Inventory::can_drop(Item *item) const
{
	if (item == nullptr)
	{
		return false;
	}

	if (item->has_method("can_drop"))
	{
		return item->call("can_drop", this);
	}

	return TagManager::get_singleton()->has_all_tags(this, item->get_item_tags()->get_tags_required_to_remove());
}

bool Inventory::can_equip(Item *p_item, String p_slot) const
{
	if (!has_equipment())
	{
		return false;
	}

	if (p_item == nullptr)
	{
		return false;
	}

	if (p_slot.is_empty())
	{
		return false;
	}

	if (p_item->has_method("can_equip"))
	{
		return p_item->call("can_equip", this, equipment, p_slot);
	}

	return TagManager::get_singleton()->has_all_tags(this, p_item->get_item_tags()->get_tags_required_to_equip()) && equipment->can_equip(p_item, p_slot);
}

bool Inventory::drop_item(Item *p_item)
{
	if (can_drop(p_item))
	{
		TagManager::get_singleton()->add_tags(this, p_item->get_item_tags()->get_tags_added_on_drop());
		TagManager::get_singleton()->remove_tags(this, p_item->get_item_tags()->get_tags_removed_on_drop());

		if (p_item->has_method("on_drop"))
		{
			p_item->call("on_drop", this);
		}

		int index = items.find(p_item);

		if (index >= 0)
		{
			items.remove_at(index);

			emit_signal("item_dropped", p_item);

			return true;
		}
	}

	return false;
}

bool Inventory::equip_item(Item *p_item, String p_slot)
{
	if (can_equip(p_item, p_slot))
	{
		TagManager::get_singleton()->add_tags(this, p_item->get_item_tags()->get_tags_added_on_equip());
		TagManager::get_singleton()->remove_tags(this, p_item->get_item_tags()->get_tags_removed_on_equip());

		if (p_item->has_method("on_equip"))
		{
			p_item->call("on_equip", this, equipment, p_slot);
		}

		Item *previous_equipped_item = equipment->equip(p_item, p_slot);

		emit_signal("item_equipped", p_item, p_slot);

		if (previous_equipped_item)
		{
			items.append(previous_equipped_item);

			emit_signal("item_added", previous_equipped_item);
		}

		return true;
	}

	return false;
}

Equipment *Inventory::get_equipment() const
{
	return equipment;
}

Node *Inventory::get_inventory_owner() const
{
	return inventory_owner;
}

bool Inventory::has_equipment() const
{
	return equipment != nullptr;
}

bool Inventory::has_inventory_owner() const
{
	return inventory_owner != nullptr;
}

void Inventory::set_equipment(Equipment *p_equipment)
{
	equipment = p_equipment;
}

void Inventory::set_inventory_owner(Node *p_owner)
{
	inventory_owner = p_owner;
}

Inventory::SplitError Inventory::split_quantity(InventoryItem *p_item, int p_quantity)
{
	if (p_quantity == 0)
	{
		return QUANTITY_IS_ZERO;
	}

	if (p_quantity < 0)
	{
		return QUANTITY_IS_NEGATIVE;
	}

	if (p_item == nullptr)
	{
		return ITEM_IS_NULL;
	}

	int quantity = p_item->get_quantity();

	if (p_quantity > quantity)
	{
		return QUANTITY_IS_GREATER_THAN_ITEM_QUANTITY;
	}

	if (p_quantity == quantity)
	{
		Ref<InventoryItem> duplicate = p_item->duplicate();

		for (int i = 0; i < items.size(); i++)
		{
			Variant item_variant = items[i];
			InventoryItem *item = cast_to<InventoryItem>(item_variant);

			if (item != nullptr && item == p_item)
			{
				item->set_quantity(item->get_quantity() - p_quantity);
				duplicate->set_quantity(p_quantity);

				emit_signal("item_splitted", item, duplicate);

				return OK;
			}
		}

		return ITEM_NOT_FOUND;
	}

	return ERROR;
}
