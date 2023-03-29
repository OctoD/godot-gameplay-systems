@tool
class_name Equipment extends Node


## Handles your equipped items.
##
## It uses slots to determine which item can be equippend and how.


## Emitted when an [Item] is equipped on a determined [EquipmentSlot].
signal equipped(item: Item, slot: EquipmentSlot)
## Emitted when the [Equipment] refuses to equip an [Item] because of it's own tags requirements.
signal refused_to_equip(item: Item, slot: EquipmentSlot)
## Emitted when an [Item] is unequipped on a determined [EquipmentSlot].
signal unequipped(item: Item, slot: EquipmentSlot)
## Emitted when the [Equipment] refuses to unequip an [Item] because of it's own tags requirements.
signal refused_to_unequip(item: Item, slot: EquipmentSlot)


@export_category("Equipment")
## The path to the owning character.
@export_node_path("Node2D", "Node3D") var owner_path: NodePath = NodePath()
## The path to the related [Inventory]. This is not necessary, unless you want to have 
## an inventory based gameplay system.
## [br]For example: a classic Doom/Quake-like game, will not have an inventory system, 
## all weapons are set at startup and can be used only if some tags are set.
@export_node_path("Inventory") var inventory_path: NodePath = NodePath()
## Slots available in current [Equipment].
@export var slots: Array[EquipmentSlot] = []
## An array of tags which describe the state of the equipment.
@export var tags: Array[String] = []


## All equipped [Item]s.
var equipped_items: Array[Item]:
	get:
		var items: Array[Item]

		for slot in slots:
			if slot.has_equippend_item:
				items.append(slot.current)

		return items


## Returns the related [Inventory] searched by [member Equipment.inventory_path]. 
var inventory: Inventory:
	get:
		return get_node(inventory_path)


## Binds slots signals
func _ready() -> void:
	for slot in slots:
		slot.item_equipped.connect(func (item: Item):
			equipped.emit(item, slot)	
		)
		slot.item_unequipped.connect(func (item: Item):
			unequipped.emit(item, slot)	
		)


## Checks if an [Item] can be equipped or not based on 
## it's own [member Item.tags_required_to_equip] property.
## [br]If the [Item] has no tags set, it always return [code]true[/code], 
## otherwise it check that all the tags specified are included 
## in the current [member Equipment.tags] member.
func can_equip(item: Item) -> bool:
	if item.tags_required_to_equip.size() == 0:
		return true
		
	for tag in item.tags_required_to_equip:
		if not tags.has(tag):
			return false
	
	return true
	

## Checks if an [Item] can be unequipped or not based on 
## it's own [member Item.tags_required_to_unequip] property.
## [br]If the [Item] has no tags set, it always return [code]true[/code], 
## otherwise it check that all the tags specified are included 
## in the current [member Equipment.tags] member.
func can_unequip(item: Item) -> bool:
	if item.tags_required_to_unequip.size() == 0:
		return true
		
	for tag in item.tags_required_to_unequip:
		if not tags.has(tag):
			return false
	
	return true


## Finds the first suitable [EquipmentSlot] and equips the [Item].
## [br]Passing [code]skip_tags_check[/code] to [code]true[/code], 
## the check against [member Item.tags_required_to_equip] will be skipped.
func equip(item: Item, skip_tags_check: bool = false) -> void:
	for slot in slots:
		if not skip_tags_check and slot.can_accept(item):
			slot.equip(item)
			return
		elif slot.can_accept(item):
			if can_equip(item):
				slot.equip(item)
			else:
				refused_to_equip.emit(item, slot)
			return


## Equips the passed [Item] whose slot satisfies a [Callable] predicate.
## [br]
## [br]Note: the [EquipmentSlot] will check in any case if [method Equipment.can_accept] returns [code]true[/code] before calling the predicate.
## [br]
## [br]
## [code]
## equipment.equip_by(my_item, func (slot: EquipmentSlot) -> bool: return slot.is_free)
## [/code]
## [br]Passing [code]skip_tags_check[/code] to [code]true[/code], 
## the check against [member Item.tags_required_to_equip] will be skipped.
func equip_by(item: Item, predicate: Callable, skip_tags_check: bool = false) -> void:
	for slot in slots:
		if not slot.can_accept(item):
			continue
		if not skip_tags_check and predicate.call(slot):
			slot.equip(item)
			return
		elif can_equip(item) and predicate.call(slot):
			slot.equip(item)
			return
		


## Finds the first [Item] which satisfies the [Callable] predicate.
## [br]Returns [code]null[/code] if none is found.
func find_item_by(predicate: Callable) -> Item:
	for item in equipped_items:
		if predicate.call(item):
			return item
	
	return null


## Finds the first [EquipmentSlot] which satisfies the [Callable] predicate.
## [br]Returns [code]null[/code] if none is found.
func find_slot_by(predicate: Callable) -> EquipmentSlot:
	for slot in slots:
		if predicate.call(slot):
			return slot
	return null


## Finds the first slot whose equipped [member Item.name] equals to the passed [member Item.name] and unequips it.
## [br]Passing [code]skip_tags_check[/code] to [code]true[/code], 
## the check against [member Item.tags_required_to_equip] will be skipped.
func unequip(item: Item, skip_tags_check: bool = false) -> void:
	for slot in slots:
		if slot.has_equippend_item and slot.current.name == item.name and not skip_tags_check:
			slot.unequip()
			return
		elif slot.has_equippend_item and slot.current.name == item.name and can_unequip(item):
			slot.unequip()
			return


## Unequips the first [EquipmentSlot] which satisfies the [Callable] predicate.
## [br]Passing [code]skip_tags_check[/code] to [code]true[/code], 
## the check against [member Item.tags_required_to_equip] will be skipped.
func unequip_by(predicate: Callable, skip_tags_check: bool = false) -> void:
	for slot in slots:
		if slot.has_equippend_item and predicate.call(slot) and not skip_tags_check:
			slot.unequip()
			return
		elif slot.has_equippend_item and predicate.call(slot) and can_unequip(slot.current):
			slot.unequip()
			return


## Unequips all slots. ## [br]Passing [code]skip_tags_check[/code] to [code]true[/code], 
## the check against [member Item.tags_required_to_equip] will be skipped.
func unequip_all(skip_tags_check: bool = false) -> void:
	for slot in slots:
		if slot.has_equippend_item and not skip_tags_check:
			slot.unequip()
		elif slot.has_equippend_item and can_unequip(slot.current):
			slot.unequip()
