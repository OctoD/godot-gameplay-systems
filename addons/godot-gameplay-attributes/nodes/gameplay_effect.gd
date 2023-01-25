@icon("res://addons/godot-gameplay-attributes/assets/effect_icon.png")
@tool
class_name GameplayEffect extends Node

@export_category("Effect")
@export var table: AttributeTable = null
@export var attributes_affected: Array[AttributeEffect] = []
