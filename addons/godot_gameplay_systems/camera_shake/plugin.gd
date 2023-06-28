@tool
extends EditorPlugin


func _enter_tree() -> void:
	add_custom_type("CameraShake", "Node", load("res://addons/godot_gameplay_systems/camera_shake/nodes/camera_shake.gd"), null)


func _exit_tree() -> void:
	remove_custom_type("CameraShake")
