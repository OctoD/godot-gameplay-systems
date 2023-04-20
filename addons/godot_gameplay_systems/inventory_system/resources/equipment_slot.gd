@tool
class_name EquipmentSlot extends Resource


## Represents an equipment slot.


## Emitted when an [Item] is equipped.
## [br]Note, this will always be emitted after the [signal EquipmentSlot.unequipped_item] signal if a previous [Item] was equipped.
signal item_equipped(item: Item, slot: EquipmentSlot)
## Emitted if the [Item] passed to [method EquipmentSlot.equip] method is not acceptable.
signal item_refused_to_equip(item: Item, slot: EquipmentSlot)
## Emitted when an [Item] is unequipped.
signal item_unequipped(item: Item, slot: EquipmentSlot)


@export_category("Slot")
## The name given to this slot.
## [br]It is useful to be queried by [method Equipment.activate_by_name] method.
@export var name: String = ""
## A white-list [Array] of accepted [Item]s.
## [br]Note: if this array is empty, all [Item]s will be eligible to be equipped, so beware.
@export var accepted_items: Array[Item] = []
## The current equipped [Item]
@export var equipped: Item = null


## [br]Is [code]true[/code] if an [Item] is equipped, [code]false[/code] otherwise.
var has_equipped_item: bool:
	get:
		return equipped != null
## [br]Is [code]true[/code] if no [Item] are equipped, [code]false[/code] otherwise.
var is_free: bool:
	get:
		return equipped == null


func _init(_accepted_items: Array[Item] = [], _equipped_item: Item = null) -> void:
	accepted_items = _accepted_items
	
	if can_equip(_equipped_item):
		equipped = _equipped_item


## Determines if the slot can accept an [Item]
func can_equip(item: Item) -> bool:
	if item == null:
		return false
	
	if accepted_items.size() == 0:
		return true
	
	for accepted in accepted_items:
		if accepted.name == item.name:
			return true
	
	return false


## Equips an [Item]
func equip(item: Item) -> void:
	if item == null:
		return

	if not can_equip(item):
		item_refused_to_equip.emit(item, self)
		return

	if has_equipped_item:
		item_unequipped.emit(equipped, self)
		equipped = null

	equipped = item
	item_equipped.emit(item, self)


## Unequips an [Item] if any.
## [br]If there is an equipped item, the signal [signal EquipmentSlot.item_unequipped] will be emitted.
func unequip() -> void:
	if has_equipped_item:
		item_unequipped.emit(equipped, self)
		equipped = null
