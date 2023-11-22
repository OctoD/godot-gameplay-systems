class_name TurnBasedGame extends Node


## Emitted when a turn changes.
signal turn_changed(manager: TurnBasedGame)
## Emitted when the turn based game starts.
signal turn_game_started()
## Emitted when the turn based game stops.
signal turn_game_stopped()
## Emitted when a subscriber is added.
signal subscriber_added(subscriber: TurnSubscriber)
## Emitted when a subscriber is removed.
signal subscriber_removed(subscriber: TurnSubscriber)


## The current turn.
var current_turn: int = 0
## The current turn subscriber.
var current_turn_subscriber: TurnSubscriber:
	get:
		if subscribers.size() == 0:
			return null

		return subscribers[current_turn]
## The turn subscribers.
var subscribers: Array[TurnSubscriber] = []


func _ready() -> void:
	add_to_group("ggs.turnbased")


func _sort_subscribers() -> void:
	subscribers.sort_custom(func (a, b): 
		return a.priority < b.priority
	)


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
		
	subscribers.append(sub)
	subscriber_added.emit(sub)

	_sort_subscribers()
	
	return true


## Ends the current turn
func end_turn_sequence() -> void:
	if subscribers.size() == 0:
		return

	subscribers[current_turn].end_turn()

	current_turn = 0

	turn_game_stopped.emit()


## Calls next turn
func next_turn() -> void:
	var subscribers_count := subscribers.size()

	if current_turn < subscribers_count:
		subscribers[current_turn].turn_ended.emit()
		subscribers[current_turn]._turn_ended()

	current_turn += 1

	if current_turn >= subscribers_count:
		current_turn = 0

	subscribers[current_turn].turn_started.emit()
	subscribers[current_turn]._turn_started()


## Removes a [TurnSubscriber]
func remove_subscriber(sub: TurnSubscriber) -> bool:
	if not subscribers.has(sub):
		return false
	
	var sub_turn_index = subscribers.find(sub)
	
	subscribers.remove_at(sub_turn_index)
	subscriber_removed.emit(sub)

	_sort_subscribers()

	return true


## Starts the turn based game.
func start_turn_sequence() -> void:
	if subscribers.size() == 0:
		return

	current_turn = 0

	subscribers[current_turn]._turn_started()
	subscribers[current_turn].turn_started.emit()

	turn_game_started.emit()
