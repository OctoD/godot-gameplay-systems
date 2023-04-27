Item
====

It's a `Resource` which represents and `Item` in a 2D or 3D world.

> Important: always specify the `Item.name`. It's used for querying and identifying your `Item` properly, since there's not an internal reflection system like in C#

It can be described with tags. Each tag can be added, removed or required at a specific circumstance (like tags required for activation, tags required for remove and more).

An `Item` has also four virtual methods which can be overridden to create your gameplay mechanisms.

An instance of `ItemActivationEvent` is passed when trying to activate the item, while 
the `Equipment` and `EquipmentSlot` instances are passed when equipping/unequipping.

```gdscript
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
```