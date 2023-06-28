## AbilityContainer
## 
## This is the container for [Ability] resources.
## [br][Ability] resources can be activated, cancelled or finished under some circumstances and are used to apply 
## [GameplayEffect] resources to [GameplayAttributeMap] instances.

@icon("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/AbilityContainer.svg")

class_name AbilityContainer extends Node


## Represents an [Ability] lifecycle state.
enum LifeCycle {
	Activated = 0,
	Blocked = 1,
	Cancelled = 2,
	Ended = 3,
	CooldownStarted = 4,
	CooldownEnded = 5,
}


## Emitted when an ability is activated manually or automatically
signal ability_activated(ability: Ability, activation_event: ActivationEvent)
## Emitted when an ability blocked it's execution. This happen when the [method Ability.can_block] returns [code]true[/code]. 
signal ability_blocked(ability: Ability, activation_event: ActivationEvent)
## Emitted when an ability is manually or automatically cancelled
signal ability_cancelled(ability: Ability, activation_event: ActivationEvent)
## Emitted when an ability has ended
signal ability_ended(ability: Ability, activation_event: ActivationEvent)
## Emitted when an ability is granted
signal ability_granted(ability: Ability)
## Emitted when an ability is revoked
signal ability_revoked(ability: Ability)
## Emitted when the node is activated or disabled
signal activated(active: bool)
## Emitted when an ability cooldown ended
signal cooldown_ended(ability: Ability)
## Emitted when an ability cooldown started
signal cooldown_started(ability: Ability)
## Emitted when tags are updated
signal tags_updated(updated_tags: Array[String], previous_tags: Array[String])


@export_category("Abilities")
## It's the path to the [GameplayAttributeMap] which holds all character attributes
@export_node_path("GameplayAttributeMap") var gameplay_attribute_map_path = NodePath()
## It's a preset of [Ability] resources. [Ability] can be also granted at runtime using [method AbilityContainer.grant]
@export var abilities: Array[Ability] = []
## If set to [code]false[/code], you will not be able to add/end/grant/revoke abilities. 
## [br]Ideal to set a character to a dead state.
@export var active := true:
	get:
		return active
	set(value):
		active = value
		
		if not active:
			cancel_many()
			stop_many_cooldowns()
		
		activated.emit(value)
## It's a preset of tags. Tags can be granted/removed at runtime and can affect the lifetime of an [Ability]
@export var tags: Array[String] = []

## It's a dictionary of cooldowns. Keys are [Ability] resources, while values are [Timer] nodes.
var cooldowns: Dictionary = {}
## It's the related [GameplayAttributeMap] as specified by [member AbilityContainer.gameplay_attribute_map_path]
var gameplay_attribute_map: GameplayAttributeMap
## It's a dictionary of granted abilities.
var granted_abilities: Array[Ability] = []


## Creates a cooldown [Timer] for an [Ability].
## [br]It's called internally by the current [AbilityContainer], so you should not call it.
func _create_cooldown(ability: Ability) -> void:
	if not _has_cooldown(ability):
		var timer = Timer.new()

		timer.one_shot = !ability.cooldown_continuos
		timer.wait_time = ability.cooldown_duration

		cooldowns[ability] = timer

		timer.stop()
		timer.timeout.connect(func ():
			_handle_lifecycle_tagging(LifeCycle.CooldownEnded, ability)
			
			if timer.one_shot:
				ability.end_ability(ActivationEvent.new(self))
			else:
				activate_one(ability)
				
			cooldown_ended.emit(ability)
		)

		add_child(timer)


## Gets a cooldown [Timer] for an [Ability]
## [br]It's called internally by the current [AbilityContainer], so you should not call it.
func _get_cooldown_timer(ability: Ability) -> Timer:
	if _has_cooldown(ability):
		return cooldowns.get(ability)
	return null


## Handles the [signal Ability.activated] signal
## [br]It's called internally by the current [AbilityContainer], so you should not call it.
func _handle_ability_activated(ability: Ability, activation_event: ActivationEvent) -> void:
	if not _is_eligible_for_operation(activation_event):
		return

	_handle_lifecycle_tagging(LifeCycle.Activated, ability)

	if _has_cooldown(ability):
		var timer = _get_cooldown_timer(ability)
		
		if timer.is_stopped():
			_handle_lifecycle_tagging(LifeCycle.CooldownStarted, ability)
			cooldown_started.emit(ability)
			ability_activated.emit(ability, activation_event)
			timer.start()
	else:
		ability_activated.emit(ability, activation_event)

		if ability.can_end(activation_event):
			ability.end_ability(activation_event)


## Handles the [signal Ability.blocked] signal.
## [br]It's called internally by the current [AbilityContainer], so you should not call it.
func _handle_ability_blocked(ability: Ability, activation_event: ActivationEvent) -> void:
	if not _is_eligible_for_operation(activation_event):
		return
		
	ability_blocked.emit(ability, activation_event)
	_handle_lifecycle_tagging(LifeCycle.Blocked, ability)


## Handles the [signal Ability.cancelled] signal
## [br]It's called internally by the current [AbilityContainer], so you should not call it.
func _handle_ability_cancelled(ability: Ability, activation_event: ActivationEvent) -> void:
	if not _is_eligible_for_operation(activation_event):
		return
	
	_handle_lifecycle_tagging(LifeCycle.Cancelled, ability)
	stop_cooldown(ability)
	ability_cancelled.emit(ability, activation_event)


## Handles the [signal Ability.ended] signal
## [br]It's called internally by the current [AbilityContainer], so you should not call it.
func _handle_ability_ended(ability: Ability, activation_event: ActivationEvent) -> void:
	if not _is_eligible_for_operation(activation_event):
		return
	
	_handle_lifecycle_tagging(LifeCycle.Ended, ability)
	stop_cooldown(ability)
	ability_ended.emit(ability, activation_event)


## Returns [code]true[/code] if an [Ability] has created a cooldown [Timer], [code]false[/code] otherwise
## [br]It's called internally by the current [AbilityContainer], so you should not call it.
func _has_cooldown(ability: Ability) -> bool:
	return cooldowns.has(ability)


## Handles tags addition/removal based on current lifecycle state
## [br]It's called internally by the current [AbilityContainer], so you should not call it.
func _handle_lifecycle_tagging(lifecycle: LifeCycle, ability: Ability) -> void:
	match lifecycle:
		LifeCycle.Activated:
			add_tags(ability.tags_activation)
			remove_tags(ability.tags_to_remove_on_activation)
			return
		LifeCycle.Blocked:
			remove_tags(ability.tags_to_remove_on_block)
			return
		LifeCycle.Cancelled:
			remove_tags(ability.tags_to_remove_on_cancellation)
			return
		LifeCycle.Ended:
			remove_tags(ability.tags_to_remove_on_end)
			return
		LifeCycle.CooldownStarted:
			add_tags(ability.tags_cooldown_start)
			remove_tags(ability.tags_to_remove_on_cooldown_start)
			return
		LifeCycle.CooldownEnded:
			add_tags(ability.tags_cooldown_end)
			remove_tags(ability.tags_to_remove_on_cooldown_end)
			return


## Returns [code]true[/code] if the [AbilityContainer] can process and [ActivationEvent], [code]false[/code] otherwise.
func _is_eligible_for_operation(activation_event: ActivationEvent) -> bool:
	return activation_event.ability_container == self and active


## The [method Node._ready] override
func _ready() -> void:
	gameplay_attribute_map = get_node(gameplay_attribute_map_path)
	grant_all_abilities()


## Activates a single [Ability] calling [method Ability.try_activate].
func activate_one(ability: Ability) -> void:
	if not active:
		return

	if granted_abilities.has(ability):
		ability.try_activate(ActivationEvent.new(self))


## Activates many [Ability] resources by tags calling [method Ability.try_activate]
## [br]If parallel_execution is [code]true[/code], then the event passed is generated once for all abilities
## otherwise the event will be regenerated for each iteration
func activate_many(parallel_execution: bool = false) -> void:
	if not active:
		return
		
	if parallel_execution:
		var activation_event = ActivationEvent.new(self)

		for x in granted_abilities:
			x.try_activate(activation_event)
	else:
		for x in granted_abilities:
			x.try_activate(ActivationEvent.new(self))


## Adds a tag to an [AbilityContainer] avoiding duplicates
func add_tag(tag: String, skip_emitting = false) -> void:
	if not tags.has(tag):
		var previous_tags: Array[String] = tags.duplicate()
		tags.append(tag)
		tags_updated.emit(tags, previous_tags)


## Adds many tags to an [AbilityContainer]
func add_tags(tags: Array[String]) -> void:
	var previous_tags: Array[String]

	for t in tags:
		if not self.tags.has(t):
			if previous_tags == null:
				previous_tags = tags.duplicate()
			
			add_tag(t)
		
	tags_updated.emit(tags, previous_tags)


## Checks if the [Ability] can be granted
func can_grant(ability: Ability) -> bool:
	if not active:
		return false
	
	if ability.grant_tags_required.size() > 0:
		if ability.has_all_tags(ability.grant_tags_required, self.tags):
			return !granted_abilities.has(ability)
		else:
			return false
	
	return !granted_abilities.has(ability)


## Checks if the [Ability] can be revoked
func can_revoke(ability: Ability) -> bool:
	if not active:
		return false
	
	return granted_abilities.has(ability) and ability.can_end(ActivationEvent.new(self))


## Cancels one [Ability] using [method Ability.can_cancel]
func cancel_one(ability: Ability) -> void:
	if not active:
		return
	
	var activation_event = ActivationEvent.new(self)

	if ability.can_cancel(activation_event):
		stop_cooldown(ability)
		ability.cancel(activation_event)


## Cancels many [Ability].
func cancel_many() -> void:
	if not active:
		return
	
	var activation_event = ActivationEvent.new(self)

	for a in granted_abilities:
		if a.can_cancel(activation_event):
			stop_cooldown(a)
			a.cancel(activation_event)


## Ends an ability if possible.
func end_one(ability: Ability) -> void:
	if not active:
		return
	
	var activation_event = ActivationEvent.new(self)

	if granted_abilities.has(ability):
		if ability.can_end(activation_event):
			stop_cooldown(ability)
			ability.end_ability(activation_event)
		

## Ends many abilities if possible.
func end_many() -> void:
	if not active:
		return
	
	var activation_event = ActivationEvent.new(self)
	
	for a in granted_abilities:
		if a.can_end(activation_event):
			stop_cooldown(a)
			a.end_ability(activation_event)


## Finds the first [Ability] which matches the [Callable] predicate. Returns [code]null[/code] otherwise.
func find_by(predicate: Callable, includes_ungranted = false) -> Ability:
	if includes_ungranted:
		for a in abilities:
			if predicate.call(a):
				return a
	for a in granted_abilities:
		if predicate.call(a):
			return a
	return null
	

## Returns a filtered array of [Ability] which satisfy the [Callable] predicate.
func filter_abilities(predicate: Callable, includes_ungranted = false) -> Array[Ability]:
	var out: Array[Ability] = []
	
	if includes_ungranted:
		for a in abilities:
			if predicate.call(a):
				out.append(a)
	for a in granted_abilities:
		if predicate.call(a):
			out.append(a)
	
	return out


## Gives an [Ability] at runtime
## If the [Ability] has already been granted, it will be ignored silently
## [br]Returns [code]true[/code] if the ability has been granted, [code]false[/code] otherwise
func grant(ability: Ability) -> bool:
	# It's not active, maybe the owner is dead or on holiday
	if not active:
		return false
	
	# Obviously skip granting if ability is null
	if ability == null:
		return false
	
	# Skips if cannot be granted
	if not can_grant(ability):
		return false

	# Removes from abilities array if it's there. This avoids duplication which could lead to bugs.
	var ability_index = abilities.find(ability)

	if ability_index >= 0:
		abilities.remove_at(ability_index)

	# Appends to abilities array
	granted_abilities.append(ability)

	# Connecting signals (unless they are already connected)
	if not ability.activated.is_connected(_handle_ability_activated):
		ability.activated.connect(_handle_ability_activated)
	if not ability.blocked.is_connected(_handle_ability_blocked):
		ability.blocked.connect(_handle_ability_blocked)
	if not ability.cancelled.is_connected(_handle_ability_cancelled):
		ability.cancelled.connect(_handle_ability_cancelled)
	if not ability.ended.is_connected(_handle_ability_ended):
		ability.ended.connect(_handle_ability_ended)

	# Creating cooldown if needed
	if ability.has_cooldown:
		_create_cooldown(ability)

	# Granting tags if any
	if ability.grant_tags:
		add_tags(ability.grant_tags)

	# Emits grant signal, so UI/parent nodes can do stuff with it
	ability_granted.emit(ability)

	# Returns true, so the caller knows the ability has been granted
	return true


## Grants many [Ability] at runtime
## If an [Ability] is granted, it is removed from the [member AbilityContainer.abilities] array and added to the [member AbilityContainer.granted_abilities] array.
## If an [Ability] has already been granted, it will be ignored silently
## [br]Returns [code]int[/code] the number of abilities granted
func grant_all_abilities() -> int:
	var granted = 0
	var cursor = -1

	for i in abilities.size():
		var ability = abilities[cursor]

		if grant(ability):
			granted += 1
		else:
			cursor -= 1

	return granted


## Returns [code]true[/code] if has an [Ability] which satisfies the [Callable] predicate, [code]false[/code] otherwise
func has_ability(predicate: Callable, includes_ungranted = false) -> bool:
	return find_by(predicate, includes_ungranted) != null


## Returns [code]true[/code] if the tag is contained in the tags of the specified [Ability] in the [AbilityContainer], [code]false[/code] otherwise.
func has_tag(tag: String) -> bool:
	return tags.has(tag)


## Removes a single tag
func remove_tag(tag: String) -> void:
	var index = tags.find(tag)
	
	if index >= 0:
		var previous_tags = tags.duplicate()
		tags.remove_at(index)
		tags_updated.emit(tags, previous_tags)


## Removes many tags
func remove_tags(tags_to_remove: Array[String]) -> void:
	if tags_to_remove.size() == 0:
		return

	var previous_tags = tags.duplicate()
	
	for t in tags_to_remove:
		var index = tags.find(t)
		
		if index >= 0:
			tags.remove_at(index)

	tags_updated.emit(tags, previous_tags)


## End an [Ability] and then removes from the [member AbilityContainer.granted_abilities] array and emits [signal AbilityContainer.ability_revoked].
func revoke(ability: Ability, removes_completely: bool = false) -> void:
	if not active:
		return
	
	if not can_revoke(ability):
		return
	
	var index = granted_abilities.find(ability)
	var activation_event = ActivationEvent.new(self)

	if ability.can_end(activation_event):
		ability.end_ability(activation_event)
		
		if _has_cooldown(ability):
			cooldowns[ability].queue_free()
			cooldowns.erase(ability)

		if index >= 0:
			granted_abilities.remove_at(index)
			ability_revoked.emit(ability)

			if not removes_completely and not abilities.has(ability):
				abilities.append(ability)


## Stops an ability cooldown
func stop_cooldown(ability: Ability) -> void:
	if _has_cooldown(ability):
		_get_cooldown_timer(ability).stop()


## Stops all cooldowns at once
func stop_many_cooldowns() -> void:
	for cooldown in cooldowns.values():
		cooldown.stop()
