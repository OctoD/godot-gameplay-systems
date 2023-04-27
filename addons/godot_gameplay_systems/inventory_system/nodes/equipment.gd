@icon("res://addons/godot_gameplay_systems/inventory_system/assets/EquipmentIcon.png")
@tool
class_name Equipment extends Node


## Handles your equipped items.
##
## It uses slots to determine which item can be equippend and how.
##
## Note: an equipment should be unique for a character.


enum LifeCycle {
	## One item has been activated from the inventory.
	Activate = 0,
	## One item has been equipped.
	Equip = 2,
	## One item has been removed from the inventory.
	Remove = 3,
	## One item has been unequipped.
	Unequip = 4,
}


## Emitted when an [Item] is activated.
signal item_activated(item: Item, activation_type: int)
## Emitted when an [Item] is equipped on a determined [EquipmentSlot].
signal equipped(item: Item, slot: EquipmentSlot)
## Emitted when the [Equipment] refuses to equip an [Item] because of it's own tags requirements or no [EquipmentSlot] can be found. 
## [br]In the last case, slot will be passed as [code]null[/code]
signal refused_to_equip(item: Item, slot: EquipmentSlot)
## Emitted when an [Item] is unequipped on a determined [EquipmentSlot].
signal unequipped(item: Item, slot: EquipmentSlot)
## Emitted when the [Equipment] refuses to unequip an [Item] because of it's own tags requirements.
signal refused_to_unequip(item: Item, slot: EquipmentSlot)
## Emitted when any add tag method is called.
signal tag_added(tag: String, tags: Array[String])
## Emitted when any remove tag method is called.
signal tag_removed(tag: String, tags: Array[String])


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

@export_group("Gameplay", "gameplay_")
@export var gameplay_equip_automatically: bool = false


## All equipped [Item]s.
var equipped_items: Array[Item]:
	get:
		var items: Array[Item]

		for slot in slots:
			if slot.has_equipped_item:
				items.append(slot.equipped)

		return items


## The related [Inventory] searched by [member Equipment.inventory_path]. 
var inventory: Inventory


## Used internally to handle a [signal Inventory.item_activated] signal.
func _handle_item_activated(item: Item, activation_type: int) -> void:
	_handle_life_cycle(LifeCycle.Activate, item)
	item_activated.emit(item, activation_type)
		

## Used internally to handle a [signal Inventory.item_added] signal.
func _handle_item_added(item: Item) -> void:
	if gameplay_equip_automatically:
		var slot = find_slot_by_item(item)

		if slot != null and not slot.has_equipped_item:
			equip(item)


## Used internally to handle a [signal EquipmentSlot.item_added] signal.
func _handle_item_equipped(item: Item, slot: EquipmentSlot):
	equipped.emit(item, slot)
	item._equip(self, slot)
	_handle_life_cycle(LifeCycle.Equip, item)
		


## Used internally to handle a [signal Inventory.item_removed] signal.
func _handle_item_removed(item: Item) -> void:
	unequip(item)
	_handle_life_cycle(LifeCycle.Remove, item)


## Handles tags internally. Do not call it manually.
func _handle_life_cycle(life_cycle: LifeCycle, item: Item) -> void:
	match life_cycle:
		LifeCycle.Activate:
			add_tags(item.tags_added_on_activation)
			remove_tags(item.tags_removed_on_activation)
			return
		LifeCycle.Equip:
			add_tags(item.tags_added_on_equip)
			remove_tags(item.tags_removed_on_equip)
			return
		LifeCycle.Remove:
			add_tags(item.tags_added_on_remove)
			remove_tags(item.tags_removed_on_remove)
		LifeCycle.Unequip:
			add_tags(item.tags_added_on_unequip)
			remove_tags(item.tags_removed_on_unequip)
			return


## Used internally to handle a [signal EquipmentSlot.refused_to_equip] signal.
func _handle_item_refused_to_equip(item: Item, slot: EquipmentSlot):
	refused_to_equip.emit(item, slot)	


## Used internally to handle a [signal EquipmentSlot.item_unequipped] signal.
func _handle_item_unequipped(item: Item, slot: EquipmentSlot):
	unequipped.emit(item, slot)	
	item._unequip(self, slot)
	_handle_life_cycle(LifeCycle.Unequip, item)


## Binds slots signals
func _ready() -> void:
	setup()


## Activates an [Item]. 
## [br]If an [Inventory] is bound to this equipment, the [method Inventory.activate] will be called.
## [br]Otherwise, the [method Item.activate] method will be called directly.
func activate(item: Item, activation_type: int = 0) -> void:
	if inventory:
		inventory.activate(item, activation_type)
	else:
		if can_activate(item, activation_type):
			item._activate(ItemActivationEvent.new(self, activation_type))
			item_activated.emit(item, activation_type)
			_handle_life_cycle(LifeCycle.Activate, item)


## Adds one tag.
func add_tag(tag: String) -> void:
	if not tags.has(tag):
		tags.append(tag)
		tag_added.emit(tag, tags)


## Adds many tags.
func add_tags(_tags: Array[String]) -> void:
	for t in _tags:
		add_tag(t)


## Checks if an [Item] can be directly activated by this [Equipment].
func can_activate(item: Item, activation_type: int) -> bool:
	if item.tags_required_to_activate.size() > 0:
		for t in item.tags_required_to_activate:
			if not tags.has(t):
				return false
		
	return is_equipped(item) and item._can_activate(ItemActivationEvent.new(self, activation_type))


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
	var slot = find_slot_by_item(item)

	if not slot:
		refused_to_equip.emit(item, slot)
		return

	if skip_tags_check:
		if slot.has_equipped_item:
			slot.unequip()
		slot.equip(item)
		return
	else:
		if can_equip(item):
			if slot.has_equipped_item:
				slot.unequip()
			slot.equip(item)
			return
	
	refused_to_equip.emit(item, slot)


## Equips the passed [Item] whose slot satisfies a [Callable] predicate.
## [br]
## [br]Useful to equip on slots which accept the same [Item] like charms or rings in diablo-like equipments.
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
	var slot = find_slot_by_item(item)
	
	if slot == null:
		refused_to_equip.emit(item, slot)
		return
	
	var predicate_result = predicate.call(slot);
	
	if skip_tags_check and predicate_result:
		slot.equip(item)
		return
	
	if can_equip(item) and predicate_result:
		slot.equip(item)
		return
			
	refused_to_equip.emit(item, slot)
		


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


## Finds the first [EquipmentSlot] that can equip the passed [Item].
func find_slot_by_item(item: Item) -> EquipmentSlot:
	return find_slot_by(func (x: EquipmentSlot): return x.can_equip(item))


## Checks if a tag is contained in this [Equipment].
func has_tag(tag: String) -> bool:
	return tags.has(tag)



## Checks if all these tags are contained in this [Equipment].
func has_tags(_tags: Array[String]) -> bool:
	for t in _tags:
		if not tags.has(t):
			return false
	
	return true


## Checks if the [Item] is equipped.
func is_equipped(item: Item) -> bool:
	var slot = find_slot_by_item(item)
	
	if slot == null:
		return false
	
	return slot.has_equipped_item and slot.equipped.name == item.name


## Removes one tag.
func remove_tag(tag: String) -> void:
	var index = tags.find(tag)
	
	if index >= 0:
		tags.remove_at(index)
		tag_removed.emit(tags)


## Removes many tags.
func remove_tags(_tags: Array[String]) -> void:
	for t in _tags:
		remove_tag(t)


## Programmatically setups an [Equipment]
func setup() -> void:
	if not inventory_path.is_empty():
		inventory = get_node(inventory_path) as Inventory

	if not Engine.is_editor_hint() and not owner_path.is_empty():
		var _owner = get_node(owner_path)
		_owner.set_meta("ggsEquipment", self)

	if inventory != null:
		if not inventory.item_added.is_connected(_handle_item_activated):
			inventory.item_activated.connect(_handle_item_activated)

		if not inventory.item_added.is_connected(_handle_item_added):
			inventory.item_added.connect(_handle_item_added)
			
		if not inventory.item_removed.is_connected(_handle_item_removed):
			inventory.item_removed.connect(_handle_item_removed)
	
	for slot in slots:
		if not slot.item_equipped.is_connected(_handle_item_equipped):
			slot.item_equipped.connect(_handle_item_equipped)
		
		if not slot.item_refused_to_equip.is_connected(_handle_item_refused_to_equip):
			slot.item_refused_to_equip.connect(_handle_item_refused_to_equip)

		if not slot.item_unequipped.is_connected(_handle_item_unequipped):
			slot.item_unequipped.connect(_handle_item_unequipped)
			


## Finds the first slot whose equipped [member Item.name] equals to the passed [member Item.name] and unequips it.
## [br]Passing [code]skip_tags_check[/code] to [code]true[/code], 
## the check against [member Item.tags_required_to_equip] will be skipped.
func unequip(item: Item, skip_tags_check: bool = false) -> void:
	var slot = find_slot_by_item(item)
	
	if slot == null:
		return
	elif slot.has_equipped_item and slot.equipped.name == item.name and skip_tags_check:
		slot.unequip()
		return
	elif slot.has_equipped_item and slot.equipped.name == item.name and can_unequip(item):
		slot.unequip()
		return


## Unequips the first [EquipmentSlot] which satisfies the [Callable] predicate.
## [br]Passing [code]skip_tags_check[/code] to [code]true[/code], 
## the check against [member Item.tags_required_to_equip] will be skipped.
func unequip_by(predicate: Callable, skip_tags_check: bool = false) -> void:
	for slot in slots:
		if slot.has_equipped_item and predicate.call(slot) and skip_tags_check:
			slot.unequip()
			return
		elif slot.has_equipped_item and predicate.call(slot) and can_unequip(slot.equipped):
			slot.unequip()
			return


## Unequips all slots. ## [br]Passing [code]skip_tags_check[/code] to [code]true[/code], 
## the check against [member Item.tags_required_to_equip] will be skipped.
func unequip_all(skip_tags_check: bool = false) -> void:
	for slot in slots:
		if slot.has_equipped_item and skip_tags_check:
			slot.unequip()
		elif slot.has_equipped_item and can_unequip(slot.equipped):
			slot.unequip()

