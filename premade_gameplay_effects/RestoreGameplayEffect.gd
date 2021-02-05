tool
extends GameplayEffect
class_name RestoreGameplayEffect

export(String) var attribute_name
export(float) var value = 0


func _ready():
	activation_trigger = EffectActivationEvent.ImmediateActivation


func should_deactivate() -> bool:
	return true

func apply_effect() -> void:
	var parent: GameplayAttributeMap = get_parent_attribute_map()
	
	if parent:
		var attribute: GameplayAttribute = parent.get_attribute(attribute_name)
		if attribute and attribute.name == attribute_name:
			attribute.current_value = clamp(attribute.current_value + value, 0, attribute.max_value)
			emit_signal("effect_applied", self)
