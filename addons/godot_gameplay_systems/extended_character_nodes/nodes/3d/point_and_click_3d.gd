@tool
class_name PointAndClick3D extends Node3D


## Emitted when the player clicks a new position
signal new_position_marked(position: Vector3)


@export_category("PointAndClick3D")
## Tells if the [code]PointAndClick3D[/code] is active.
@export var active: bool = true
## The movement speed
@export var movement_speed: float = 100.0
## Is the [CharacterBody3D] to move.
@export var character_3d: CharacterBody3D = null
## Is the [CharacterBody3D] child [NavigationAgent3D]. 
## Is used to determine the path in the world.
@export var navigation_agent: NavigationAgent3D = null
## If set to [code]true[/code] the [code]PointAndClick3D[/code] will move the [code]CharacterBody3D[/code] automatically.
@export var automatic_movement: bool = true

@export_flags_3d_physics var clickable_layer: int = 1


## Gets the current mouse position in the world.
var mouse_position: Vector3:
	get:
		if character_3d == null:
			return Vector3.ZERO

		var camera = get_viewport().get_camera_3d()
		var mouse_position = get_viewport().get_mouse_position()
		var direct_space_state = get_world_3d().direct_space_state
		var pos = camera.project_position(mouse_position, 100.0)
		var raycast_origin = camera.project_ray_origin(mouse_position)
		var raycast_end = (camera.project_ray_normal(mouse_position) + raycast_origin) * 2000.0
		# var query = PhysicsRayQueryParameters3D.new().create(raycast_origin, raycast_end, clickable_layer, [character_3d])
		var query = PhysicsRayQueryParameters3D.new().create(raycast_origin, pos, clickable_layer, [character_3d])
		var raycast_array = direct_space_state.intersect_ray(query)
		var target_position = raycast_array.get("position", Vector3.ZERO)

		if target_position != Vector3.ZERO:
			return target_position
		
		return Vector3.ZERO


func _handle_velocity_computed(_velocity: Vector3) -> void:
	character_3d.velocity = _velocity
	character_3d.move_and_slide()


## The physics process function
func _physics_process(delta: float) -> void:
	if not Engine.is_editor_hint() and automatic_movement:
		move_to_clicked_position()


## The ready function
func _ready() -> void:
	if not Engine.is_editor_hint():
		navigation_agent.velocity_computed.connect(_handle_velocity_computed)


## Returns [code]true[/code] if the navigation path's final position has been reached.
func is_navigation_finished() -> bool:
	if navigation_agent != null:
		return navigation_agent.is_navigation_finished()
	return false

	
## Moves the [code]CharacterBody3D[/code] to the clicked position.
func move_to_clicked_position() -> void:
	if Engine.is_editor_hint():
		return
	
	if navigation_agent == null:
		return
		
	if navigation_agent.is_navigation_finished():
		return

	if not active:
		return
	
	var _velocity: Vector3 = (navigation_agent.get_next_path_position() - global_position).normalized() * movement_speed

	if navigation_agent.avoidance_enabled:
		navigation_agent.set_velocity(_velocity)
	else:
		_handle_velocity_computed(_velocity)


## Sets the [code]navigation_agent[/code] target position to current click position.
func set_new_movement_position() -> void:
	if Engine.is_editor_hint():
		return
	
	if navigation_agent == null:
		return
	
	var target_position = mouse_position
	
	if target_position != Vector3.ZERO:
		navigation_agent.target_position = target_position
		new_position_marked.emit(target_position)


func stop_movement() -> void:
	navigation_agent.target_position = character_3d.position
