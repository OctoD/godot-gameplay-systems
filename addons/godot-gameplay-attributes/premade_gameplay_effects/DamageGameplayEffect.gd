tool
extends GameplayEffect
class_name DamageGameplayEffect

@export var attribute_name: String = ""
@export var damage_min: float = 0
@export var damage_max: float = 0


func _ready():
	activation_trigger = EffectActivationEvent.ImmediateActivation


func should_deactivate() -> bool:
	return true

func apply_effect() -> void:
	var parent  = get_parent_attribute_map() as GameplayAttributeMap
	
	if parent:
		var attribute  = parent.get_attribute(attribute_name) as GameplayAttribute
		if attribute and attribute.name == attribute_name:
			randomize()
			var dmg = (randf() * (damage_max - damage_min)) + damage_min
			attribute.current_value = clamp(attribute.current_value - dmg, 0, attribute.max_value)
			effect_applied.emit(self)
