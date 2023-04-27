class_name ItemActivationEvent extends RefCounted

## The activation type
var activation_type: int = 0
## [code]true[/code] if owner is not [code]null[/code], [code]false[/code] otherwise.
var has_owner: bool:
	get:
		return owner != null
## The inventory owner
var owner: Node
## The equipment which emits the activation event or is bound to an [Inventory]. It could be [code]null[/code].
var equipment: Equipment
## The inventory which emits the activation event or is bound to an [Equipment]. It could be [code]null[/code].
var inventory: Inventory


## Builds the event
func _init(_inventory_or_equipment: Variant, _activation_type: int = 0) -> void:
	var someone_really_called_me = false
	
	assert(_activation_type != null, "activation_type cannot be null")

	activation_type = _activation_type
	
	if _inventory_or_equipment is Inventory:
		inventory = _inventory_or_equipment
		equipment = inventory.equipment
		someone_really_called_me = true
		
		if not inventory.owner_path.is_empty():
			owner = inventory.get_node(inventory.owner_path)
		
	if _inventory_or_equipment is Equipment:
		equipment = _inventory_or_equipment
		inventory = equipment.inventory
		someone_really_called_me = true
		
		if not equipment.owner_path.is_empty():
			owner = equipment.get_node(equipment.owner_path)
			
	assert(someone_really_called_me, "an ItemActivationEvent can be called by an Equipment or Inventory node")
