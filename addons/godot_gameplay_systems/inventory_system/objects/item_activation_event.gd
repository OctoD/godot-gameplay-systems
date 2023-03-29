class_name ItemActivationEvent extends RefCounted

## The activation type
var activation_type: int = 0
## [code]true[/code] if owner is not [code]null[/code], [code]false[/code] otherwise.
var has_owner: bool:
	get:
		return owner != null
## The inventory owner
var owner: Node
## The inventory which emits the activation event
var inventory: Inventory


## Builds the event
func _init(_inventory: Inventory, _activation_type: int = 0) -> void:
	assert(_inventory != null, "Inventory cannot be null")
	assert(_activation_type != null, "activation_type cannot be null")

	activation_type = _activation_type
	inventory = _inventory

	if _inventory and not inventory.owner_path.is_empty():
		owner = inventory.get_node(inventory.owner_path)
