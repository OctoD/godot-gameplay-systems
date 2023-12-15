extends EffectedArea2D


var direction := Vector2.RIGHT
var speed = 10.0


func _physics_process(delta: float) -> void:
	rotate(5 * delta)
	global_position += direction * speed
