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
## It gives this subscriber
@export var priority: int = 0


var game: TurnBasedGame:
	get:
		for child in get_tree().get_nodes_in_group("ggs.turnbased"):
			if child is TurnBasedGame:
				return child
		return null


func _enter_tree() -> void:
	var _game = game
	
	if _game != null:
		_game.add_subscriber(self)


func _exit_tree() -> void:
	var _game = game
	
	if _game != null:
		_game.remove_subscriber(self)


func _ready() -> void:
	add_to_group("ggs.turnbased")


func end_turn() -> void:
	var _game = game
	
	if _game != null:
		_game.next_turn()

