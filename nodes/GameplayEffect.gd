tool
extends Node
class_name GameplayEffect


func _ready():
	setup_effect()


func setup_effect() -> void:
	connect_to_parent_signal()


func apply_effect(attribute: GameplayAttribute) -> void:
	pass


func connect_to_parent_signal() -> void:
	var parent = get_parent()

	if parent.has_signal("attribute_changed"):
		parent.connect("attribute_changed", self, "on_attribute_changed")


func on_attribute_changed(attribute: GameplayAttribute) -> void:
	if should_activate():
		apply_effect(attribute);

		if should_deactivate():
			queue_free()


func should_activate() -> bool:
	return true


func should_deactivate() -> bool:
	return true


func _get_configuration_warning():
	if get_parent().has_signal("attribute_changed"):
		return ""

	return "GameplayAttribute must be a direct child of a GameplayAttributeMap node."

