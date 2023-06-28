extends CharacterBody2D
class_name Player


# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity: int = ProjectSettings.get_setting("physics/2d/default_gravity")
var speed: float = 0.0
var jump_velocity: float = 0.0
var flipped := true

var is_dead: bool:
	get:
		var attribute = gameplay_attribute_map.get_attribute_by_name("health")
		
		if attribute:
			return attribute.current_value <= 0.0
		
		return true

@onready var ability_container: AbilityContainer = $AbilityContainer
@onready var animated_sprite: AnimatedSprite2D = $CollisionShape2d/AnimatedSprite2D
@onready var camera_shake: CameraShake = $CameraShake
@onready var gameplay_attribute_map: GameplayAttributeMap = $GameplayAttributeMap
@onready var hud = $Camera2D/CanvasLayer/Hud
@onready var inventory: Inventory = $Inventory


func _handle_attribute_changed(spec: AttributeSpec) -> void:
	var prev_health = gameplay_attribute_map.get_attribute_by_name("health").current_value
	
	hud.handle_attribute_changed(spec)
	
	match spec.attribute_name:
		"health":
			if prev_health > spec.current_value:
				velocity.y -= 5.0
			if spec.current_value <= 0.0:
				print("Added dead tag to player ability container")
				ability_container.add_tag("dead")
				## Shake for the death
				camera_shake.shake(50.0, 1, 250)


func _ready() -> void:
	speed = gameplay_attribute_map.get_attribute_by_name("speed").current_value
	jump_velocity = gameplay_attribute_map.get_attribute_by_name("jump_height").current_value

	gameplay_attribute_map.attribute_changed.connect(_handle_attribute_changed)

	hud.initialize_attributes(gameplay_attribute_map)
	
	animated_sprite.play("default")
	

func _input(event: InputEvent) -> void:
	if event.is_action_pressed("resurrect"):
		var resurrect = ability_container.find_by(func (x): return x is ResurrectAbility)
		
		if resurrect:
			ability_container.activate_one(resurrect)
	
	if event.is_action_pressed("fireball"):
		var fireball = ability_container.find_by(func (x): return x is FireballAbility)
	
		if fireball:
			ability_container.activate_one(fireball)

			if not is_dead:
				camera_shake.shake(3.0, 0.5, 400)


func _physics_process(delta: float) -> void:
	# Add the gravity.
	if not is_on_floor():
		velocity.y += gravity * delta
		

	# You are dead, sorry. Press "r" to resurrect
	if is_dead:
		velocity.x = 0
		animated_sprite.stop()
		move_and_slide()
		return
		

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
