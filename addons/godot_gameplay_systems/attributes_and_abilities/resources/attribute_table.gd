@icon("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/AttributeTable.svg")

class_name AttributeTable extends Resource

## Represents a table of attributes

@export_category("Attributes")
## The list of attributes
@export var attributes : Array[String] = []


func _init(p_attributes: Array[String] = []) -> void:
	attributes = p_attributes
