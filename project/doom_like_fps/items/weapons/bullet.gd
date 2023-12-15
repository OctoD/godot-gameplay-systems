extends EffectedArea3D


var damage: float = 10.0
var speed: float = 10.0
var velocity = Vector3.ZERO


func _ready() -> void:
	var effect = GameplayEffect.new()
	var health_effect = AttributeEffect.new()
	
	health_effect.attribute_name = "health"
	health_effect.maximum_value = -absf(damage)
	health_effect.minimum_value = -absf(damage)
	
	effect.attributes_affected.append(health_effect)
	
	add_child(effect)

	super._ready()


func _physics_process(delta: float) -> void:
	velocity += Vector3.DOWN * gravity * delta
	look_at(transform.origin + velocity.normalized(), Vector3.UP)
	transform.origin += velocity * delta
