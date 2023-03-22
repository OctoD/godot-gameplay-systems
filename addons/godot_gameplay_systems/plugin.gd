@tool
extends EditorPlugin

const attributes_and_abilities_plugin_script = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/plugin.gd")


var attributes_and_abilities_plugin: EditorPlugin


func _init() -> void:
	attributes_and_abilities_plugin = attributes_and_abilities_plugin_script.new()


func _enter_tree():
	attributes_and_abilities_plugin._enter_tree()


func _exit_tree():
	attributes_and_abilities_plugin._exit_tree()
