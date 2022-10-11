extends Node
class_name GameplayAttributeMap


signal attribute_changed(name: String, value: float, previous_value: float)
signal effect_added(effect: GameplayEffect)
signal effect_applied(effect: GameplayEffect)
signal setup_finished(map: GameplayAttributeMap)

@export_category("Gameplay attributes map")
@export_node_path(Node2D, Node3D) var owning_character_path := NodePath()
@export var attributes: Array[Resource]


var _effects_paused = false


var owning_character: 
	get:
		return find_child(owning_character_path)


func _ready():
	if owner:
		await owner.ready
	set_meta("gameplay_attribute_map", "true")
	
	for attribute in attributes:
		add_child(attribute.to_attribute())
	
	for attribute in get_attributes():
		if not attribute.attribute_changed.is_connected(_handle_attribute_changed):
			attribute.attribute_changed.connect(_handle_attribute_changed)
		
	for effect in get_effects():
		effect.effect_activated.connect(_handle_effect_applied)

	child_entered_tree.connect(_handle_child_entered)
	child_exiting_tree.connect(_handle_child_exiting)
	tree_exiting.connect(_handle_tree_exiting)
	setup_finished.emit(self)
	

func _handle_attribute_changed(name: String, value: float, previous_value: float):
	attribute_changed.emit(name, value, previous_value)

	for effect in get_effects():
		if effect.attribute_name == name: 
			effect.apply(GameplayEffect.ActivationEvent.ON_ATTRIBUTE_CHANGE)


func _handle_child_entered(child: Node):
	if child is GameplayAttribute:
		child.attribute_changed.connect(_handle_attribute_changed)

	if child is GameplayEffect:
		child.effect_activated.connect(_handle_effect_applied)
		child.apply(child.ActivationEvent.ON_ENTER_TREE)
		effect_added.emit(child)


func _handle_child_exiting(child: Node):
	if child is GameplayAttribute:
		child.attribute_changed.disconnect(_handle_attribute_changed)
		
	if child is GameplayEffect:
		child.effect_activated.disconnect(_handle_effect_applied)


func _handle_effect_applied(activated_effect: GameplayEffect):
	for modified_effect in activated_effect.modified_attributes:
		if modified_effect is GameplayAttributeResource:
			var attr = find_attribute(modified_effect.attribute_name)
			
			if attr:
				if activated_effect.apply_as_range:
					attr.current_value += randf_range(modified_effect.minimum_value, modified_effect.maximum_value)
				else:
					attr.current_value += modified_effect.default_value
			
	if not activated_effect.is_paused:
		effect_applied.emit(activated_effect)


func _handle_tree_exiting():
	pass


func add_effect(effect: GameplayEffect) -> void:
	if effect:
		if effect.owner:
			effect.owner.remove_child(effect)
		add_child(effect)


func find_attribute(path: NodePath) -> GameplayAttribute:
	return get_node(path) as GameplayAttribute


func find_effect(path: NodePath) -> GameplayEffect:
	return get_node(path) as GameplayEffect


func get_attributes() -> Array[GameplayAttribute]:
	var children = [] as Array[GameplayAttribute]
	
	for child in get_children():
		if child is GameplayAttribute:
			children.append(child)

	return children


func get_effects() -> Array[GameplayEffect]:
	var children = [] as Array[GameplayEffect]
	
	for child in get_children():
		if child is GameplayEffect:
			children.append(child)
	
	return children


func pause_effects() -> void:
	if _effects_paused:
		return
	
	_effects_paused = true
	for effect in get_effects():
		effect.pause()


func resume_effects() -> void:
	if not _effects_paused:
		return
	
	_effects_paused = false
	for effect in get_effects():
		effect.resume()
	
