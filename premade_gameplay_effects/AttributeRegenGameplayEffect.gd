tool
extends TimedGameplayEffect
class_name AttributeRegenGameplayEffect

export(String) var attribute_name = ""
export(int) var duration = 0
export(float) var increment_per_second = 0


func apply_effect(attribute: GameplayAttribute) -> void:
	if attribute.current_value < attribute.max_value and attribute.name == attribute_name:
		attribute.current_value = clamp(attribute.current_value + increment_per_second, 0, attribute.max_value)

