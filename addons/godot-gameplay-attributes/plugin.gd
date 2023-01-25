@tool
extends EditorPlugin


const ATTRIBUTE_RESOURCE_NAME = "AttributeResource"
const ATTRIBUTE_TABLE_RESOURCE_NAME = "AttributeTableResource"
const ATTRIBUTE_EFFECT_RESOURCE_NAME = "AttributeEffectResource"
const GAMEPLAY_EFFECT_NAME = "GameplayEffect"
const GAMEPLAY_ATTRIBUTE_MAP_NAME = "GameplayAttributeMap"

var attributes_table_resource = preload("res://addons/godot-gameplay-attributes/resources/attribute_table.gd")
var attribute_resource = preload("res://addons/godot-gameplay-attributes/resources/attribute.gd")
var attribute_effect_resource = preload("res://addons/godot-gameplay-attributes/resources/attribute_effect.gd")
var gameplay_effect = preload("res://addons/godot-gameplay-attributes/nodes/gameplay_effect.gd")
var gameplay_attribute_map = preload("res://addons/godot-gameplay-attributes/nodes/gameplay_attribute_map.gd")


var attribute_inspector_plugin_script = preload("res://addons/godot-gameplay-attributes/inspector/gameplay_attribute_map_inspector_plugin.gd")
var attribute_inspector_plugin: EditorInspectorPlugin


func _enter_tree():
	add_custom_type(ATTRIBUTE_RESOURCE_NAME, "Resource", attribute_resource, preload("res://addons/godot-gameplay-attributes/assets/attribute_icon.png"))
	add_custom_type(ATTRIBUTE_TABLE_RESOURCE_NAME, "Resource", attributes_table_resource, preload("res://addons/godot-gameplay-attributes/assets/attribute_map_icon.png"))
	add_custom_type(ATTRIBUTE_EFFECT_RESOURCE_NAME, "Resource", attribute_effect_resource, preload("res://addons/godot-gameplay-attributes/assets/effect_icon.png"))
	add_custom_type(GAMEPLAY_ATTRIBUTE_MAP_NAME, "Node", gameplay_attribute_map, preload("res://addons/godot-gameplay-attributes/assets/attribute_map_icon.png"))
	add_custom_type(GAMEPLAY_EFFECT_NAME, "Node", gameplay_effect, preload("res://addons/godot-gameplay-attributes/assets/effect_icon.png"))

	attribute_inspector_plugin = attribute_inspector_plugin_script.new()
	
	add_inspector_plugin(attribute_inspector_plugin)


func _exit_tree():
	remove_custom_type(ATTRIBUTE_RESOURCE_NAME)
	remove_custom_type(ATTRIBUTE_TABLE_RESOURCE_NAME)
	remove_custom_type(ATTRIBUTE_EFFECT_RESOURCE_NAME)
	remove_custom_type(GAMEPLAY_ATTRIBUTE_MAP_NAME)
	remove_custom_type(GAMEPLAY_EFFECT_NAME)
	
	remove_inspector_plugin(attribute_inspector_plugin)
