extends CharacterBody3D


@onready var point_and_click: PointAndClick3D = $PointAndClick3D
@onready var mesh_instance_3D: MeshInstance3D = $MeshInstance3D


func _input(event: InputEvent) -> void:
	if event.is_action_pressed("diablo_like_move_to"):
		point_and_click.set_new_movement_position()
		mesh_instance_3D.look_at(point_and_click.mouse_position)
