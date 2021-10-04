tool
extends Node
class_name GameplayAttribute


export(float) var max_value = 0.0 setget set_max_value, get_max_value
export(float) var current_value = 0.0  setget set_current_value, get_current_value


signal attribute_changed(attribute)


func get_current_value() -> float:
	return current_value


func get_max_value() -> float:
	return max_value


func set_current_value(value: float) -> void:
	var prev_max = max_value
	var prev_value = current_value
	current_value = clamp(value, 0, max_value)
	emit_signal("attribute_changed", {
		"prev_max": prev_max,
		"prev_value": prev_value,
		"current_max": max_value,
		"current_value": current_value,
		"name": self.name
	})


func set_max_value(value: float) -> void:
	if value >= 0:
		var prev_value = current_value
		var prev_max = max_value
		max_value = value
		emit_signal("attribute_changed", {
			"prev_max": prev_max,
			"prev_value": prev_value,
			"current_max": max_value,
			"current_value": current_value,
			"name": self.name
		})


func _get_configuration_warning():
	if get_parent().has_signal("attribute_changed"):
		return ""

	return "GameplayAttribute must be a direct child of a GameplayAttributeMap node."
