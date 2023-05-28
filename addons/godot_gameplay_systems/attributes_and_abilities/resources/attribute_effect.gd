@icon("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/AttributeEffect.svg")

class_name AttributeEffect extends Resource

## An AttributeEffect is a resource which stores all effects mutation informations
## 
## It is consumed once by a GameplayAttributeMap if it's lifetime is "oneshot", otherwise
## it will be consumed each [member AttributeEffect.apply_every_second] seconds for a maximum of [member AttributeEffect.max_applications] times


enum {
	## The effect will be applied once
	LIFETIME_ONE_SHOT = 0,
	## The effect will be applied each tot seconds
	LIFETIME_TIME_BASED = 1,
}

@export_category("Effect life-time")
## The attribute effect life-time:[br]
## LIFETIME_ONE_SHOT [b]0[/b] is equal to a oneshot effect, aka applied once.[br]
## LIFETIME_TIME_BASED [b]1[/b] is equal to a time-based effect, applied each [member AttributeEffect.apply_every_second] seconds for a maximum of [member AttributeEffect.max_applications] times
@export_enum("One-Shot", "Time-Based") var life_time = 0:
	get:
		return life_time
	set(value):
		life_time = value
		emit_changed()
## If [member life_time] is [b]1[/b], then the effect is applied each seconds as specified by this parameter
@export var apply_every_second := 1.0:
	get:
		return apply_every_second
	set(value):
		apply_every_second = value
		emit_changed()
## If [member life_time] is [b]1[/b], then the effect is applied each seconds as specified by [member apply_every_second] for a maximum of times specified by this parameter
@export var max_applications := 1:
	get:
		return max_applications
	set(value):
		max_applications = value
		emit_changed()

@export_category("Attribute modifier")
@export_enum("Value modification", "Value buff") var applies_as = 0:
	get:
		return applies_as
	set(value):
		applies_as = value
		emit_changed()
## The attribute name to mutate
@export var attribute_name := "":
	get:
		return attribute_name
	set(value):
		attribute_name = value
		emit_changed()
## The minimum value. 
## [br]Can be negative
@export var minimum_value := 0.0:
	get:
		return minimum_value
	set(value):
		minimum_value = value
		emit_changed()
## The minimum value. 
## [br]Can be negative
@export var maximum_value := 0.0:
	get:
		return maximum_value
	set(value):
		maximum_value = value
		emit_changed()
@export_group("Pipeline")
## If it is set, it will call [method AttributeEffectCondition.should_apply]
@export var condition: Resource = null:
	get:
		return condition
	set(value):
		condition = value
		emit_changed()


## Gets the computed current value.[br]
##
## If both [member minimum_value] and [member maximum_value] are different from [code]0.0[/code] the resulting [code]float[/code] is a value between
## [br] - [member minimum_value] and [member maximum_value] if minimum_value is less than maximum
## [br] - [member maximum_value] and [member minimum_value] if minimum_value is greater than maximum
func get_current_value() -> float:
	if minimum_value < maximum_value:
		return randf_range(minimum_value, maximum_value)
	elif minimum_value > maximum_value:
		return randf_range(maximum_value, minimum_value)
	else:
		return minimum_value


## Checks if the current attribute effect can be applied
func should_apply(gameplay_effect: GameplayEffect, gameplay_attribute_map: GameplayAttributeMap) -> bool:
	if condition == null:
		return true
	
	if condition.has_method("should_apply"):
		return condition.should_apply(self, gameplay_effect, gameplay_attribute_map)

	printerr("condition has not a method should_apply(attribute_effect: AttributeEffect, effect: GameplayEffect, gameplay_attributes: GameplayAttributeMap) -> bool")
	
	return true
