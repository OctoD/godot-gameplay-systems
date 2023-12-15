extends CharacterBody3D


@export var turn_priority: int = 0
@onready var point_and_click_3d: PointAndClick3D = $PointAndClick3D
@onready var turn_subscriber: TurnSubscriber = $TurnSubscriber
@onready var current_turn_indicator: MeshInstance3D = $CurrentTurnIndicator


func _ready() -> void:
	turn_subscriber.priority = turn_priority
	current_turn_indicator.visible = false

	set_process_input(false)

	turn_subscriber.turn_started.connect(func ():
		set_process_input(true)
		current_turn_indicator.visible = true
	)

	turn_subscriber.turn_ended.connect(func ():
		set_process_input(false)
		current_turn_indicator.visible = false
	)


func _input(event: InputEvent) -> void:
	if event.is_action_pressed("diablo_like_move_to"):
		point_and_click_3d.set_new_movement_position()

