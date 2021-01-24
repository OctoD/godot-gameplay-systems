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
			if child.has_signal("attribute_changed"):
				child.connect("attribute_changed", self, "on_attribute_changed")


func on_attribute_changed(attribute: GameplayAttribute, attribute_value_changed: String) -> void:
	emit_signal("attribute_changed", attribute, attribute_value_changed)


func _get_configuration_warning():
	var children = get_children()
	var message = "Requires at least on GameplayAttribute node"
	
	if children.size() == 0:
		_is_valid = false
		return message
	
	var gameplay_attributes_count = 0
	
	for child in children:
		if child.has_signal("attribute_changed"):
			gameplay_attributes_count += 1

	if gameplay_attributes_count == 0:
		_is_valid = false
		return message
	
	_is_valid = true
	
	return ""
