@icon("res://addons/godot_gameplay_systems/interactables/assets/InteractionIcon.png")
@tool
class_name InteractionManager extends Node


## Handles interactions.


## Emitted when a bound raycast detects and interactable.
signal interactable_focus_in(interactable: Node)
## Emitted when a bound raycast loses a focus to an interactable.
signal interactable_focus_out(interactable: Node)
## Emitted when an interaction is blocked.
signal interaction_blocked(interactable: Node, interaction: Interaction)
## Emitted when an interaction is cancelled.
signal interaction_cancelled(interactable: Node, interaction: Interaction)
## Emitted when an interaction is ended.
signal interaction_ended(interactable: Node, interaction: Interaction)
## Emitted when an interaction is started.
signal interaction_started(interactable: Node, interaction: Interaction)
## Emitted when an interaction is refused to block.
signal interaction_block_refused(interactable: Node, interaction: Interaction)
## Emitted when an interaction is refused to cancel.
signal interaction_cancel_refused(interactable: Node, interaction: Interaction)
## Emitted when an interaction is refused to end.
signal interaction_end_refused(interactable: Node, interaction: Interaction)
## Emitted when an interaction is refused to start.
signal interaction_start_refused(interactable: Node, interaction: Interaction)
## Emitted when tags have changed.
signal tags_changed()

@export_category("Interaction")
## The path to the interaction owner.
@export_node_path("Node2D", "Node3D") var interacting_owner_path := NodePath()
## The path to the interaction raycast node.
@export_node_path("InteractionRayCast2D", "InteractionRayCast3D") var interaction_raycast_path := NodePath()

@export_group("Tags", "tags_")
## The tags associated to this interaction manager.
@export var tags: Array[String] = []
## Tags which will blocks the interaction completely.
@export var tags_blocking_interaction: Array[String] = []
## Tags required to trigger an interaction.
@export var tags_required_to_interact: Array[String] = []


## Checks if it can interact.
var can_interact: bool:
	get:
		if tags_blocking_interaction.size() == 0 and tags_required_to_interact.size() == 0:
			return true

		if tags_blocking_interaction.size() > 0:
			for tag in tags_blocking_interaction:
				if tags.has(tag):
					return false

		if tags_required_to_interact.size() > 0:
			for tag in tags_required_to_interact:
				if not tags.has(tag):
					return false

		return focused_interactable != null
## Is the interacting owner. Usually a [CharacterBody2D] or [CharacterBody3D].
var interacting_owner: Node:
	get:
		if interacting_owner != null:
			return interacting_owner

		interacting_owner = get_node(interacting_owner_path)
		return interacting_owner
	set(value):
		interacting_owner = value
## Is an interaction raycast. Used to determine if the owner can see and reach the interactable.
var interaction_raycast: Node:
	get:
		if interaction_raycast != null:
			return interaction_raycast

		interaction_raycast = get_node(interaction_raycast_path)
		return interaction_raycast
	set(value):
		interaction_raycast = value
## Is [code]true[/code] if the [InteractionManager]
var is_interacting: bool:
	get:
		if current_interactable == null:
			return false

		if current_interactable.interaction == null:
			return false

		if current_interactable.interaction.tags_added_on_start.size() > 0:
			return has_tags(current_interactable.interaction.tags_added_on_start)

		return true
## It's the current interactable [Node]. This variable is stored when you start an interaction and cleared when you end an interaction.
var current_interactable: Node = null
## It's the current focused interactable [Node].
var focused_interactable: Node = null
## It's the current focused interactable [Node]'s [Interaction].
var interaction: Interaction:
	get:
		if current_interactable == null:
			return null

		return current_interactable.interaction if is_interacting else null


func _handle_focus_in(node: Node) -> void:
	interactable_focus_in.emit(node)
	focused_interactable = node


func _handle_focus_out(node: Node) -> void:
	interactable_focus_out.emit(node)
	focused_interactable = null


## Overrides virtual and handles input events
func _input(input: InputEvent) -> void:
	if is_interacting and interaction_raycast != null:
		current_interactable.interaction.handle_input(input, self, current_interactable)


## Overrides virtual and handles process
func _process(delta: float) -> void:
	if is_interacting and interaction_raycast != null:
		current_interactable.interaction.handle_process(delta, self, current_interactable)


## Overrides virtual and handles physics process
func _physics_process(delta: float) -> void:
	if is_interacting and interaction_raycast != null:
		current_interactable.interaction.handle_physics_process(delta, self, current_interactable)


func _ready() -> void:
	if interaction_raycast != null:
		interaction_raycast.interactable_detected.connect(_handle_focus_in)
		interaction_raycast.interactable_focus_in.connect(_handle_focus_in)
		interaction_raycast.interactable_focus_out.connect(_handle_focus_out)


## Adds a tag. 
func add_tag(tag: String) -> void:
	if not tags.has(tag):
		tags.append(tag)
		tags_changed.emit()


## Adds many tags at once.
## [br]Note: this will emit the [signal InteractionManager.tags_changed] only once.
func add_tags(tags: Array[String]) -> void:
	var updated = false

	for tag in tags:
		if not self.tags.has(tag):
			self.tags.append(tag)
			updated = true

	if updated:
		tags_changed.emit()


## Returns [code]true[/code] if can ends interaction, [code]false[/code] otherwise.
func can_end_interaction() -> bool:
	if can_interact and interaction != null:
		if interaction.tags_required_to_block.size() > 0:
			return not has_tags(interaction.tags_required_to_block) and has_tags(interaction.tags_required_to_end)
		else:
			return has_tags(interaction.tags_required_to_end)
	return true


## Returns [code]true[/code] if can starts interaction, [code]false[/code] otherwise.
func can_start_interaction() -> bool:
	return can_interact and focused_interactable.interaction != null


## Ends an interaction with the currently focused node.
## [br]Note: this will emit the [signal InteractionManager.tags_changed] only once.
## [br]Note: this will emit the [signal InteractionManager.interaction_ended] only once.
func end_interaction() -> void:
	if can_end_interaction():
		if current_interactable.has_method("_on_interaction_ended"):
			current_interactable.call("_on_interaction_ended", self)

		current_interactable.interaction.on_before_interaction_end(self, current_interactable)
		add_tags(current_interactable.interaction.tags_added_on_end)
		remove_tags(current_interactable.interaction.tags_removed_on_end)
		interaction_ended.emit(current_interactable)
		current_interactable = null


## Starts an interaction with the currently focused node.
## [br]Note: this will emit the [signal InteractionManager.tags_changed] only once.
## [br]Note: this will emit the [signal InteractionManager.interaction_started] only once.
func start_interaction() -> void:
	if can_start_interaction():
		focused_interactable.interaction.on_before_interaction_start(self, focused_interactable)
		add_tags(focused_interactable.interaction.tags_added_on_start)
		remove_tags(focused_interactable.interaction.tags_removed_on_start)
		interaction_started.emit(focused_interactable)
		current_interactable = focused_interactable

		if current_interactable.has_method("_on_interaction_started"):
			current_interactable.call("_on_interaction_started", self)


## Checks if has a tag.
func has_tag(tag: String) -> bool:
	return tags.has(tag)


## Checks if has tags.
## [br]If the param [code]match_all[/code] is [code]true[/code], then this [InteractionManager] must have all the passed tags.
## [br]If the param [code]match_all[/code] is [code]false[/code], then this function returns [code]true[/code] if this [InteractionManager] has one or many tags passed.
func has_tags(tags: Array[String], match_all: bool = true) -> bool:
	for tag in tags:
		if not self.tags.has(tag) and match_all:
			return false
		elif self.tags.has(tag) and not match_all:
			return true
	return true


## Removes a tag. Returns [code]true[/code] if the tag is removed, [code]false[/code] otherwise.
func remove_tag(tag: String) -> bool:
	var index = tags.find(tag)

	if index < 0:
		return false

	tags.remove_at(index)
	tags_changed.emit()

	return true


## Removes a tag. Returns the count of the removed elements.
func remove_tags(tags: Array[String]) -> int:
	var count = 0

	for tag in tags:
		var index = self.tags.find(tag)

		if index >= 0:
			self.tags.remove_at(index)
			count += 1

	if count > 0:
		tags_changed.emit()

	return count
