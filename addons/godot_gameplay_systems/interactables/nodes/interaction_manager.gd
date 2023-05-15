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

		return true
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
		if focused_interactable == null:
			return false

		return has_tags(focused_interactable.interaction.tags_added_on_start)
## It's the current focused interactable [Node].
var focused_interactable: Node = null
## It's the current focused interactable [Node]'s [Interaction].
var interaction: Interaction:
	get:
		return focused_interactable.interaction if can_interact else null


## Overrides virtual and handles input events
func _input(input: InputEvent) -> void:
	if is_interacting and interaction_raycast != null:
		focused_interactable.interaction.handle_input(input, self, focused_interactable)


## Overrides virtual and handles process
func _process(delta: float) -> void:
	if is_interacting and interaction_raycast != null:
		focused_interactable.interaction.handle_process(delta, self, focused_interactable)


## Overrides virtual and handles physics process
func _physics_process(delta: float) -> void:
	if is_interacting and interaction_raycast != null:
		focused_interactable.interaction.handle_physics_process(delta, self, focused_interactable)


func _ready() -> void:
	var handle_raycast_detection = func (node: Node) -> void:
		if focused_interactable != node and node != null:
			interactable_focus_out.emit(node)
			interactable_focus_in.emit(node)
			focused_interactable = node
		elif focused_interactable != node and node == null:
			interactable_focus_out.emit(focused_interactable)
			focused_interactable = null

	if interaction_raycast != null:
		interaction_raycast.interactable_focus_in.connect(handle_raycast_detection)

	interacting_owner.child_entered_tree.connect(func (node: Node) -> void:
		if node is InteractionRayCast2D or node is InteractionRayCast3D and node.interactable_focus_in.get_connection_count(handle_raycast_detection) == 0:
			node.interactable_focus_in.connect(handle_raycast_detection)
	)


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
		return has_tags(interaction.tags_required_to_end) and not has_tags(interaction.tags_required_to_block)
	return true


## Returns [code]true[/code] if can starts interaction, [code]false[/code] otherwise.
func can_start_interaction() -> bool:
	if can_interact and interaction != null:
		return not has_tags(interaction.tags_added_on_start, false) and has_tags(interaction.tags_required_to_start)
	return false


## Starts an interaction with the currently focused node.
func interact_start() -> void:
	if can_start_interaction():
		focused_interactable.interaction


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
