class_name SotLikeCrate extends InteractableArea3D


@export var fall_speed := 9.8


@onready var fell_raycast: RayCast3D = $RayCast3D

var dragged := false


func _physics_process(delta: float) -> void:
	var collider = fell_raycast.get_collider()
	
	if collider == null and not dragged:
		# apply simulated gravity fallspeed
		position += Vector3(0, -absf(fall_speed), 0) * delta
		rotation = Vector3(0, 0, 0)

