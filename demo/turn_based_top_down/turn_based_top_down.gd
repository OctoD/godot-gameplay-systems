extends Node


@onready var start: Button = $Control/Start
@onready var next_turn: Button = $Control/NextTurn


func _ready() -> void:
	start.pressed.connect(handle_start, CONNECT_ONE_SHOT)
	next_turn.pressed.connect(handle_next)

	next_turn.visible = false


func handle_next() -> void:
	TurnManager.get_turn_based_game().next_turn()


func handle_start() -> void:
	TurnManager.get_turn_based_game().start_turn_sequence()
	start.queue_free()
	next_turn.visible = true
