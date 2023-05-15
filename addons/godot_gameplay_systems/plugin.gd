@tool
extends EditorPlugin

const attributes_and_abilities_plugin_script = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/plugin.gd")
const inventory_system_script = preload("res://addons/godot_gameplay_systems/inventory_system/plugin.gd")
const interactables_script = preload("res://addons/godot_gameplay_systems/interactables/plugin.gd")


var attributes_and_abilities_plugin: EditorPlugin
var inventory_system: EditorPlugin
var interactables: EditorPlugin


func _init() -> void:
	attributes_and_abilities_plugin = attributes_and_abilities_plugin_script.new()
	inventory_system = inventory_system_script.new()
	interactables = interactables_script.new()


func _enter_tree():
	attributes_and_abilities_plugin._enter_tree()
	inventory_system._enter_tree()
	interactables._enter_tree()


func _exit_tree():
	attributes_and_abilities_plugin._exit_tree()
	inventory_system._exit_tree()
	interactables._exit_tree()
