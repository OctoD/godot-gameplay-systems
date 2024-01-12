extends Control

@onready var attribute_container: AttributeContainer = $AttributeContainer
@onready var label_2: Label = $Label2

class BuffDex extends AttributeEffect:
	func _init() -> void:
		affected_amount = 10
		application_type = AttributeEffect.ADD_BUFF
		affected_attribute = "attributes.dexterity"


class BuffStr extends AttributeEffect:
	func _init() -> void:
		affected_amount = 5
		application_type = AttributeEffect.ADD_BUFF
		affected_attribute = "attributes.strength"


class SpeedDecrease extends AttributeEffect:
	func _init() -> void:
		affected_amount = 1
		application_type = AttributeEffect.SUBTRACT_VALUE
		affected_attribute = "attributes.speed"


class SpeedIncrease extends AttributeEffect:
	func _init() -> void:
		affected_amount = 5
		application_type = AttributeEffect.ADD_BUFF
		affected_attribute = "attributes.speed"


class StaminaDecrease extends AttributeEffect:
	func _init() -> void:
		affected_amount = 5
		application_type = AttributeEffect.SUBTRACT_VALUE
		affected_attribute = "attributes.stamina"


class StaminaIncrease extends AttributeEffect:
	func _init() -> void:
		affected_amount = 5
		application_type = AttributeEffect.ADD_VALUE_OR_BUFF
		affected_attribute = "attributes.stamina"
		
		
class DebuffCondition extends AttributeEffectCondition:
	func get_break_type(attribute_effect: AttributeEffect, attribute_container: AttributeContainer) -> AttributeEffectCondition.BreakType:
		# if the effect lasted for more than 2 seconds, we will start to debuff it
		if attribute_container.count_timeouts(attribute_effect) > 2:
			if (attribute_container.get_attribute(attribute_effect.affected_attribute).buff > 0):
				return AttributeEffectCondition.NO_BREAK

		return AttributeEffectCondition.BREAK_RESET_COUNTER


class DebuffDex extends AttributeEffect:
	func _init() -> void:
		affected_amount = 5
		application_type = AttributeEffect.SUBTRACT_BUFF
		affected_attribute = "attributes.dexterity"
		life_cycle = AttributeEffect.INFINITE_TIME_BASED
		conditions.append(DebuffCondition.new())


class DebuffStr extends AttributeEffect:
	func _init() -> void:
		application_type = AttributeEffect.SUBTRACT_BUFF
		affected_attribute = "attributes.strength"
		life_cycle = AttributeEffect.INFINITE_TIME_BASED
		conditions.append(DebuffCondition.new())
	
	func calculate_affected_amount(container: AttributeContainer) -> float:
		var attribute = container.get_attribute(affected_attribute)
		
		if attribute != null:
			## loses 5% each second
			var value_to_debuff = (attribute.value / 100) * 5
			
			if value_to_debuff > 0:
				return value_to_debuff
			else:
				return 1.0
		
		return affected_amount


func make_gameplay_effect(attribute_effect: AttributeEffect) -> GameplayEffect:
	var x = GameplayEffect.new()

	if (attribute_effect != null):
		x.attribute_effects_applied.append(attribute_effect)
	
	return x


func _handle_attribute_changed(attribute: Attribute) -> void:
	print(attribute.tag_name + " has changed")
	print_label()


func _ready() -> void:
	print_label()
	add_child((make_gameplay_effect(DebuffDex.new())))
	add_child((make_gameplay_effect(DebuffStr.new())))
	attribute_container.attribute_changed.connect(_handle_attribute_changed)


func _input(event: InputEvent) -> void:
	if event is InputEventKey and event.is_pressed():
		var k = event.as_text_keycode()
		
		if k == "1":
			add_child(make_gameplay_effect(SpeedIncrease.new()))
		elif k == "2":
			add_child(make_gameplay_effect(SpeedDecrease.new()))
		elif k == "Q":
			add_child(make_gameplay_effect(StaminaIncrease.new()))
		elif k == "W":
			add_child(make_gameplay_effect(StaminaDecrease.new()))
		elif k == "0":
			add_child(make_gameplay_effect(BuffDex.new()))
			add_child(make_gameplay_effect(BuffStr.new()))
		
		print_label()


func print_attribute(attribute: Attribute) -> String:
	if (attribute == null):
		return ""
	
	return "tag_name: {0}; value: {1}; maximum_value: {2}; buff: {3};".format({
		0: attribute.tag_name,
		1: int(attribute.value),
		2: int(attribute.max_value),
		3: int(attribute.buff)
	})


func print_label() -> void:
	label_2.text = """ 
		{0}
		{1}
		{2}
		{3}
	""".format({
		0: print_attribute(attribute_container.get_attribute("attributes.stamina")),
		1: print_attribute(attribute_container.get_attribute("attributes.speed")),
		2: print_attribute(attribute_container.get_attribute("attributes.dexterity")),
		3: print_attribute(attribute_container.get_attribute("attributes.strength"))
	})
