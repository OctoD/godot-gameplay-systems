tool
extends Node
class_name GameplayAttribute


export(float) var max_value = 0.0 setget set_max_value, get_max_value
export(float) var current_value = 0.0  setget set_current_value, get_current_value


signal max_value_changed
signal current_value_changed


func get_current_value() -> float:
	return current_value


func get_max_value() -> float:
	return max_value


func set_current_value(value: float) -> void:
	if is_inside_tree():
		current_value = clamp(value, 0, max_value)
		emit_signal("current_value_changed", name, current_value)
		

func set_max_value(value: float) -> void:
	if is_inside_tree() and value >= 0:
		max_value = value
		emit_signal("max_value_changed", name, value)


func _get_configuration_warning():
	if get_parent().has_signal("attribute_changed"):
		return ""

	return "GameplayAttribute must be a direct child of a GameplayAttributeMap node."
