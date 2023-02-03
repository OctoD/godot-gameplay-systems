class_name StopEffectIf0 extends AttributeEffectCondition


func should_apply(attribute_effect: AttributeEffect, effect: GameplayEffect, gameplay_attributes: GameplayAttributeMap) -> bool:
	var attribute = gameplay_attributes.get_attribute_by_name(attribute_effect.attribute_name)

	if attribute:
		return attribute.current_value > 0

	return false
