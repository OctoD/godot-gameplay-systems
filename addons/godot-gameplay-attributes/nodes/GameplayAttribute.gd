tool
extends Node
class_name GameplayAttribute


signal attribute_changed(attribute)


@export var max_value := 0.0:
	get:
		return max_value
	set(value):
		if value >= 0:
			var prev_value = current_value
			var prev_max = max_value
			
			max_value = value

			attribute_changed.emit({
				"prev_max": prev_max,
				"prev_value": prev_value,
				"current_max": max_value,
				"current_value": current_value,
				"name": self.name
			})

@export var current_value := 0.0:
	get:
		return current_value
	set(value):
		var prev_max = max_value
		var prev_value = current_value
		
		current_value = clamp(value, 0, max_value)

		attribute_changed.emit({
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
