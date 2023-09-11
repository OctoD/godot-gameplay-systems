class_name TurnSubscriber extends Node

## A turn based participant
## 
## It represents a scene which can partecipate to a turn based game


## Emitted when this subscriber turn ends
signal turn_ended()
## Emitted when this subscriber turn starts
signal turn_started()
## Emitter when the turn round ended, 
signal turn_round_ended()


@export_group("Turn based game")
## Priority of this subscriber. The higher the priority, the sooner the turn starts.
@export var priority: int = 0


func _enter_tree() -> void:
	if TurnManager.get_turn_based_game() != null:
		TurnManager.get_turn_based_game().add_subscriber(self)


func _exit_tree() -> void:
	if TurnManager.get_turn_based_game() != null:
		TurnManager.get_turn_based_game().remove_subscriber(self)


func _ready() -> void:
	add_to_group("ggs.turnbased")

	if TurnManager.get_turn_based_game() != null:
		TurnManager.get_turn_based_game().add_subscriber(self)


## Called when the turn round ended
## [br]It's a virtual method, it can be overrided
func _turn_ended() -> void:
	pass


## Called when the turn round started
## [br]It's a virtual method, it can be overrided
func _turn_started() -> void:
	pass


## Ends the turn of this subscriber
func end_turn() -> void:
	if TurnManager.get_turn_based_game() != null:
		TurnManager.get_turn_based_game().next_turn()

