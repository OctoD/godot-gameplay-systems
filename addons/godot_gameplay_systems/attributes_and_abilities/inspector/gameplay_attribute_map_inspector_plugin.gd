@tool
extends EditorInspectorPlugin


var attribute_editor = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/inspector/attribute_editor.gd")
var attribute_effect_editor = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/inspector/attribute_effect_editor.gd")


func _can_handle(object) -> bool:
	return object is GameplayAttributeMap


func _parse_property(object: Object, type, name: String, hint_type, hint_string: String, usage_flags, wide: bool) -> bool:
	if type == 28 and name == "attributes":
		add_property_editor(name, attribute_editor.new(), true)
		return true
	if type == 28 and name == "attributes_affected":
		add_property_editor(name, attribute_effect_editor.new(), true)
		return true
	if type == 24 and name == "table":
		return true
	return false
