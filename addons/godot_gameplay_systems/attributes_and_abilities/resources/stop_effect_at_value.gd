class_name StopEffectAtValue extends AttributeEffectCondition

@export_category("Rule")
## The value to stop at
@export var value_to_stop_at: float = 0.0
## The value condition
@export_enum("Equal", "Greater than", "Lesser than", "Greater Equal to", "Less Equal To") var operator = 0


func should_apply(attribute_effect: AttributeEffect, effect: GameplayEffect, gameplay_attributes: GameplayAttributeMap) -> bool:
	var attribute = gameplay_attributes.get_attribute_by_name(attribute_effect.attribute_name)

	if attribute == null:
		return false

	match operator:
		0: 	return attribute.current_value == value_to_stop_at
		1:	return attribute.current_value > value_to_stop_at
		2:	return attribute.current_value < value_to_stop_at
		3:	return attribute.current_value >= value_to_stop_at
		3:	return attribute.current_value <= value_to_stop_at


	return false
