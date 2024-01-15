#include <godot_cpp/classes/engine.hpp>

#include "Item.h"

using namespace ggs;

void ItemStack::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("get_item"), &ItemStack::get_item);
	ClassDB::bind_method(D_METHOD("get_max_quantity"), &ItemStack::get_max_quantity);
	ClassDB::bind_method(D_METHOD("get_quantity"), &ItemStack::get_quantity);
	ClassDB::bind_method(D_METHOD("set_item", "p_item"), &ItemStack::set_item);
	ClassDB::bind_method(D_METHOD("set_max_quantity", "p_max_quantity"), &ItemStack::set_max_quantity);
	ClassDB::bind_method(D_METHOD("set_quantity", "p_quantity"), &ItemStack::set_quantity);

	/// properties binding
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "item", PROPERTY_HINT_RESOURCE_TYPE, "Item"), "set_item", "get_item");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "max_quantity"), "set_max_quantity", "get_max_quantity");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "quantity"), "set_quantity", "get_quantity");
}

Ref<Item> ItemStack::get_item() const
{
    return Ref<Item>(item);
}

int ItemStack::get_max_quantity() const
{
    return 0;
}

void ItemStack::set_item(Item *p_item)
{
	item = p_item;
}

void ItemStack::set_max_quantity(int p_max_quantity)
{
}

int ItemStack::get_quantity() const
{
    return quantity;
}

void ItemStack::set_quantity(int p_quantity)
{
	quantity = p_quantity;
}

void ItemStackSetting::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("get_stacking_type"), &ItemStackSetting::get_stacking_type);
	ClassDB::bind_method(D_METHOD("get_maximum_stack_size"), &ItemStackSetting::get_maximum_stack_size);
	ClassDB::bind_method(D_METHOD("set_maximum_stack_size", "p_maximum_stack_size"), &ItemStackSetting::set_maximum_stack_size);
	ClassDB::bind_method(D_METHOD("set_stacking_type", "p_stacking_type"), &ItemStackSetting::set_stacking_type);

	/// properties binding
	ADD_PROPERTY(PropertyInfo(Variant::INT, "stacking_type", PROPERTY_HINT_ENUM, "Finite,Infinite"), "set_stacking_type", "get_stacking_type");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "maximum_stack_size"), "set_maximum_stack_size", "get_maximum_stack_size");
}

int ItemStackSetting::get_maximum_stack_size() const
{
    return maximum_stack_size;
}

ItemStackSetting::StackingType ItemStackSetting::get_stacking_type() const
{
	return (ItemStackSetting::StackingType)stacking_type;
}

void Item::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("get_stack_setting"), &Item::get_stack_setting);
	ClassDB::bind_method(D_METHOD("set_stack_setting", "p_stack_setting"), &Item::set_stack_setting);

	/// properties binding
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "stack_setting", PROPERTY_HINT_RESOURCE_TYPE, "ItemStackSetting"), "set_stack_setting", "get_stack_setting");
}

ItemStackSetting *Item::get_stack_setting() const
{
	return stack_setting;
}

void ItemStackSetting::set_maximum_stack_size(int p_maximum_stack_size)
{
	maximum_stack_size = p_maximum_stack_size;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void ItemStackSetting::set_stacking_type(ItemStackSetting::StackingType p_stacking_type)
{
	stacking_type = p_stacking_type;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}

void Item::set_stack_setting(ItemStackSetting *p_stack_setting)
{
	stack_setting = p_stack_setting;

	if (Engine::get_singleton()->is_editor_hint())
	{
		emit_changed();
	}
}
