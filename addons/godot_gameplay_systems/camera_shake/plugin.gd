@tool
extends EditorPlugin


func _enter_tree() -> void:
	add_custom_type("CameraShake", "Node", preload("./nodes/camera_shake.gd"), null)


func _exit_tree() -> void:
	remove_custom_type("CameraShake")
