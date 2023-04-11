@icon("res://addons/godot_gameplay_systems/inventory_system/assets/ItemIcon.png")
@tool
class_name Item extends Resource


## Represents an item in the world


@export_category("Item")
## Name given to this item.
## [br]Use it just for your internal purpose, you should use a dictionary of name->i18n values for multilanguage purpose.
@export var name: StringName = ""
## Determines if an [Item] can stack or not. 
@export var can_stack: bool = false
## If [member Item.can_stack] is [code]true[/code], it will decrease automatically it's own stack on activation.
@export var decrease_stack_on_use: bool = false
## The rendered (2D or 3D) item into the game world, or in front of the camera.
@export var scene: PackedScene =  null
## Tags used to categorize this [Item].
@export var tags: Array[String] = []

@export_group("Stacking", "quantity_")
## Current quantity.
@export var quantity_current: int = 1
## If [member Item.can_stack] is set to [code]true[/code].
## [br]Set it to [code]0[/code] for infinite stacking (e.g. currency and similar).
@export var quantity_max: int = 1

@export_group("Tags", "tags_")
## Tags added to [Inventory] and [Equipment] on [Item] activation.
@export var tags_added_on_activation: Array[String] = []
## Tags added to [Inventory] on [Item] add.
## [br]Note, if some [Item]s are added to an [Inventory] through the editor, these tags will be added inside
## the [method Inventory._ready] method.
@export var tags_added_on_add: Array[String] = []
## Tags added to [Equipment] when the [Item] is equipped.
@export var tags_added_on_equip: Array[String] = []
## Tags added to [Inventory] and [Equipment] on [Item] remove.
@export var tags_added_on_remove: Array[String] = []
## Tags added to [Equipment] owner when the [Item] is unequipped.
@export var tags_added_on_unequip: Array[String] = []
## Requires an [Inventory] or [Equipment] to have all these tags before activating this [Item].
@export var tags_required_to_activate: Array[String] = []
## Requires an [Inventory] to have all these tags before adding this [Item].
@export var tags_required_to_add: Array[String] = []
## Requires an [Equipment] to have all these tags before equipping this [Item].
@export var tags_required_to_equip: Array[String] = []
## Requires an [Inventory] to have all these tags before removing this [Item].
@export var tags_required_to_remove: Array[String] = []
## Requires an [Equipment] to have all these tags before unequipping this [Item].
@export var tags_required_to_unequip: Array[String] = []
## Tags removed from [Inventory] and [Equipment] on [Item] activation.
@export var tags_removed_on_activation: Array[String] = []
## Tags removed from [Inventory] on [Item] add.
@export var tags_removed_on_add: Array[String] = []
## Tags removed from the [Equipment] when the [Item] is equipped.
@export var tags_removed_on_equip: Array[String] = []
## Tags removed from [Inventory] and [Equipment] on [Item] remove.
@export var tags_removed_on_remove: Array[String] = []
## Tags removed from the [Equipment] when the [Item] is unequipped.
@export var tags_removed_on_unequip: Array[String] = []


## A virtual method called when the item is activated. Override it to determine how the item behaves on activation.
func _activate(_activation_event: ItemActivationEvent) -> void:
	pass


## Returns if the item has the right tags to be activated. Override it to determine if the item can be added to an [Inventory].
func _can_activate(_activation_event: ItemActivationEvent) -> bool:
	return true


## A virtual method called when this item is equipped.
func _equip(_equipment: Equipment, _equipment_slot: EquipmentSlot) -> void:
	pass


## A virtual method called when this item is unequipped.
func _unequip(_equipment: Equipment, _equipment_slot: EquipmentSlot) -> void:
	pass

