tool
extends Node
class_name GameplayAttributeMap


signal attribute_changed

var _is_valid = false


func _ready():
	if _is_valid or not Engine.editor_hint:
		connect_child_signals()


func apply_effect(effect: GameplayEffect) -> void:
	add_child(effect)


func connect_child_signals() -> void:
	if not Engine.editor_hint:
		for child in get_children():
			if child.has_signal("attribute_changed"):
				child.connect("attribute_changed", self, "on_attribute_changed")


func get_attribute(attribute_name: String) -> GameplayAttribute:
	var found: GameplayAttribute = find_node(attribute_name)
	return found


func on_attribute_changed(attribute: GameplayAttribute, attribute_value_changed: String) -> void:
	emit_signal("attribute_changed", attribute, attribute_value_changed, self)



func _get_gameplay_effects() -> Array:
	var effects = []
	
	for child in get_children():
		if child is GameplayEffect:
			effects.append(child)
		
	return effects


func _get_configuration_warning():
	var children = get_children()
	var message = "Requires at least on GameplayAttribute node"
	var parent = get_parent()
	var is_editing = Engine.editor_hint
	
	if parent != null and not (parent is KinematicBody or parent is KinematicBody2D) and is_editing:
		_is_valid = false
		return "GameplayAttributeMap must be direct child of a KinematicBody or KinematicBody2D"
	
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
