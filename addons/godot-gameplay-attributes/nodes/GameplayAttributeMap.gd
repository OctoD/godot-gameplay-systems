tool
extends Node
class_name GameplayAttributeMap


signal attribute_changed(attribute)
signal effect_activated(effect)
signal effect_applied(effect)
signal effect_deactivated(effect)

var _is_valid = false


func _ready():
	if _is_valid or not Engine.editor_hint:
		connect_child_signals()


func apply_effect(effect: GameplayEffect) -> void:
	add_child(effect)

	if effect.should_activate(GameplayEffect.EffectActivationEvent.AddedToAttributeMap):
		effect.apply_effect()

		if effect.should_deactivate():
			effect.queue_free()


func connect_child_signals() -> void:
	if not Engine.editor_hint:
		for child in get_children():
			if child.has_signal("attribute_changed"):
				child.connect("attribute_changed", self, "_on_attribute_changed")
			if child.has_signal("effect_activated"):
				child.connect("effect_activated", self, "_on_effect_activated")
			if child.has_signal("effect_applied"):
				child.connect("effect_applied", self, "_on_effect_applied")
			if child.has_signal("effect_deactivated"):
				child.connect("effect_deactivated", self, "_on_effect_deactivated")


func get_attribute(attribute_name: String) -> GameplayAttribute:
	var found: GameplayAttribute = find_node(attribute_name)
	return found


func get_attribute_value(attribute_name: String) -> float:
	var attribute = get_attribute(attribute_name)

	if attribute:
		return attribute.current_value
	else:
		return 0.0


func get_attribute_max_value(attribute_name: String) -> float:
	var attribute = get_attribute(attribute_name)

	if attribute:
		return attribute.max_value
	else:
		return 0.0
		

func get_gameplay_effect(effect_name: String) -> GameplayEffect:
	return find_node(effect_name) as GameplayEffect

	
func get_attributes() -> Array:
	var attributes = []
	
	for child in get_children():
		if child is GameplayAttribute:
			attributes.append(child)
		
	return attributes


func get_effects() -> Array:
	var effects = []
	
	for child in get_children():
		if child is GameplayEffect:
			effects.append(child)
		
	return effects


func _on_attribute_changed(attribute: Dictionary) -> void:
	emit_signal("attribute_changed", attribute)


func _on_effect_activated(effect: GameplayEffect) -> void:
	emit_signal("effect_activated", effect)


func _on_effect_applied(effect: GameplayEffect) -> void:
	emit_signal("effect_applied", effect)


func _on_effect_deactivated(effect: GameplayEffect) -> void:
	emit_signal("effect_deactivated", effect)


func play_effect(effect_name: String) -> bool:
	for effect in get_effects():
		if effect.name == effect_name:
			effect.play_effect()
			return true

	return false
		


func pause_effect(effect_name: String) -> bool:
	for effect in get_effects():
		if effect.name == effect_name:
			effect.pause_effect()
			return true

	return false


func _get_configuration_warning():
	var children = get_children()
	var message = "Requires at least on GameplayAttribute node"
	var parent = get_parent()
	var is_editing = Engine.editor_hint
	
	if children.size() == 0:
		_is_valid = false
		return message
	
	var gameplay_attributes_count = 0
	
	for child in children:
		if child.has_signal("attribute_changed"):
			gameplay_attributes_count += 1

	if gameplay_attributes_count == 0:
		_is_valid = false
		return message
	
	_is_valid = true
	
	return ""
