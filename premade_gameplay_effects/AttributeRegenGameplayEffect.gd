tool
extends TimedGameplayEffect
class_name AttributeRegenGameplayEffect

export(String) var attribute_name = ""
export(float) var increment_per_second = 0


func _ready():
	duration = 0
	activation_trigger = EffectActivationEvent.ImmediateActivation


func apply_effect() -> void:
	var parent: GameplayAttributeMap = get_parent_attribute_map()
	
	if parent:
		var attribute: GameplayAttribute = parent.get_attribute(attribute_name)
		if attribute and attribute.current_value < attribute.max_value and attribute.name == attribute_name:
			attribute.current_value = clamp(attribute.current_value + increment_per_second, 0, attribute.max_value)
			emit_signal("effect_applied", self)
