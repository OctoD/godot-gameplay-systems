@tool
@icon("res://addons/godot_gameplay_systems/interactables/assets/InteractionIcon.png")
class_name Interaction extends Resource

## Represents an interaction

@export_category("Interaction")

@export_group("Tags added on", "tags_added_on_")
## Tags added when an interaction starts
@export var tags_added_on_start: Array[String] = []
## Tags added when an interaction is blocked
@export var tags_added_on_block: Array[String] = []
## Tags added when an interaction is cancelled
@export var tags_added_on_cancel: Array[String] = []
## Tags added when an interaction ends
@export var tags_added_on_end: Array[String] = []

@export_group("Tags required to", "tags_required_to_")
## Tags required to start an interaction
@export var tags_required_to_start: Array[String] = []
## Tags required to block an interaction
@export var tags_required_to_block: Array[String] = []
## Tags required to cancel an interaction
@export var tags_required_to_cancel: Array[String] = []
## Tags required to end an interaction
@export var tags_required_to_end: Array[String] = []

@export_group("Tags removed on", "tags_removed_on_")
## Tags removed when an interaction starts
@export var tags_removed_on_start: Array[String] = []
## Tags removed when an interaction is blocked
@export var tags_removed_on_block: Array[String] = []
## Tags removed when an interaction is cancelled
@export var tags_removed_on_cancel: Array[String] = []
## Tags removed when an interaction ends
@export var tags_removed_on_end: Array[String] = []


## Invoked right before an interaction ends.
## [br]It's a virtual method, so it can be overridden in a script.
func on_before_interaction_end(manager: InteractionManager, interacted_node: Node) -> void:
	pass


## Invoked right before an interaction starts.
## [br]It's a virtual method, so it can be overridden in a script.
func on_before_interaction_start(manager: InteractionManager, interacted_node: Node) -> void:
	pass


## Invoked each time an input is received when the interaction is active.
## [br]It's a virtual method, so it can be overridden in a script.
func handle_input(input: InputEvent, manager: InteractionManager, interacted_node: Node) -> void:
	pass


## Invoked inside the physics process if the interaction is active.
## [br]It's a virtual method, so it can be overridden in a script.
func handle_physics_process(delta: float, manager: InteractionManager, interacted_node: Node) -> void:
	pass


## Invoked inside the process if the interaction is active.
## [br]It's a virtual method, so it can be overridden in a script.
func handle_process(delta: float, manager: InteractionManager, interacted_node: Node) -> void:
	pass

