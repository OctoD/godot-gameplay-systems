@tool
class_name PointAndClick2D extends Node2D


signal new_position_marked(position: Vector2)


@export_category("PointAndClick2D")
## Tells if the [code]PointAndClick2D[/code] is active.
@export var active: bool = true
## The movement speed
@export var movement_speed: float = 100.0
## Is the [CharacterBody2D] to move.
@export var character_2d: CharacterBody2D = null
## Is the [CharacterBody2D] child [NavigationAgent2D]. 
## Is used to determine the path in the world.
@export var navigation_agent: NavigationAgent2D = null
## If set to [code]true[/code] the [code]PointAndClick2D[/code] will move the [code]CharacterBody2D[/code] automatically.
@export var automatic_movement: bool = true


## Returns the mouse position in a 2D world.
var mouse_position: Vector2:
	get:
		return character_2d.get_global_mouse_position()


## Handles movement
func _handle_velocity_computed(_velocity: Vector2) -> void:
	character_2d.velocity = _velocity
	character_2d.move_and_slide()


## The physics process function
func _physics_process(delta: float) -> void:
	if not Engine.is_editor_hint() and automatic_movement:
		move_to_clicked_position()


## The ready function
func _ready() -> void:
	if not Engine.is_editor_hint():
		navigation_agent.velocity_computed.connect(_handle_velocity_computed)


## Returns [code]true[/code] if the [CharacterBody2D] can move.
func can_move() -> bool:
	if Engine.is_editor_hint():
		return false

	if navigation_agent == null:
		return false

	if character_2d == null:
		return false

	return active


## Returns [code]true[/code] if the [code]navigation_agent[/code] is not [code]null[/code] and the [code]navigation_agent[/code] has finished navigating.
func is_navigation_finished() -> bool:
	if navigation_agent != null:
		return navigation_agent.is_navigation_finished()
	return false


## Moves the [code]character_2d[/code] to the clicked position with the given speed.
func move_to_clicked_position() -> void:
	if can_move():
		var _velocity: Vector2 = (navigation_agent.get_next_path_position() - global_position).normalized() * movement_speed

		if navigation_agent.avoidance_enabled:
			navigation_agent.set_velocity(_velocity)
		else:
			_handle_velocity_computed(_velocity)


## Sets the [code]navigation_agent[/code] target position to current click position.
func set_new_movement_position() -> void:
	if can_move():
		navigation_agent.target_position = mouse_position
		new_position_marked.emit(navigation_agent.target_position)



## Stops the [code]navigation_agent[/code] movement.
func stop_movement() -> void:
	if can_move():
		navigation_agent.target_position = character_2d.position

