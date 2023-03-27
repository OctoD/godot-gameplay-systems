@tool
class_name Inventory extends Node


signal item_activated(item: Item, activation_id: int)
signal item_added(item: Item, items: Array[Item])
signal item_removed(item: Item, items: Array[Item])


@export_category("Inventory")
## Is the path to the owner (aka the character or entity which owns the inventory).
@export_node_path("Node") var owner_path: NodePath = NodePath()
## Is the array of items.
@export var items: Array[Item] = []


func _handle_activate(item: Item, activation_id: int) -> void:
	item_activated.emit(item, activation_id)


func _ready() -> void:
	for item in items:
		if not item.activated.is_connected(_handle_activate):
			item.activated.connect(_handle_activate)


## Adds an item to the inventory and connects it's signals
func add_item(item: Item) -> void:
	items.append(item.duplicate())
	item_added.emit(item, items)
	item.activated.connect(_handle_activate)


# Counts all items
func count_items() -> int:
	return items.size()
	

## Counts all items by a given predicate
func count_items_by(predicate: Callable) -> int:
	var num := 0
	
	for i in items:
		if predicate.call(i):
			num += 1
	
	return num


## Removes an item from the inventory and disconnects it's signals
func remove_item(item: Item) -> void:
	var index = items.find(item)
	
	if index >= 0:
		items.remove_at(index)
		
		if item.activated.is_connected(_handle_activate):
			item.activated.disconnect(_handle_activate)
		
