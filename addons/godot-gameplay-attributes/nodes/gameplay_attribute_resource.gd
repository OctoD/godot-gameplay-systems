class_name GameplayAttributeResource
extends Resource

@export_category("Attribute")
@export var attribute_name: String = ""
@export var minimum_value := 0.0
@export var maximum_value := 0.0
@export var default_value := 0.0


func to_attribute() -> GameplayAttribute:
	var attribute = GameplayAttribute.new()
	attribute.name = attribute_name
	attribute.max_value = maximum_value
	attribute.min_value = minimum_value
	attribute.current_value = default_value
	return attribute
