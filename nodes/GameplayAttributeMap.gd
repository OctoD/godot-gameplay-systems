tool
extends Node
class_name GameplayAttributeMap

signal attribute_changed

var _is_valid = false

func _ready():
	if _is_valid:
		connect_child_signals()


func connect_child_signals() -> void:
	if not Engine.editor_hint:
		for child in get_children():
			if child.has_signal("current_value_changed") and child.has_signal("max_value_changed"):
				child.connect("current_value_changed", self, "on_attribute_current_value_changed")
				child.connect("max_value_changed", self, "on_attribute_max_value_changed")


func get_attribute_max_value(attribute_name: String) -> float:
	var found = find_node(attribute_name);
	
	if found && found.has("max_value"):
		return found.max_value
	else:
		return 0.0


func get_attribute_value(attribute_name: String) -> float:
	var found = find_node(attribute_name);

	if found && found.has("current_value"):
		return found.current_value
	else:
		return 0.0


func on_attribute_current_value_changed(attribute_name: String, attribute_value: float) -> void:
	emit_signal("attribute_changed", "current", attribute_name, attribute_value)


func on_attribute_max_value_changed(attribute_name: String, attribute_max_value: float) -> void:
	emit_signal("attribute_changed", "max", attribute_name, attribute_max_value)


func _get_configuration_warning():
	var children = get_children()
	var message = "Requires at least on GameplayAttribute node"
	
	if children.size() == 0:
		_is_valid = false
		return message
	
	var gameplay_attributes_count = 0
	
	for child in children:
		if child.has_signal("current_value_changed") and child.has_signal("max_value_changed"):
			gameplay_attributes_count += 1

	if gameplay_attributes_count == 0:
		_is_valid = false
		return message
	
	_is_valid = true
	
	return ""
