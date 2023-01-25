@icon("res://addons/godot-gameplay-attributes/assets/effect_icon.png")

class_name AttributeEffect extends Resource

@export_category("Effect life-time")
@export_enum("One-Shot", "Time-Based") var life_time = 0
@export var apply_every_second := 1.0
@export var max_applications := 1

@export_category("Attribute modifier")
@export var attribute_name := ""
@export var minimum_value := 0.0
@export var maximum_value := 0.0
