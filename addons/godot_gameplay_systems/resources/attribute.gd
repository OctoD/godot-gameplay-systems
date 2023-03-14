class_name AttributeResource extends Resource

@export_category("Attribute")
## Is the attribute name
@export var attribute_name := ""
## Is the attribute minimum value
@export var minimum_value := 0.0
## Is the attribute maximum value
@export var maximum_value := 0.0
## Is the attribute initial value
@export var current_value := 0.0


func _init(p_attribute_name: String = "", p_minimum_value: float = 0.0, p_maximum_value: float = 0.0, p_current_value: float = 0.0) -> void:
	attribute_name = p_attribute_name
	minimum_value = p_minimum_value
	maximum_value = p_maximum_value
	current_value = p_current_value
