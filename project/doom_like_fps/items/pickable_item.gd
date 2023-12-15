@tool
extends "res://addons/godot_gameplay_systems/inventory_system/nodes/pickable_item_3d.gd"


func _init() -> void:
	automatically_pick = true


func _rotate(delta: float) -> void:
	rotate_y(1 * delta)

func _process(delta: float) -> void:
	if Engine.is_editor_hint():
		_rotate(delta)


func _physics_process(delta: float) -> void:
	if not Engine.is_editor_hint():
		_rotate(delta)

