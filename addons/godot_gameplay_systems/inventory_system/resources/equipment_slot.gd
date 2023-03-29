@tool
class_name EquipmentSlot extends Resource


## Represents an equipment slot.


## Emitted when an [Item] is equipped.
## [br]Note, this will always be emitted after the [signal EquipmentSlot.unequipped_item] signal if a previous [Item] was equipped.
signal item_equipped(item: Item)
## Emitted when an [Item] is unequipped.
signal item_unequipped(item: Item)


@export_category("Slot")
## The name given to this slot.
## [br]It is useful to be queried by [method Equipment.activate_by_name] method.
@export var name: String = ""
## An [Array] of accepted [Item]s.
@export var accepted_items: Array[Item] = []
## The current equipped [Item]
@export var current: Item = null


## [br]Is [code]true[/code] if an [Item] is equipped, [code]false[/code] otherwise.
var has_equippend_item: bool:
	get:
		return current != null
## [br]Is [code]true[/code] if no [Item] are equipped, [code]false[/code] otherwise.
var is_free: bool:
	get:
		return current == null


func _init(_accepted_items: Array[Item] = [], _equipped_item: Item = null) -> void:
	accepted_items = _accepted_items
	current = _equipped_item


## Determines if the slot can accept an [Item]
func can_accept(item: Item) -> bool:
	return accepted_items.any(func (x: Item): x.name == item.name)


## Determines if an [Item] can be equipped or not.
func can_equip(item: Item) -> bool:
	return item.tags_added_on_add


## Equips an [Item]
func equip(item: Item) -> void:
	if has_equippend_item:
		item_unequipped.emit(current)
		current = null

	current = item
	item_equipped.emit(item)


## Unequips an [Item] if any.
## [br]If there is an equipped item, the signal [signal EquipmentSlot.item_unequipped] will be emitted.
func unequip() -> void:
	if has_equippend_item:
		item_unequipped.emit(current)
		current = null
