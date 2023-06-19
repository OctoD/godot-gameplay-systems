extends EditorPlugin


func _enter_tree() -> void:
	add_custom_type("PointAndClick2D", "Node2D", load("res://addons/godot_gameplay_systems/extended_character_nodes/nodes/2d/point_and_click_2d.gd"), null)
	add_custom_type("PointAndClick3D", "Node3D", load("res://addons/godot_gameplay_systems/extended_character_nodes/nodes/3d/point_and_click_3d.gd"), null)


func _exit_tree() -> void:
	remove_custom_type("PointAndClick2D")
	remove_custom_type("PointAndClick3D")

	