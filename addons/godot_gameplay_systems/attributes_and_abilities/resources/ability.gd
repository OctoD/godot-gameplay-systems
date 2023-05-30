@icon("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/Ability.svg")
class_name Ability extends Resource

## Represents an ability or skill

## Emitted the the ability has been activated.
signal activated(Ability, ActivationEvent)
## Emitted the the ability has been blocked in [method Ability.try_activate].
signal blocked(Ability, ActivationEvent)
## Emitted the the ability has been cancelled.
signal cancelled(Ability, ActivationEvent)
## Emitted the the ability has been ended.
signal ended(Ability, ActivationEvent)

@export_group("User interface", "ui_")
## Is the icon shown in your user interface.
@export var ui_icon: Texture2D = null
## Is the name shown in your user interface.
@export var ui_name: String = ""

@export_group("Cooldown", "cooldown_")
## Sets a cooldown duration before the ability can be used again.
@export var cooldown_duration := 0.0
## Sets the cooldown as continuos, so it will keep on working every [member Ability.cooldown_duration] seconds.
@export var cooldown_continuos := false

@export_group("Ability Granting", "grant_")
## Automatically grants an ability when added to a [AbilityContainer].
@export var grant_automatic := true
## Adds these tags to the owning [AbilityContainer] when the ability is granted.
## [br]Useful for skill trees or skill progression systems.
@export var grant_tags: Array[String] = []
## Tags required for granting an ability
## [br]These tags will be checked to ensure that the [Ability] can be granted or not.
@export var grant_tags_required: Array[String] = []

@export_group("Tags", "tags_")
## Tags added once ability has been activated.
## [br]Use [member Ability.tags_to_remove_on_activation] to remove some of these tags after the activation.
@export var tags_activation: Array[String] = []
## Tags required for activation. 
## [br]The ability cannot be activated if the [AbilityContainer] does not have all the tags provided here.
@export var tags_activation_required: Array[String] = []
## Blocks execution if ore or more tags are contained by [AbilityContainer]
## [br]Use these tags to block the activation of an ability.
@export var tags_block: Array[String] = []
## Tags required for cancellation.
## [br]Use these tags to determine if an ability can be cancelled or not.
@export var tags_cancellation_required: Array[String] = []
## Tags added when cooldown is started.
## [br]Use [member Ability.tags_to_remove_on_cooldown_start] to remove some tags from this array when a cooldown starts.
@export var tags_cooldown_start: Array[String] = []
## Tags added when cooldown is ended.
## [br]Use [member Ability.tags_to_remove_on_cooldown_end] to remove some tags from this array when a cooldown ends.
@export var tags_cooldown_end: Array[String] = []
## Tags which will block the end of an [Ability].
@export var tags_end_blocking: Array[String] = []
## Tags which will be removed on activation.
@export var tags_to_remove_on_activation: Array[String] = []
## Tags which will be removed on block.
@export var tags_to_remove_on_block: Array[String] = []
## Tags which will be removed on cancellation.
@export var tags_to_remove_on_cancellation: Array[String] = []
## Tags which will be removed when a cooldown start.
@export var tags_to_remove_on_cooldown_start: Array[String] = []
## Tags which will be removed when a cooldown end.
@export var tags_to_remove_on_cooldown_end: Array[String] = []
## Tags which will be removed when an ability ends.
@export var tags_to_remove_on_end: Array[String] = []


## Is [code]true[/code] if [member Ability.cooldown_duration] is greater than [code]0.0[/code], [code]false[/code] otherwise.
var has_cooldown: bool:
	get:
		return cooldown_duration > 0.0


## Activates the effect. This will forcefully activate it even if some criteria do not match.
## You should use [method Ability.try_activate] instead for a proper (and safer) flow.
func activate(activation_event: ActivationEvent) -> void:
	activated.emit(self, activation_event)


## Return [code]true[/code] if the ability can be activated, [code]false[/code] otherwise.
## [br]Always return: [code]true[/code] if [member Ability.tags_activation_required] is empty.
func can_activate(activation_event: ActivationEvent) -> bool:
	if tags_activation_required.size() > 0:
		return has_all_tags(tags_activation_required, activation_event.tags)
	
	return true


## Returns [code]true[/code] if the ability can be blocked, [code]false[/code] otherwise.
## [br]Always return: [code]true[/code] if [member Ability.tags_block] is empty.
func can_block(activation_event: ActivationEvent) -> bool:
	if tags_block.size() > 0:
		return has_some_tags(tags_block, activation_event.tags)

	return false


## Return [code]true[/code] if the ability can be cancelled, [code]false[/code] otherwise.
## [br]Always return: [code]true[/code] if [member Ability.tags_cancellation_required] is empty.
func can_cancel(activation_event: ActivationEvent) -> bool:
	if tags_cancellation_required.size() > 0:
		return has_some_tags(tags_cancellation_required, activation_event.tags)
	
	return false


## Return [code]true[/code] if the ability can be ended, [code]false[/code] otherwise.
## [br]Always return: [code]true[/code] if [member Ability.tags_end_blocking] is empty.
func can_end(activation_event: ActivationEvent) -> bool:
	if tags_end_blocking.size() > 0:
		return !has_some_tags(tags_end_blocking, activation_event.tags)

	return true


## Cancels an ability forcefully. Remember to call [method Ability.can_cancel] first.
## [br]This will forcefully activate it even if some criteria do not match.
## [br]You should use [method Ability.try_activate] instead for a proper (and safer) flow.
func cancel(activation_event: ActivationEvent) -> void:
	if can_cancel(activation_event):
		cancelled.emit(self, activation_event)


## Ends the ability forcefully. Remember to call [method Ability.can_end] first.
## [br]This will forcefully activate it even if some criteria do not match.
## [br]You should use [method Ability.try_activate] instead for a proper (and safer) flow.
func end_ability(activation_event: ActivationEvent) -> void:
	if can_end(activation_event):
		ended.emit(self, activation_event)


## Checks if the parameter [code]tags[/code] has all tags included in [code]tags_to_check[/code].
## [br]It checks if [code]tags[/code] has all [code]tags_to_check[/code].
func has_all_tags(tags: Array[String], tags_to_check: Array[String]) -> bool:
	for t in tags:
		if not tags_to_check.has(t):
			return false

	return true

## Checks if the parameter [code]tags[/code] has some tags included in [code]tags_to_check[/code].
## [br]It checks if [code]tags[/code] has all [code]tags_to_check[/code].
func has_some_tags(tags: Array[String], tags_to_check: Array[String]) -> bool:
	for t in tags:
		if tags_to_check.has(t):
			return true

	return false


## Tries to activate an ability, then tries to cancel it and then tries to end it.
func try_activate(activation_event: ActivationEvent) -> void:
	if can_block(activation_event):
		blocked.emit(self, activation_event)
		return

	if can_activate(activation_event):
		activate(activation_event)
