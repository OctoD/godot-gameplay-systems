@tool
extends EffectedArea2D

@export_category("Projectile")
@export var texture: Texture2D = null:
	get:
		return texture
	set(value):
		texture = value
		sprite2d.texture = texture
@export var texture_scale: Vector2 = Vector2.ONE:
	get:
		return texture_scale
	set(value):
		texture_scale = value
		sprite2d.scale = value

@onready var sprite2d: Sprite2D = $Sprite2D

var speed: float = 5.0
var velocity: Vector2 = Vector2.ZERO


func _physics_process(delta: float) -> void:
	position += velocity * speed * delta
