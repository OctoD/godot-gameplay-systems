extends Node
class_name GameplayEffect

##
##

enum ActivationEvent {
	NONE = 0,
	ON_ENTER_TREE = 1,
	ON_ATTRIBUTE_CHANGE = 2,
}


signal effect_activated(effect: GameplayEffect)
signal effect_deactivated(effect: GameplayEffect)

## the activation event which triggers the effect
## 
## [br] [b]None[/b] is ideal for a programmatic activation
## [br] [b]On enter tree[/b] triggered when [member GameplayAttributeMap.add_effect] is called or when the effect is added to a [GameplayAttributeMap] as a child
## [br] [b]On attribute change[/b] triggered when the [member GameplayEffect.attribute_name] attribute changes
@export var activation_event: ActivationEvent
## If set to [b]true[/b] the effect will call [method queue_free] on deactivation
@export var instant := true
## If set to [b]true[/b], the modified attributes will be applied with a random range from minimum to maximum value, otherwise will use default_value
@export var apply_as_range := false
## An array of modified gameplay attributes
@export var modified_attributes: Array[Resource] = []

var is_paused := false


func _handle_attribute_changed(name: String, _value: float, _oldvalue: float) -> void:
	for attr in modified_attributes:
		if attr is GameplayAttributeResource:
			if name == attr.attribute_name:
				apply(ActivationEvent.ON_ATTRIBUTE_CHANGE)


func _enter_tree():
	var gameplay_attribute_map = get_gameplay_attribute_map()
	if gameplay_attribute_map:
		apply(ActivationEvent.ON_ENTER_TREE)
		

func _exit_tree():
	var gameplay_attribute_map = get_gameplay_attribute_map()

	if gameplay_attribute_map and gameplay_attribute_map.attribute_changed.is_connected(_handle_attribute_changed):
		gameplay_attribute_map.attribute_changed.disconnect(_handle_attribute_changed)


func _ready():
	if owner:
		await owner.ready
	var gameplay_attribute_map = get_gameplay_attribute_map()
	
	if gameplay_attribute_map:
		gameplay_attribute_map.attribute_changed.connect(_handle_attribute_changed)

## Activates the effect
func activate() -> void:
	if not is_paused:
		effect_activated.emit(self)

## Applies an effect given a specific condition
func apply(condition: ActivationEvent):
	if is_paused:
		return
	
	if should_activate(condition):
		activate()
		
		if should_deactivate():
			deactivate()

## Deactivates the effect.
## 
## If the effect is [member GameplayEffect.instant], the effect will call [method Node.queue_free]
func deactivate() -> void:
	effect_deactivated.emit(self)
	
	if instant:
		queue_free()


func get_gameplay_attribute_map(prev_node: Node = self) -> Node:
	var parent = prev_node.get_parent()

	if parent:
		if parent.has_meta("gameplay_attribute_map"): 
			return parent
		return get_gameplay_attribute_map(parent)
	
	return null


func pause() -> void:
	is_paused = true
	
	
func resume() -> void:
	is_paused = false


func should_activate(condition: ActivationEvent) -> bool:
	return activation_event == condition


func should_deactivate() -> bool:
	return true
