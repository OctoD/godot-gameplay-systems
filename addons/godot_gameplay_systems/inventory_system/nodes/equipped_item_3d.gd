@tool
class_name EquippedItem3D extends Node3D


## Displays the current equipped [Item] from a specific [Equipment] node.


## Emitted when an [Item] is displayed.
signal item_displayed(item: Item)
## Emitted when an [Item] is hidden.
signal item_hidden(item: Item)


@export_category("Equipment")
## The path to the [Equipment] node
@export_node_path("Equipment") var equipment_path: NodePath = NodePath():
	get:
		return equipment_path
	set(value):
		equipment_path = value
		update_configuration_warnings()

@export_group("Tagging", "tags_")
## Displays an equipped [Item] only if both it has these the [member Item.tags] tags.
@export var tags_to_display: Array[String] = []


var current: Node3D = null


func _init() -> void:
	if Engine.is_editor_hint():
		update_configuration_warnings()


func _ready() -> void:
	assert(not equipment_path.is_empty(), "equipment_path cannot be empty")

	var equipment = get_node(equipment_path)
	
	equipment.equipped.connect(func (item: Item, _slot: EquipmentSlot):
		if tags_to_display.size() > 0:
			var has_tags = true
			for tag in tags_to_display:
				if not item.tags.has(tag):
					has_tags = false
					break
			if not has_tags:
				return

		if item.scene and item.scene.can_instantiate():
			current = item.scene.instantiate()
			add_child(current)
	)
	
	equipment.unequipped.connect(func (_item: Item, _slot: EquipmentSlot):
		if current:
			remove_child(current)
			current = null
	)


func _get_configuration_warnings() -> PackedStringArray:
	var errors: Array[String] = []
	
	if equipment_path == null:
		errors.append("equipment_path cannot be null")

	if equipment_path != null and equipment_path.is_empty():
		errors.append("equipment_path cannot be empty")

	return PackedStringArray(errors)
