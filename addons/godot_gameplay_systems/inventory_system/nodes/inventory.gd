@icon("res://addons/godot_gameplay_systems/inventory_system/assets/InventoryIcon.png")
@tool
class_name Inventory extends Node


## Represents an inventory.
##
## Note: an Inventory should be unique for a character.


enum LifeCycle {
	## An [Item] has been activated.
	Activated = 0,
	## An [Item] has been added to the inventory.
	Added = 1,
	## An [Item] has been removed from an inventory.
	Removed = 2,
}


## Emitted when an [Item] is properly activated with a specific activation type.
signal item_activated(item: Item, activation_type: int)
## Emitted when an [Item] has been added to this inventory.
signal item_added(item: Item)
## Emitted when an [Item] has been activated and it's own stack has been consumed entirely.
signal item_depleted(item: Item)
## Emitted when an [Item] has been removed from this inventory.
signal item_removed(item: Item)
## Emitted when the [Inventory] refuses to add an [Item] because of lacking tags.
signal refused_to_add(item: Item)
## Emitted when the [Inventory] refuses to remove an [Item] because of lacking tags.
signal refused_to_remove(item: Item)


@export_category("Inventory")
## Is the path to the owner (aka the character or entity which owns the inventory).
@export_node_path("Node2D", "Node3D") var owner_path: NodePath = NodePath()
## Is the path to the related [Equipment] node. 
## [br]This is not necessary unless you want to make this [Inventory] to talk with an [Equipment] automatically.
## [br]For example: a classic Doom/Quake-like game, will not have an inventory system, 
## all weapons are set at startup and can be used only if some tags are set.
@export_node_path("Equipment") var equipment_path: NodePath = NodePath()
## Is the array of items.
@export var items: Array[Item] = []
## Tags associated to this [Inventory]
@export var tags: Array[String] = []

## Related [Equipment] node if any.
var equipment: Equipment


## Internal method. Handles all life cycle events managing the tagging system.
func _handle_lifecycle_tags(life_cycle: LifeCycle, item: Item) -> void:
	assert(item != null, "Item cannot be null")

	match life_cycle:
		LifeCycle.Activated:
			add_tags(item.tags_added_on_activation)
			remove_tags(item.tags_removed_on_activation)
		LifeCycle.Added:
			add_tags(item.tags_added_on_add)
			remove_tags(item.tags_removed_on_add)
		LifeCycle.Removed:
			add_tags(item.tags_added_on_remove)
			remove_tags(item.tags_removed_on_remove)


## Ready function. Adds all starting [member Item.tags_added_on_add] when the node is ready.
func _ready() -> void:
	setup()
	


## Activates an [Item] with an optional [code]activation_type[/code].
## Activation can occur only if [method Item._can_activate] returns [code]true[/code].
func activate(item: Item, activation_type: int = 0) -> void:
	var activation_event = ItemActivationEvent.new(self, activation_type)

	if item._can_activate(activation_event):
		item._activate(activation_event)
		item_activated.emit(item, activation_type)
		_handle_lifecycle_tags(LifeCycle.Activated, item)
		
		if item.can_stack and item.decrease_stack_on_use:
			item.quantity_current = clampi(item.quantity_current - 1, 0, item.quantity_current)
			
			if item.quantity_current == 0:
				var index = items.find(item)

				if index >= 0:
					items.remove_at(index)
					item_depleted.emit(item)


## Adds an item to the inventory and connects it's signals
## [br][Item] is duplicated when added. If an [Item] has [member Item.can_stack], it will stack [member Item.quantity_current] until [member Item.quantity_max] is reached.
## [br]If the quantity exceed the maximum, another [Item] will be added to the inventory with the difference in stacks.
## [br]Returns the copied [Item].
## [br]Note: always check it the [Item] is [code]null[/code] or not, since it could not be added if some tags requirements are not met.
func add_item(item: Item) -> Item:
	if not can_add(item):
		refused_to_add.emit(item)
		return null
	
	# Finds the first item which is already in the inventory, is stackable and it's own stack is not at the maximum quantity.
	var found = find_by(func (x: Item): return item.name == x.name and x.can_stack and x.quantity_current < x.quantity_max)

	# Check if there's another [Item] in the inventory and if is stackable.
	if found and found.can_stack:
		var new_quantity = found.quantity_current + item.quantity_current

		# It's not stackable to an infinite value
		if found.quantity_max != 0:
			found.quantity_current = clampi(new_quantity, 0, found.quantity_max)

			if new_quantity > found.quantity_max:
				var duplicated_item = found.duplicate() as Item

				duplicated_item.quantity_current = new_quantity - found.quantity_max

				return add_item(duplicated_item)
		# Stacking it to infinite value
		else:
			found.quantity_current = new_quantity
		item_added.emit(found)
		return found
	
	var item_to_return = item.duplicate()
	items.append(item_to_return)

	item_added.emit(item_to_return)

	_handle_lifecycle_tags(LifeCycle.Added, item_to_return)

	return item_to_return


## Adds many items. 
func add_items(_items: Array[Item]) -> Array[Item]:
	var out: Array[Item] = []
	
	for i in _items:
		out.append(add_item(i))
		
	return out


## Adds a tag to [member Inventory.tags].
## [br]Duplicated tags are discarded
func add_tag(tag: String) -> void:
	if tag == null:
		return
	
	if not tags.has(tag):
		tags.append(tag)


## Adds many tags to [member Inventory.tags].
## [br]Duplicated tags are discarded
func add_tags(_tags: Array[String]) -> void:
	if _tags.size() == 0:
		return
	
	for t in _tags:
		if not tags.has(t):
			tags.append(t)


## Checks if an item can be activated with an optional activation id.
func can_activate(item: Item, activation_type: int = 0) -> bool:
	if item.tags_required_to_activate.size() > 0:
		for tag in item.tags_required_to_activate:
			if not tags.has(tag):
				return false
	
	return item._can_activate(ItemActivationEvent.new(self, activation_type))


## Checks if an [Item] can be added to this [Inventory] checking if all [member Item.tags_required_to_add] exists in this [Inventory]
func can_add(item: Item) -> bool:
	if item.tags_required_to_add.size() == 0:
		return true

	for tag in item.tags_required_to_add:
		if not tags.has(tag):
			return false

	return true


## Checks if an [Item] can be added from this [Inventory] checking if all [member Item.tags_required_to_remove] exists in this [Inventory]
func can_remove(item: Item) -> bool:
	if item.tags_required_to_remove.size() == 0:
		return true

	for tag in item.tags_required_to_remove:
		if not tags.has(tag):
			return false

	return true

## Counts all items.
## [br]If [code]count_stacks[/code] is passed to [code]true[/code], the count will returns also count all stacked quantities.
func count_items(count_stacks: bool = false) -> int:
	if count_stacks:
		var count = 0
		
		for item in items:
			count += item.quantity_current
			
		return count
	else:
		return items.size()
	

## Counts all items by a given predicate.
## [br]If [code]count_stacks[/code] is passed to [code]true[/code], the count will returns also count all stacked quantities.
func count_items_by(predicate: Callable, count_stacks: bool = false) -> int:
	var num := 0

	for i in items:
		if predicate.call(i):
			if count_stacks:
				num += i.quantity_current
			else:
				num += 1
	
	return num


## Filters [member Inventory.items] by the [Callable] predicate.
## [br]It returns all [Item]s which satisfy the predicate.
func filter_by(predicate: Callable) -> Array[Item]:
	var out: Array[Item] = []
	
	for i in items:
		if predicate.call(i):
			out.append(i)
	
	return out


## Find first [Item] which satisfies the [Callable] predicate and returns it.
## [br]If none are found, then returns [code]null[/code]
func find_by(predicate: Callable) -> Item:
	for i in items:
		if predicate.call(i):
			return i
	return null


## Instantiate the [member Item.scene] if any, otherwise returns [code]null[/code].
## [br]If it can be istantiated, it will try to call a [code]_from_item(item: Item, inventory: Inventory) -> void[/code] method bound to the packed scene.
func instantiate_item(item: Item) -> Node:
	if item.scene != null and item.scene.can_instantiate():
		var instance = item.scene.instantiate()
		
		if instance.has_method("_from_item"):
			instance.call("_from_item", item, self)
		
		return instance
	
	return null

	
## Removes an item from the inventory
## [br]If [code]bypass_tag_check[/code] is set to [code]true[/code] then the check for [member Item.tags_required_to_remove] will not be performed.
func remove_item(item: Item, bypass_tag_check: bool = false) -> void:
	if not can_remove(item) and not bypass_tag_check:
		refused_to_remove.emit(item)
		return

	var index = items.find(item)

	if index >= 0:
		items.remove_at(index)
		item_removed.emit(item)
		_handle_lifecycle_tags(LifeCycle.Removed, item)


## Removes many items from an inventory
## [br]If [code]bypass_tag_check[/code] is set to [code]true[/code] then the check for [member Item.tags_required_to_remove] will not be performed.
func remove_items(_items: Array[Item], bypass_tag_check: bool = false) -> void:
	for i in _items:
		remove_item(i)


## Removes items using a [Callable] predicate. If the predicate is satisfied by the [Item], the [Item] is going to be removed entirely.
## [br]If [code]bypass_tag_check[/code] is set to [code]true[/code] then the check for [member Item.tags_required_to_remove] will not be performed.
func remove_items_by(predicate: Callable, bypass_tag_check: bool = false) -> void:
	for i in items:
		if predicate.call(i):
			remove_item(i, bypass_tag_check)


## Removes a tag.
func remove_tag(tag: String) -> void:
	if tags.has(tag):
		tags.erase(tag)


## Removes many tags.
func remove_tags(_tags: Array[String]) -> void:
	for t in _tags:
		if tags.has(t):
			tags.erase(t)


## Programmatically setups an [Inventory]
func setup() -> void:
	if not equipment_path.is_empty():
		equipment = get_node(equipment_path) as Equipment
	
	if not Engine.is_editor_hint() and not owner_path.is_empty():
		var _owner = get_node(owner_path)
		_owner.set_meta("ggsInventory", self)

	for i in items:
		add_tags(i.tags_added_on_add)
