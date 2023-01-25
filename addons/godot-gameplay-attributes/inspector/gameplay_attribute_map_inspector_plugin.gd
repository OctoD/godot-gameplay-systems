@tool
extends EditorInspectorPlugin


var attribute_editor = preload("res://addons/godot-gameplay-attributes/inspector/attribute_editor.gd")
var attribute_effect_editor = preload("res://addons/godot-gameplay-attributes/inspector/attribute_effect_editor.gd")


func _can_handle(object) -> bool:
	if object is GameplayAttributeMap:
		return true
	if object is GameplayEffect:
		return true
	
	return false


func _parse_property(object: Object, type: int, name: String, hint_type: int, hint_string: String, usage_flags: int, wide: bool) -> bool:
	if type == 28 and name == "attributes":
		add_property_editor(name, attribute_editor.new(), true)
		return true
	if type == 28 and name == "attributes_affected":
		add_property_editor(name, attribute_effect_editor.new(), true)
		return true
	if type == 24 and name == "table":
		return true
	return false
