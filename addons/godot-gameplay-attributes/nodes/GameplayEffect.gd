extends Node
class_name GameplayEffect

enum EffectActivationEvent {
	AttributeChanged,
	AddedToAttributeMap,
	ImmediateActivation,
}


export(EffectActivationEvent) var activation_trigger = EffectActivationEvent.ImmediateActivation


signal effect_activated(effect)
signal effect_applied(effect)
signal effect_deactivated(effect)


func _ready():
	if not Engine.editor_hint:
		setup_effect()
		if should_activate(EffectActivationEvent.ImmediateActivation):
			apply_effect()

			if should_deactivate():
				queue_free()


func play_effect() -> void:
	pass


func pause_effect() -> void:
	pass


func setup_effect() -> void:
	_connect_to_parent_signal()


func apply_effect() -> void:
	pass


func _connect_to_parent_signal() -> void:
	var parent = get_parent()

	if parent.has_signal("attribute_changed"):
		parent.connect("attribute_changed", self, "_on_attribute_changed")


func get_effect_owner():
	var parent = get_parent_attribute_map()

	if parent:
		return parent.get_parent()


# deprecated, use get_effect_owner and cast properly instead
func get_kinematic_owner():
	var parent = get_parent_attribute_map()

	if parent:
		return parent.get_parent()


func get_parent_attribute_map():
	return get_parent()


func _on_attribute_changed(attribute: Dictionary) -> void:
	if should_activate(EffectActivationEvent.AttributeChanged):
		apply_effect();

		if should_deactivate():
			queue_free()


func should_activate(activation_event: int) -> bool:
	return activation_trigger == activation_event


func should_deactivate() -> bool:
	return true


func _get_configuration_warning():
	if get_parent().has_signal("attribute_changed"):
		return ""

	return "GameplayAttribute must be a direct child of a GameplayAttributeMap node."

