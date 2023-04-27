extends GutTest


# A test class. Tests activation.
class SubItem extends Item:
	enum SubItemActivation {
		OK,
		NOPE
	}
	
	func _init() -> void:
		name = "SubItem test"

	func _can_activate(event: ItemActivationEvent) -> bool:
		return event.activation_type == SubItemActivation.OK


func make_inventory() -> Inventory:
	var instance = Inventory.new()
	add_child_autofree(instance)
	return instance


func before_each() -> void:
	clear_signal_watcher()


func test_add_item_to_inventory() -> void:
	var item = Item.new()
	var inventory = make_inventory()
	item.name = "test"
	inventory.add_item(item)
	assert_eq(inventory.items.size(), 1, "Item has been added")
	assert_eq(inventory.items[0].name, item.name, "Item has same name")


func test_item_can_activate() -> void:
	var inventory = make_inventory()
	watch_signals(inventory)
	
	var item = SubItem.new()
	var x = inventory.add_item(item)
	
	inventory.activate(x, SubItem.SubItemActivation.OK)
	
	assert_signal_emitted(inventory, "item_activated", "item not activated")
	assert_signal_emit_count(inventory, "item_activated", 1, "item not activated")
	
	inventory.activate(x, SubItem.SubItemActivation.NOPE)
	
	assert_signal_emit_count(inventory, "item_activated", 1, "item activated, this should have been blocked by [Item.can_activate]")
	clear_signal_watcher()


func test_tagging() -> void:
	var inventory = make_inventory()
	var item = Item.new()
	var tags_added_on_activation = "tags_added_on_activation"
	var tags_added_on_add = "tags_added_on_add"
	var tags_added_on_remove = "tags_added_on_remove"
	var tags_removed_on_activation = "tags_removed_on_activation"
	var tags_removed_on_add = "tags_removed_on_add"
	var tags_removed_on_remove = "tags_removed_on_remove"
	
	inventory.tags.append_array([
		tags_removed_on_activation,
		tags_removed_on_add,
		tags_removed_on_remove,
	])
	
	item.tags_added_on_activation.append(tags_added_on_activation)
	item.tags_added_on_add.append(tags_added_on_add)
	item.tags_added_on_remove.append(tags_added_on_remove)
	item.tags_removed_on_activation.append(tags_removed_on_activation)
	item.tags_removed_on_add.append(tags_removed_on_add)
	item.tags_removed_on_remove.append(tags_removed_on_remove)
	
	var added_item = inventory.add_item(item)
	
	assert_eq(inventory.tags.has(tags_added_on_add), true, "tags_added_on_add are not set")
	assert_eq(not inventory.tags.has(tags_removed_on_add), true, "tags_removed_on_add are set")
	assert_eq(not inventory.tags.has(tags_added_on_activation), true, "tags_added_on_activation are set")
	assert_eq(not inventory.tags.has(tags_added_on_remove), true, "tags_added_on_remove are set")
	assert_eq(inventory.tags.has(tags_removed_on_activation), true, "tags_removed_on_activation are not set")
	assert_eq(inventory.tags.has(tags_removed_on_remove), true, "tags_removed_on_remove are not set")
	
	inventory.activate(added_item)
	
	assert_eq(inventory.tags.has(tags_added_on_activation), true, "tags_added_on_activation are not set")
	assert_eq(not inventory.tags.has(tags_removed_on_activation), true, "tags_removed_on_activation are set")
	assert_eq(inventory.tags.has(tags_removed_on_remove), true, "tags_removed_on_remove are not set")
	
	inventory.remove_item(added_item)
	
	assert_eq(inventory.items.size(), 0, "item has not been removed")
	
	assert_eq(inventory.tags.has(tags_added_on_remove), true, "tags_added_on_remove are not set")
	assert_eq(not inventory.tags.has(tags_removed_on_remove), true, "tags_removed_on_remove are set")


func test_signals() -> void:
	var inventory = make_inventory()
	watch_signals(inventory)
	
	var item = Item.new()
	var added = inventory.add_item(item)
	
	inventory.activate(added)
	inventory.remove_item(added)
	
	assert_signal_emitted_with_parameters(inventory, "item_activated", [added, 0])
	assert_signal_emitted_with_parameters(inventory, "item_added", [added])
	assert_signal_emitted_with_parameters(inventory, "item_removed", [added])


func test_stacking() -> void:
	var inventory = make_inventory()
	watch_signals(inventory)
	
	var _make_item = func () -> Item:
		var item = Item.new()
		
		item.name = "foo"
		item.can_stack = true
		item.decrease_stack_on_use = true
		item.quantity_max = 3
		
		return item
	
	var iteration = 0
	
	while iteration < 7:
		var i = _make_item.call()
		inventory.add_item(i)
		iteration += 1
	
	# let's say we pickup 7 items of the same type, so we will find three items in total inside the inventory
	# two with the full stack, one with a 1/3 of stack 
	assert_eq(inventory.items.size(), 3, "issue with stacking")
	assert_eq(inventory.items[0].quantity_current, 3, "first item quantity should be 3")
	assert_eq(inventory.items[1].quantity_current, 3, "first item quantity should be 3")
	assert_eq(inventory.items[2].quantity_current, 1, "first item quantity should be 1")
	
	# now let's say we want to use six of them, based on their array indexes (aka looping them), 
	# we should find ourselves with just one stacked item with quantity_current set to 1
	
	iteration = 0
	
	while iteration < 6:
		inventory.activate(inventory.items[0])
		iteration += 1

	assert_eq(inventory.items.size(), 1, "issue with unstacking")
	assert_eq(inventory.items[0].quantity_current, 1, "issue with quantities")
	assert_signal_emitted(inventory, "item_depleted", "signal not emitted but it should, since at least one stack has been depleted by activate")


# just a test class
class TestItem000 extends Item:
	func _init() -> void:
		can_stack = true
		quantity_max = 4
		name = "TestItem000"
	

# omg another test class
class TestItem001 extends Item:
	func _init() -> void:
		name = "TestItem001"


func test_filter_by() -> void:
	var inventory = make_inventory()
	# Adds four TestItem000, which will result in a single stack of 4/4
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	# Adds five TestItem001, which will result in five stacks of 1/1
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	
	assert_eq(inventory.items.size(), 6, "size is not 6, check stacking algo")
	
	var found000 = inventory.filter_by(func (x: Item): return x is TestItem000)
	var found001 = inventory.filter_by(func (x: Item): return x is TestItem001)
	
	assert_eq(found000.size(), 1, "filter_by is wrong")
	assert_eq(found001.size(), 5, "filter_by is wrong")
	
	
func test_find_by() -> void:
	var inventory = make_inventory()
	# Adds four TestItem000, which will result in a single stack of 4/4
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	# Adds five TestItem001, which will result in five stacks of 1/1
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	
	var found000 = inventory.find_by(func (x: Item): return x.quantity_current > 1)
	var found001 = inventory.find_by(func (x: Item): return x.quantity_current > 1 and x is TestItem001)
	
	assert_eq(found000 != null, true, "find_by is wrong")
	assert_eq(found001 == null, true, "find_by is wrong")


func test_count() -> void:
	var inventory = make_inventory()
	# Adds four TestItem000, which will result in a single stack of 4/4
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	# Adds five TestItem001, which will result in five stacks of 1/1
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	
	# count should be 6, since it stacks
	assert_eq(inventory.count_items(), 6, "stacking count is wrong")
	# count should be 9, since it adds stacks to the items count
	assert_eq(inventory.count_items(true), 9, "stacking count is wrong")


func test_count_by() -> void:
	var inventory = make_inventory()
	# Adds four TestItem000, which will result in a single stack of 4/4
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	inventory.add_item(TestItem000.new())
	# Adds five TestItem001, which will result in five stacks of 1/1
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())
	inventory.add_item(TestItem001.new())


	var predicate = func (x: Item): return x is TestItem000

	assert_eq(inventory.count_items_by(predicate), 1, "stacked count failed")
	assert_eq(inventory.count_items_by(predicate, true), 4, "aggregated count failed")
	

# Tests _ready fn
func test_ready() -> void:
	var inventory = make_inventory()
	var item = Item.new()
	var tags = ["hello", "world"]

	item.tags_added_on_add.append_array(tags)

	inventory.items.append(item)
	inventory._ready()

	assert_eq_deep(inventory.tags, tags)
