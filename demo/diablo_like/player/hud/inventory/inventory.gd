class_name DiabloLikeInventory extends Control


const inv_button = preload("res://examples/diablo_like/player/hud/inventory/inventory_item.tscn")


@export_category("Inventory")
@export var slots: int = 0


@onready var container: GridContainer = $VBoxContainer/Panel/VBoxContainer/GridContainer

var inventory: Inventory


func _draw_items() -> void:
	var index = 0
	var cells = container.get_children()
	var cellssize = cells.size()
	
	for item in inventory.items:
		if index < cellssize:
			cells[index].set_item(item)
		
		index += 1


func setup_inventory(_inventory: Inventory) -> void:
	inventory = _inventory

	inventory.item_added.connect(func (_item):
		_draw_items()	
	)
