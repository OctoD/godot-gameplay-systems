extends Node3D


@export_category("Sail config")
@export_range(0.0, 360.0, 0.1) var max_rotation := 60.0
@export_range(0, 100, 1) var rotation_speed := 20

@export_range(0.0, 10.0, 0.1) var max_height := 4.0
@export_range(0, 100, 1) var sail_speed := 20


@onready var mesh: CSGBox3D = $CSGBox3D


var max_top := 0.0


func set_movement(vec: Vector2) -> void:
	rotation.y -= vec.x * rotation_speed / 1000.0
	rotation.y = deg_to_rad(clampf(rad_to_deg(rotation.y), -max_rotation, max_rotation))

	mesh.size.y += vec.y * sail_speed / 1000.0
	mesh.size.y = clampf(mesh.size.y, 0.0, max_height)
	mesh.position.y = max_height - (mesh.size.y / 2)
