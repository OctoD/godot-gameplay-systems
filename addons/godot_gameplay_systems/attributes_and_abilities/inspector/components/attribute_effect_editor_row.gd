@tool
extends GridContainer


signal removed()


@export_category("Effect")
@export var attributes_table: AttributeTable = null:
	get:
		return attributes_table
	set(value):
		attributes_table = value
		_redraw()
@export var attribute_effect: AttributeEffect = null:
	get: 
		return attribute_effect
	set(value):
		attribute_effect = value
		_redraw()

@onready var application_count_spinbox: SpinBox = $VBoxContainer/TimerSetupContainer/ApplicationCountSpinBox
@onready var applies_as: OptionButton = $AppliesAs/OptionButton
@onready var attribute_option_button: OptionButton = $AttributeName/OptionButton
@onready var life_time_option_button: OptionButton = $LifeTime/OptionButton
@onready var minimum_value_spinbox: SpinBox = $MinimumValue/SpinBox
@onready var maximum_value_spinbox: SpinBox = $MaximumValue/SpinBox
@onready var timer_setup_container: VBoxContainer = $VBoxContainer
@onready var timer_spinbox: SpinBox = $VBoxContainer/TimerSetupContainer/TimeoutSpinBox
@onready var remove_button: Button = $AttributeName/RemoveButton


var condition_resource_input := EditorResourcePicker.new()


func _init() -> void:
	pass


func _inherit_from_resource() -> void:
	if attribute_effect != null and attributes_table != null:
		_populate_attribute_name_list()
		_select_attribute_name()
		applies_as.selected = attribute_effect.applies_as
		
		if applies_as.selected < 0:
			applies_as.selected = 0
		
		attribute_option_button.text = attribute_effect.attribute_name
		life_time_option_button.selected = attribute_effect.life_time
		minimum_value_spinbox.value = attribute_effect.minimum_value
		maximum_value_spinbox.value = attribute_effect.maximum_value
		timer_spinbox.value = attribute_effect.apply_every_second
		application_count_spinbox.value = attribute_effect.max_applications
		condition_resource_input.edited_resource = attribute_effect.condition
		_set_lifetime(attribute_effect.life_time)


func _populate_attribute_name_list() -> void:
	if attribute_option_button:
		attribute_option_button.clear()
	
	if attributes_table:
		for attribute in attributes_table.attributes:
			attribute_option_button.add_item(attribute)


func _ready() -> void:
	var condition_label = Label.new()
	
	condition_label.text = "Condition"
	condition_resource_input.base_type = "AttributeEffectCondition"
	
	add_child(condition_label)
	add_child(condition_resource_input)
	
	timer_setup_container.visible = false
	
	applies_as.item_selected.connect(func (index):
		attribute_effect.applies_as = index	
	)
	
	application_count_spinbox.value_changed.connect(func (value):
		attribute_effect.max_applications = value	
	)
	
	attribute_option_button.item_selected.connect(func (index):
		if attributes_table and attribute_effect:
			if attributes_table.attributes.size() > index:
				attribute_effect.attribute_name	= attributes_table.attributes[index]
	)	
	
	condition_resource_input.resource_changed.connect(func (resource):
		if resource:
			attribute_effect.condition = resource
		else:
			attribute_effect.condition = null
	)
	condition_resource_input.resource_selected.connect(func (resource, _i):
		if resource:
			attribute_effect.condition = resource
		else:
			attribute_effect.condition = null
	)
	
	life_time_option_button.item_selected.connect(func (id):
		if id is int:
			attribute_effect.life_time = id
			_set_lifetime(id)
	)

	minimum_value_spinbox.value_changed.connect(func (value):
		attribute_effect.minimum_value = value
	)
	
	maximum_value_spinbox.value_changed.connect(func (value):
		attribute_effect.maximum_value = value
	)
	
	remove_button.pressed.connect(func (): 
		removed.emit()	
	)
	
	timer_spinbox.value_changed.connect(func (value):
		attribute_effect.apply_every_second = value	
	)
	
	_redraw()


func _redraw() -> void:
	_populate_attribute_name_list()
	_inherit_from_resource()
	_select_attribute_name()
	

func _select_attribute_name() -> void:
	if attributes_table and attribute_effect:
		var index = attributes_table.attributes.find(attribute_effect.attribute_name)
		attribute_option_button.selected = clampi(index, 0, attribute_option_button.item_count)


func _set_lifetime(value: int) -> void:
	timer_setup_container.visible = value == 1

	if not timer_setup_container.visible:
		application_count_spinbox.value = 0
		timer_spinbox.value = 0.0


func set_values(table: AttributeTable, effect: AttributeEffect) -> void:
	await ready
	attributes_table = table
	attribute_effect = effect
