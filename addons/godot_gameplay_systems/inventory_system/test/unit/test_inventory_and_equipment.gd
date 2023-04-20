extends GutTest


func _make_ei() -> Dictionary:
	var equipment = _make_equipment()
	var inventory = _make_inventory()
	
	equipment.inventory_path = inventory.get_path()
	inventory.equipment_path = equipment.get_path()
	
	inventory.setup()
	equipment.setup()
	inventory.setup()
	equipment.setup()
	
	return { "equipment": equipment, "inventory": inventory }


func _make_equipment() -> Equipment:
	var equipment = Equipment.new()
	watch_signals(equipment)
	add_child_autofree(equipment)
	return equipment


func _make_inventory() -> Inventory:
	var inventory = Inventory.new()
	watch_signals(inventory)
	add_child_autofree(inventory)
	return inventory


func _make_item(name: String = "item_" + str(randf())) -> Item:
	var item = Item.new()
	item.name = name
	return item
	

func after_each() -> void:
	clear_signal_watcher()


func _make_slot(slot_name: String = "test", accepted_items: Array[Item] = []) -> EquipmentSlot:
	var slot = EquipmentSlot.new(accepted_items)
	slot.name = slot_name
	return slot


func test_assignments() -> void:
	var dict = _make_ei()
	var equipment = dict.equipment as Equipment
	var inventory = dict.inventory as Inventory
	
	assert_ne(equipment.inventory, null, "inventory should not be null")
	assert_ne(inventory.equipment, null, "equipment should not be null")


func test_automatic_item_equipping() -> void:
	var dict = _make_ei()
	var equipment = dict.equipment as Equipment
	var inventory = dict.inventory as Inventory
	var item000 = _make_item("item000")
	var item001 = _make_item("item001")
	var slot = _make_slot("test", [item000, item001])
	
	equipment.gameplay_equip_automatically = true
	equipment.slots.append(slot)
	
	var added = inventory.add_item(item000)
	
	assert_signal_emitted(inventory, "item_added", "item_added should have been emitted")
	assert_signal_not_emitted(inventory, "refused_to_add", "refused_to_add should have not been emitted")
	assert_signal_not_emitted(equipment, "refused_to_equip", "refused_to_equip should have not been emitted")
	assert_ne(equipment.equipped_items.size(), 0, "equipped items should not be 0")
	assert_eq(equipment.equipped_items[0].name, item000.name, "equipped item is not item000")

	inventory.add_item(item001)

	assert_eq(equipment.equipped_items[0].name, item000.name, "equipped item should remain item000")

	inventory.remove_item(added)
	
	assert_signal_not_emitted(inventory, "refused_to_remove", "item_refused_to_remove should have not been called")
	assert_signal_emitted(inventory, "item_removed", "item_removed should have been called")
	
	assert_eq(equipment.equipped_items.size(), 0, "equipped items should be 0")
	assert_eq(inventory.items.size(), 1, "inventory items size should be 1")
	
	clear_signal_watcher()
	
