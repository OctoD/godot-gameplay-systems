@icon("res://addons/godot-gameplay-attributes/assets/attribute_map_icon.png")

class_name AttributeTable extends Resource

## Represents a table of attributes

@export_category("Attributes")
## The list of attributes
@export var attributes : Array[String] = []


func _init(p_attributes: Array[String] = []) -> void:
	attributes = p_attributes
