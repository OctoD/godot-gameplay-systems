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
		
class DebuffDex extends AttributeEffect:
	func _init() -> void:
		affected_amount = 1
		application_type = AttributeEffect.SUBTRACT_VALUE
		affected_attribute = "attributes.dexterity"
		life_cycle = AttributeEffect.INFINITE_TIME_BASED
		
	func _are_conditions_met(x, y) -> bool:
		return true


func make_gameplay_effect(attribute_effect: AttributeEffect) -> GameplayEffect:
	var x = GameplayEffect.new()

	if (attribute_effect != null):
		x.attribute_effects_applied.append(attribute_effect)
	
	return x


func _ready() -> void:
	print_label()


func _input(event: InputEvent) -> void:
	if event is InputEventKey and event.is_pressed():
		var k = event.as_text_keycode()
		var m = false
		var x = Node.new()
		
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
	
	return "{0} value: {1}/max: {2}/buff: {3}".format({
		0: attribute.tag_name,
		1: attribute.value,
		2: attribute.max_value,
		3: attribute.buff
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
