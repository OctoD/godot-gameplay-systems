class_name SotLikePlayer extends CharacterBody3D


const INTERACTING_TAG = "player.interacting"
const SPEED = 5.0
const JUMP_VELOCITY = 4.5

# Get the gravity from the project settings to be synced with RigidBody nodes.
var gravity: float = ProjectSettings.get_setting("physics/3d/default_gravity", 9.8)

@export_category("Player Setup")
@export var mouse_sensitivity: float = 0.004


@onready var camera_neck: Node3D = $CameraNeck
@onready var raycast: InteractionRayCast3D = $CameraNeck/Camera3D/InteractionRayCast3D
@onready var interaction_manager: InteractionManager = $InteractionManager
@onready var interaction_explanation: Label = $BoxContainer/InteractionExplanation/ExplanationLabel


var can_move: bool:
	get:
		return not interaction_manager.has_tag(INTERACTING_TAG)
var is_interacting: bool:
	get:
		return interaction_manager.has_tag(INTERACTING_TAG)


func _ready() -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CAPTURED


func _handle_interaction(_delta: float) -> void:
	pass


func _handle_movement(_delta: float) -> void:
	# Handle Jump.
	if Input.is_action_just_pressed("fps_jump") and is_on_floor():
		velocity.y = JUMP_VELOCITY

	# Get the input direction and handle the movement/deceleration.
	# As good practice, you should replace UI actions with custom gameplay actions.
	var input_dir := Input.get_vector("fps_strafe_left", "fps_strafe_right", "fps_move_forward", "fps_move_backward")
	var direction := (transform.basis * Vector3(input_dir.x, 0, input_dir.y)).normalized()
	if direction:
		velocity.x = direction.x * SPEED
		velocity.z = direction.z * SPEED
	else:
		velocity.x = move_toward(velocity.x, 0, SPEED)
		velocity.z = move_toward(velocity.z, 0, SPEED)


func _physics_process(delta: float) -> void:
	# Add the gravity.
	if not is_on_floor():
		velocity.y -= gravity * delta

	if Input.is_action_just_pressed("fps_interact"):
		interaction_manager.handle_interaction(raycast)

	if is_interacting:
		_handle_interaction(delta)
	else:
		_handle_movement(delta)

	move_and_slide()
	



func _input(event: InputEvent):
	if event is InputEventMouseMotion:
		var y = event.relative.x * mouse_sensitivity
		var x = event.relative.y * mouse_sensitivity
		rotate_y(-y)
		camera_neck.rotate_x(x)
		camera_neck.rotation.x = clamp(camera_neck.rotation.x, -1.2, 1.2)
