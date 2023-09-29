@tool
extends EditorPlugin

const attributes_and_abilities_plugin_script = preload("./attributes_and_abilities/plugin.gd")
const camera_shake_plugin_script = preload("./camera_shake/plugin.gd")
const extended_character_nodes_script = preload("./extended_character_nodes/plugin.gd")
const inventory_system_script = preload("./inventory_system/plugin.gd")
const interactables_script = preload("./interactables/plugin.gd")
const slideshow_script = preload("./slideshow/plugin.gd")
const turn_based_script = preload("./turn_based/plugin.gd")


var attributes_and_abilities_plugin: EditorPlugin
var camera_shake_plugin: EditorPlugin
var extended_character_nodes: EditorPlugin
var inventory_system: EditorPlugin
var interactables: EditorPlugin
var slideshow: EditorPlugin
var turn_based: EditorPlugin


func _init() -> void:
	attributes_and_abilities_plugin = attributes_and_abilities_plugin_script.new()
	camera_shake_plugin = camera_shake_plugin_script.new()
	extended_character_nodes = extended_character_nodes_script.new()
	inventory_system = inventory_system_script.new()
	interactables = interactables_script.new()
	slideshow = slideshow_script.new()
	turn_based = turn_based_script.new()


func _enter_tree():
	attributes_and_abilities_plugin._enter_tree()
	camera_shake_plugin._enter_tree()
	extended_character_nodes._enter_tree()
	inventory_system._enter_tree()
	interactables._enter_tree()
	slideshow._enter_tree()
	turn_based._enter_tree()


func _exit_tree():
	attributes_and_abilities_plugin._exit_tree()
	camera_shake_plugin._exit_tree()
	extended_character_nodes._exit_tree()
	inventory_system._exit_tree()
	interactables._exit_tree()
	slideshow._exit_tree()
	turn_based._exit_tree()
