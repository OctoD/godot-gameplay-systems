@tool
class_name HazardPathFollow2D extends PathFollow2D


@export_category("Hazard")
@export var speed := 2.0


func _physics_process(delta: float) -> void:
	progress += speed * delta
