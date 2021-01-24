tool
extends Node
class_name GameplayEffect


export(bool) var one_shot = true


var _is_active = false


func _ready():
	connect_to_parent_signal()


func apply_effect(attribute_name: String, attribute_type: String, attribute_value: float) -> void:
	pass


func connect_to_parent_signal() -> void:
	var parent = get_parent()

	if parent.has_signal("attribute_changed"):
		parent.connect("attribute_changed", self, "on_parent_attribute_changed")


func on_parent_attribute_changed(attribute_name: String, attribute_type: String, attribute_value: float) -> void:
	if should_activate():
		apply_effect(attribute_name, attribute_type, attribute_value);

		if one_shot:
			queue_free()
		elif should_deactivate():
			queue_free()


func should_activate() -> bool:
	_is_active = true
	return _is_active


func should_deactivate() -> bool:
	_is_active = false
	return true


func _get_configuration_warning():
	if get_parent().has_signal("attribute_changed"):
		return ""

	return "GameplayAttribute must be a direct child of a GameplayAttributeMap node."

