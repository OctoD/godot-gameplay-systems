@tool
extends TimedGameplayEffect
class_name AttributeRegenGameplayEffect

@export var attribute_name: String = ""
@export var increment_per_second: float = 0


func _ready():
	duration = 0
	activation_trigger = EffectActivationEvent.ImmediateActivation


func apply_effect() -> void:
	var parent  = get_parent_attribute_map() as GameplayAttributeMap
	
	if parent:
		var attribute  = parent.get_attribute(attribute_name) as GameplayAttribute
		if attribute and attribute.current_value < attribute.max_value and attribute.name == attribute_name:
			attribute.current_value = clamp(attribute.current_value + increment_per_second, 0, attribute.max_value)
			effect_applied.emit(self)
