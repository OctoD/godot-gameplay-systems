tool
extends TimedGameplayEffect
class_name AttributeConsumeGameplayEffect

export(String) var attribute_name = ""
export(float) var consume_per_second = 1 setget set_consume_per_second, get_consume_per_second


func _ready():
	duration = 0
	activation_trigger = EffectActivationEvent.ImmediateActivation


func set_consume_per_second(value: float) -> void:
	consume_per_second = abs(value)


func get_consume_per_second() -> float:
	return consume_per_second


func apply_effect() -> void:
	var parent: GameplayAttributeMap = get_parent_attribute_map()
	
	if parent:
		var attribute: GameplayAttribute = parent.get_attribute(attribute_name)
		if attribute and attribute.name == attribute_name:
			attribute.current_value = clamp(attribute.current_value - abs(consume_per_second), 0, attribute.max_value)
			emit_signal("effect_applied", self)
