class_name AttributeSpec extends RefCounted

## Represents an attribute as a class
	
## Emitted when the instance has changed one of it's values
signal changed(current: AttributeSpec)
## Emitted when the instance has changed it's minimum value
signal minimum_value_changed(from: float, to: float)
## Emitted when the instance has changed it's maximum value
signal maximum_value_changed(from: float, to: float)

## used internally to avoid the initial signals propagation 
var __setup := false
## It's the attribute name
var attribute_name := ""
## It's the buff amount
var buffing_value := 0.0
## It's the current attribute's value
var current_value := 0.0:
	get:
		return current_value
	set(value):
		var previous_value = current_value

		if previous_value == value:
			return
		
		if maximum_value > minimum_value:
			current_value = clampf(value, minimum_value, maximum_value)
		elif maximum_value == minimum_value and maximum_value == 0.0:
			current_value = value
		else:
			if maximum_value == 0.0 and minimum_value > 0.0:
				current_value = clampf(value, value + 1, minimum_value)
			else:
				current_value = clampf(value, maximum_value, minimum_value)
		if not __setup:
			changed.emit(self)
## It's the maximum attribute's value. Keep 0 to mark it as infinite
var maximum_value := 0.0:
	get:
		return maximum_value
	set(value):
		var previous_value = maximum_value
		maximum_value = value
		
		if not __setup:
			maximum_value_changed.emit(previous_value, value)
## It's the maximum attribute's value. 
var minimum_value := 0.0:
	get: 
		return minimum_value
	set(value):
		var previous_value = minimum_value
		minimum_value = value
		
		if not __setup:
			minimum_value_changed.emit(previous_value, value)
## The calculated attribute value with the [member AttributeSpec.buffing_value].
var current_buffed_value: float = 0.0:
	get:
		return current_value + buffing_value


func apply_attribute_effect(attribute_effect: AttributeEffect) -> void:
	var value = attribute_effect.get_current_value()
	
	if attribute_effect.applies_as == 1:
		buffing_value += value
	else:
		if buffing_value > 0.0 and value < 0.0:
			var diff = buffing_value + value
			
			buffing_value = clampf(diff, 0, buffing_value)
			current_value += diff
		else:
			current_value += value


## Creates an instance of [AttributeSpec] starting from an [AttributeResource]
static func from_attribute(attribute: AttributeResource) -> AttributeSpec:
	var instance = AttributeSpec.new()
	instance.__setup = true
	instance.attribute_name = attribute.attribute_name
	instance.maximum_value = attribute.maximum_value
	instance.minimum_value = attribute.minimum_value
	instance.current_value = attribute.current_value
	instance.__setup = false
	return instance
