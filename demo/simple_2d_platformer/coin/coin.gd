class_name Coin extends EffectedArea2D


@onready var animated_sprite_2d = $AnimatedSprite2D


func _ready() -> void:
	super._ready()
	animated_sprite_2d.play("default")


func _physics_process(delta: float) -> void:
	rotate(1 * delta)

