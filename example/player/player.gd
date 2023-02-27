extends CharacterBody2D
class_name Player


# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity: int = ProjectSettings.get_setting("physics/2d/default_gravity")
var speed: float = 0.0
var jump_velocity: float = 0.0
var flipped := true

@onready var gameplay_attribute_map: GameplayAttributeMap = $GameplayAttributeMap
@onready var hud = $Hud
@onready var animated_sprite: AnimatedSprite2D = $CollisionShape2d/AnimatedSprite2D


func _handle_attribute_changed(spec: GameplayAttributeMap.AttributeSpec) -> void:
	var prev_health = gameplay_attribute_map.get_attribute_by_name("health").current_value
	
	hud.handle_attribute_changed(spec)
	
	match spec.attribute_name:
		"health":
			if prev_health > spec.current_value:
				velocity.y -= 5.0


func _ready() -> void:
	speed = gameplay_attribute_map.get_attribute_by_name("speed").current_value
	jump_velocity = gameplay_attribute_map.get_attribute_by_name("jump_height").current_value

	gameplay_attribute_map.attribute_changed.connect(_handle_attribute_changed)

	hud.initialize(gameplay_attribute_map)
	animated_sprite.play("default")
	


func _physics_process(delta: float) -> void:
	# Add the gravity.
	if not is_on_floor():
		velocity.y += gravity * delta

	# Handle Jump.
	if Input.is_action_just_pressed("ui_up") and is_on_floor():
		velocity.y = jump_velocity

	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var direction := Input.get_axis("ui_left", "ui_right")
	if direction:
		velocity.x = direction * speed
	else:
		velocity.x = move_toward(velocity.x, 0, speed)

	if velocity.x > 1:
		flipped = true
	elif velocity.x < -1:
		flipped = false

	animated_sprite.flip_h = flipped

	move_and_slide()
