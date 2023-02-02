extends CharacterBody2D
class_name Player


signal attribute_changed(attribute_name: String, new_value: float, old_value: float)


# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity: int = ProjectSettings.get_setting("physics/2d/default_gravity")
var speed: float = 0.0
var jump_velocity: float = 0.0

@onready var gameplay_attribute_map: GameplayAttributeMap = $GameplayAttributeMap


func _ready() -> void:
	speed = gameplay_attribute_map.get_attribute_by_name("speed").current_value
	jump_velocity = gameplay_attribute_map.get_attribute_by_name("jump_height").current_value

	gameplay_attribute_map.attribute_changed.connect(func (attribute):
		attribute_changed.emit(attribute.attribute_name, attribute.current_value, 0)
	)

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

	move_and_slide()
