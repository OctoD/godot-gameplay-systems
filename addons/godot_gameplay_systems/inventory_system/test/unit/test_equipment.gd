extends GutTest

var item000 = Item.new()
var item001 = Item.new()
var item002 = Item.new()
var item003 = Item.new()

var slot000 = EquipmentSlot.new([item000, item001])
var slot001 = EquipmentSlot.new([item001, item002])

var slots = [
	slot000,
	slot001,
]


func _init() -> void:
	item000.name = "item000"
	item001.name = "item001"
	item002.name = "item002"
	item003.name = "item003"


func before_each() -> void:
	clear_signal_watcher()


func make_equipment() -> Equipment:
	var instance = Equipment.new()
	instance.slots.append_array(slots)
	add_child_autofree(instance)
	return instance


## Tests only the .new method
func test_equipment_slot_init() -> void:
	var equipment = make_equipment()
	
	assert_eq_deep(equipment.slots, slots)


## Tests basic equip/unequip methods
func test_equip_unequip_methods() -> void:
	var eq = make_equipment()
	var has_equipped = func (x): return x.equipped != null
	
	watch_signals(eq)

	eq.equip(item000)
	
	assert_eq(eq.slots.any(has_equipped), true, "at least one slot should have an equipped item")
	assert_signal_emitted(eq, "equipped", "equipped signal should be emitted")

	eq.unequip(item000)

	assert_eq(eq.slots.any(has_equipped), false, "all slots should have not an equipped item")
	assert_signal_emitted(eq, "unequipped", "item should have been unequipped properly")
	
	eq.equip(item000)
	eq.unequip_all()
	
	assert_eq(eq.slots.any(has_equipped), false, "all slots should have not an equipped item")
	
	eq.equip(item003)
	
	assert_eq(eq.slots.any(has_equipped), false, "item should have been refused")
	assert_signal_emitted(eq, "refused_to_equip", "refused_to_equip should have been emitted")


func test_activation() -> void:
	var eq = make_equipment()
	watch_signals(eq)
	
	eq.activate(item000)
	
	assert_signal_not_emitted(eq, "item_activated", "the item is not equipped yet")
	
	eq.equip(item000)
	eq.activate(item000)
	
	assert_signal_emitted(eq, "item_activated", "the item should have been activated")


## Tests tagging lifecycle
func test_tagging_system() -> void:
	var eq = make_equipment()
	var test_item = item000.duplicate()
	var tags_added_on_activation = "tags_added_on_activation"
	var tags_added_on_equip = "tags_added_on_equip"
	var tags_added_on_unequip = "tags_added_on_unequip"
	var tags_removed_on_activation = "tags_removed_on_activation"
	var tags_removed_on_equip = "tags_removed_on_equip"
	var tags_removed_on_unequip = "tags_removed_on_unequip"
	
	var expected_tags = [
		tags_added_on_equip,
		tags_added_on_activation,
		tags_added_on_unequip,
	]
	
	eq.tags.append_array([
		tags_removed_on_equip,
		tags_removed_on_activation,
		tags_removed_on_unequip,
	])
	
	test_item.tags_added_on_activation.append(tags_added_on_activation)
	test_item.tags_added_on_equip.append(tags_added_on_equip)
	test_item.tags_added_on_unequip.append(tags_added_on_unequip)
	test_item.tags_removed_on_equip.append(tags_removed_on_equip)
	test_item.tags_removed_on_unequip.append(tags_removed_on_unequip)
	test_item.tags_removed_on_activation.append(tags_removed_on_activation)
	
	eq.equip(test_item)
	eq.activate(test_item)
	eq.unequip(test_item)
	
	assert_eq_deep(eq.tags, expected_tags)


# this emulates the character picking up a weapon
func test_tagging_block_tags()->void:
	var eq = make_equipment()
	var itemA = item000.duplicate() as Item
	var requiredA = "item000.aquired"
	
	watch_signals(eq)
	
	itemA.tags_required_to_equip.append(requiredA)
	
	eq.equip(itemA)
	
	assert_eq(eq.equipped_items.size(), 0, "itemA should have not been equipped because of it's requirements")
	assert_signal_emitted(eq, "refused_to_equip", "trying to equip itemA should emit refused_to_equip")
	assert_signal_not_emitted(eq, "equipped", "equipping itemA should not emit equipped")
	assert_eq(eq.is_equipped(itemA), false, "itemA should not be equipped")
	
	eq.add_tag(requiredA)
	
	eq.equip(itemA)
	assert_eq(eq.is_equipped(itemA), true, "itemA should be equipped now")
	assert_signal_emitted(eq, "equipped", "equipping itemA should emit equipped")
