class_name AttributeEffectCondition extends Resource


## Calls it's own method when the bound attribute should change
## 
## If the condition expressed is met, then the effect can be applied
## This kind of resource is very useful to stop infinite time-based effects


## Returns [code]true[/code] if the effect should continue to be applied, [code]false[/code] otherwise
func should_apply(
	attribute_effect: AttributeEffect,
	gameplay_effect: GameplayEffect,
	gameplay_attribute_map: GameplayAttributeMap
) -> bool:
	return true
