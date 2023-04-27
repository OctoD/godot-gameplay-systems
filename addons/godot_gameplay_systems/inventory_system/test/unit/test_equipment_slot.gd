extends GutTest

var item000 = Item.new()
var item001 = Item.new()
var item002 = Item.new()


func _init() -> void:
	item000.name = "item000"
	item001.name = "item001"
	item002.name = "item002"


func test_init() -> void:
	var eq000 = EquipmentSlot.new([item000, item001], item002) # slot.equipped should be null at this point
	var eq001 = EquipmentSlot.new([item001, item002], item002) # slot.equipped should be item002 at this point
	
	assert_eq_deep(eq000.accepted_items, [item000, item001])
	assert_eq_deep(eq001.accepted_items, [item001, item002])
	assert_eq(eq000.equipped, null, "current item on eq000 should be null, check _init fn")
	assert_eq(eq001.equipped, item002, "current item on eq000 should be item002, check _init fn")


func test_equip() -> void:
	var eq = EquipmentSlot.new([item000, item001])
	
	watch_signals(eq)
	
	assert_eq(eq.can_equip(item000), true, "item should be accepted")
	assert_eq(eq.can_equip(item002), false, "item should not be accepted")
	
	eq.equip(item000)
	
	assert_signal_emitted(eq, "item_equipped", "equipped signal should have been emitted")
	assert_eq(eq.equipped, item000, "equipped item should not be null")
	
	eq.equip(item002)

	assert_signal_emitted(eq, "item_refused_to_equip", "item_refused_to_equip signal should have been emitted, since item002 is not listed by EquipmentSlot instance")
	assert_eq(eq.equipped, item000, "equipped item should be the previously equipped one, because it cannot be accepted")
	
	eq.unequip()
	
	assert_signal_emitted(eq, "item_unequipped", "item_unequipped should have been emitted")
	assert_eq(eq.equipped, null, "equipped item should be null since it has been unequipped")
	
	eq.unequip()
	
	assert_signal_emit_count(eq, "item_unequipped", 1, "item_unequipped should have not been called twice since current item is already null")
