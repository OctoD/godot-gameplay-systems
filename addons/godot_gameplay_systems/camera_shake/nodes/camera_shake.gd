class_name CameraShake extends Node


## Emitted when the shake ends
signal shake_ended()
## Emitted when the shake starts
signal shake_started()
## Emitted when a shake occurs
signal shaken(remaining_times: int)


enum CameraContext {
	CAMERA_2D,
	CAMERA_3D,
}


@export_category("Camera shake")
## The path to the camera to shake
@export_node_path("Camera2D", "Camera3D") var camera_path: NodePath = NodePath()

@export_group("Minimum values", "min_")
## The minimum strength appliable to the shake
@export var min_strength: float = 0.0
## How many seconds the camera will be shaked (min)
@export var min_duration: float = 0.0
## How many times per second the camera will be shaked (min)
@export var min_frequency: int = 0

@export_group("Maximum values", "max_")
## The maximum strength appliable to the shake
@export var max_strength: float = 50.0
## How many seconds the camera will be shaked (max)
@export var max_duration: float = 5.0
## How many times per second the camera will be shaked (max)
@export var max_frequency: int = 50

## The camera 2d/3d node
var camera: Node
## The camera context
var camera_context: CameraContext
## Current applied duration
var duration: float = 0.0:
	get:
		return duration
	set(value):
		duration = clampf(value, min_duration, max_duration)
## Current applied frequency
var frequency: int = 0:
	get:
		return frequency
	set(value):
		frequency = clampf(value, min_frequency, max_frequency)
## Previous used [Tween]. Is [code]null[/code] if the [member CameraShake.camera] never shook or the previous [Tween] finished it's own job.
var previous_tween: Tween
## Current applied strength
var strength: float = 0.0:
	get:
		return strength
	set(value):
		strength = clampf(value, min_strength, max_strength)
## Time remaining before the shake effect ends
var time_remaining: float = 0.0:
	get:
		return duration / float(frequency)
## Returns the number of tweens to operate
var tweens_range: Array:
	get:
		return range(0, duration * frequency)

## Applies the shake
func _apply_shake() -> void:
	if camera_context == CameraContext.CAMERA_2D:
		_apply_shake_2d()
	elif camera_context == CameraContext.CAMERA_3D:
		_apply_shake_3d()


## Applies the shake using 2D context
func _apply_shake_2d() -> void:
	var _camera = camera as Camera2D
	
	assert(_camera != null, "Camera (2D) should not be null at this point, check your code before shaking the camera again")
	
	if previous_tween:
		previous_tween.stop()
	
	previous_tween = create_tween()
	previous_tween.tween_property(_camera, "offset", Vector2(0.0, 0.0), time_remaining)
	
	print("duration: ", duration)
	print("time_remaining: ", time_remaining)
	print("duration * frequency: ", duration * frequency)
	print("tweens_range: ", tweens_range)

	for _n in tweens_range:
		previous_tween.tween_property(_camera, "offset", Vector2(_get_shake_value(), _get_shake_value()), time_remaining)

	previous_tween.tween_property(_camera, "offset", Vector2(0.0, 0.0), time_remaining)
	previous_tween.play()
	
	previous_tween.step_finished.connect(func (_x):
		previous_tween = null
	)


## Applies the shake using 3D context
func _apply_shake_3d() -> void:
	var _camera = camera as Camera3D

	assert(_camera != null, "Camera (3D) should not be null at this point, check your code before shaking the camera again")

	if previous_tween != null:
		previous_tween.stop()

	previous_tween = create_tween()
	previous_tween.tween_property(_camera, "h_offset", 0.0, time_remaining)
	previous_tween.tween_property(_camera, "v_offset", 0.0, time_remaining)

	print("tweens_range: ", tweens_range)
	print("time_remaining: ", time_remaining)
	print("duration: ", duration)
	print("frequency: ", frequency)

	for _n in tweens_range:
		previous_tween.tween_property(_camera, "h_offset", _get_shake_value(), time_remaining)
		previous_tween.tween_property(_camera, "v_offset", _get_shake_value(), time_remaining)

	previous_tween.tween_property(_camera, "h_offset", 0.0, time_remaining)
	previous_tween.tween_property(_camera, "v_offset", 0.0, time_remaining)
	previous_tween.play()


func _get_shake_value(rerolls_remaining: int = 5) -> float:
	var shake_value = randf_range(-1.0, 1.0) * strength

	# Avoiding stack overflows
	if max_strength == 0.0 and shake_value == 0.0:
		return 0.0
		
	# Rerolls
	if shake_value == 0.0 and rerolls_remaining > 0:
		return _get_shake_value(rerolls_remaining - 1)

	return shake_value


func _ready() -> void:
	if camera_path.is_empty():
		if owner is Camera2D or owner is Camera3D:
			camera = owner
	else:
		camera = get_node(camera_path)

	assert(camera != null, "Camera is null. Set camera_path correctly.")

	## Try to guess if the camera is a Camera2D
	if camera is Camera2D:
		camera_context = CameraContext.CAMERA_2D
	## Try to guess if the camera is a Camera3D
	elif camera is Camera3D:
		camera_context = CameraContext.CAMERA_3D


## Resets shake 2D
func _reset_from_shake_2d() -> void:
	camera.offset = Vector2.ZERO


## Resets shake 2D
func _reset_from_shake_3d() -> void:
	camera.h_offset = 0.0
	camera.v_offset = 0.0


## Shakes current camera by the given strength, duration, and frequency.
## [br][code]strength[/code] defaults to [code]1.0[/code]
## [br][code]duration[/code] defaults to [code]1.0[/code]
## [br][code]frequency[/code] defaults to [code]5[/code]
func shake(strength: float = 1.0, duration: float = 1.0, frequency: int = 5) -> void:
	self.strength = strength
	self.duration = duration
	self.frequency = frequency

	_apply_shake()


## Resets from shake
func reset_from_shake() -> void:
	if camera is Camera2D:
		_reset_from_shake_2d()
	elif camera is Camera3D:
		_reset_from_shake_3d()
