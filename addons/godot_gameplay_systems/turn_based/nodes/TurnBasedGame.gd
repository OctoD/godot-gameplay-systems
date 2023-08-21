class_name TurnBasedGame extends Node


## Emitted when a turn changes.
signal turn_changed(manager: TurnBasedGame)
## Emitted when the turn based game starts.
signal turn_game_started()
## Emitted when the turn based game stops.
signal turn_game_stopped()


@export_category("Turn based configuration")
## The turn duration. If set to [code]0[/code] the turn lasts until the current active turn is finished.
@export_range(0.0, 1000.0, 1.0) var turn_duration: float = 0.0


var current_turn: int = 0
var subscribers: Array[TurnSubscriber] = []


func _ready() -> void:
	add_to_group("ggs.turnbased")


## Called when a [TurnSubscriber] is subscribed.
## [br]This is a virtual method
func _subscriber_added(sub: TurnSubscriber) -> void:
	pass


## Called when a [TurnSubscriber] is unsubscribed.
## [br]This is a virtual method
func _subscriber_removed(sub: TurnSubscriber) -> void:
	pass


## Adds a [TurnSubscriber]
func add_subscriber(sub: TurnSubscriber) -> bool:
	if subscribers.has(sub):
		return false

	_subscriber_added(sub)
	
	subscribers.append(sub)
	return true


## Calls next turn
func next_turn() -> void:
	var subscribers_count := subscribers.size()
	
	if current_turn < subscribers_count:
		subscribers[current_turn].end_turn()

	current_turn += 1
	
	if current_turn > subscribers_count:
		current_turn = 0


func remove_subscriber(sub: TurnSubscriber) -> bool:
	if not subscribers.has(sub):
		return false
	
	var sub_turn_index = subscribers.find(func (x): return x == sub)
	
	subscribers.remove_at(sub_turn_index)
	
	_subscriber_removed(sub)

	return true
