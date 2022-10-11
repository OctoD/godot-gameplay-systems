@tool
extends EditorPlugin


@onready var gameplay_attribute = preload("nodes/gameplay_attribute.gd")
@onready var gameplay_attribute_map = preload("nodes/gameplay_attribute_map.gd")
@onready var gameplay_attribute_resource = preload("nodes/gameplay_attribute_resource.gd")
@onready var gameplay_effect = preload("nodes/gameplay_effect.gd")
@onready var timed_gameplay_effect = preload("nodes/timed_gameplay_effect.gd")

@onready var attribute_icon = preload("assets/attribute_icon.png")
@onready var attribute_map_icon = preload("assets/attribute_map_icon.png")
@onready var timed_icon = preload("assets/timed_icon.png")

func _enter_tree():
	add_custom_type("GameplayAttribute", "Node", gameplay_attribute, attribute_icon)
	add_custom_type("GameplayAttributeMap", "Node", gameplay_attribute_map, attribute_map_icon)
	add_custom_type("GameplayEffect", "Node", gameplay_effect, null)
	add_custom_type("TimedGameplayEffect", "GameplayEffect", timed_gameplay_effect, timed_icon)


func _exit_tree():
	remove_custom_type("GameplayAttribute")
	remove_custom_type("GameplayAttributeMap")
	remove_custom_type("GameplayEffect")
	remove_custom_type("TimedGameplayEffect")
