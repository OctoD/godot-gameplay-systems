@icon("res://addons/godot-gameplay-attributes/assets/effect_icon.png")

class_name AttributeEffect extends Resource

enum {
	LIFETIME_ONE_SHOT = 0,
	LIFETIME_TIME_BASED = 1,
}

@export_category("Effect life-time")
@export_enum("One-Shot", "Time-Based") var life_time = 0:
	get:
		return life_time
	set(value):
		life_time = value
		emit_changed()
@export var apply_every_second := 1.0:
	get:
		return apply_every_second
	set(value):
		apply_every_second = value
		emit_changed()
@export var max_applications := 1:
	get:
		return max_applications
	set(value):
		max_applications = value
		emit_changed()

@export_category("Attribute modifier")
@export var attribute_name := "":
	get:
		return attribute_name
	set(value):
		attribute_name = value
		emit_changed()
@export var minimum_value := 0.0:
	get:
		return minimum_value
	set(value):
		minimum_value = value
		emit_changed()
@export var maximum_value := 0.0:
	get:
		return maximum_value
	set(value):
		maximum_value = value
		emit_changed()


func get_current_value() -> Variant:
	if minimum_value < maximum_value:
		return randf_range(minimum_value, maximum_value)
	elif minimum_value > maximum_value:
		return randf_range(minimum_value, maximum_value)
	else:
		return minimum_value
