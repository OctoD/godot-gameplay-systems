extends GridContainer


@export_category("Effect")
@export var attribute_effect: AttributeEffect = AttributeEffect.new()


@onready var attribute_name_label: Label = $AttributeName
@onready var life_time_option_button: OptionButton = $LifeTime/OptionButton
@onready var minimum_value_spinbox: SpinBox = $MinimumValue/SpinBox
@onready var maximum_value_spinbox: SpinBox = $MaximumValue/SpinBox
@onready var timer_setup_container: Panel = $Panel
@onready var timer_spinbox: SpinBox = $Panel/VBoxContainer/TimerSetupContainer/TimeoutSpinBox
@onready var application_count_spinbox: SpinBox = $Panel/VBoxContainer/TimerSetupContainer/ApplicationCountSpinBox


func _inherit_from_resource(res: AttributeEffect) -> void:
	if res != null:
		attribute_name_label.text = res.attribute_name
		life_time_option_button.selected = res.life_time
		minimum_value_spinbox.value = res.minimum_value
		maximum_value_spinbox.value = res.maximum_value
		timer_spinbox.value = res.apply_every_second
		application_count_spinbox.value = res.max_applications
		_set_lifetime(res.life_time)


func _ready() -> void:
	timer_setup_container.visible = false
	
	if attribute_effect:
		_set_lifetime(attribute_effect.life_time)
	
	attribute_effect.changed.connect(_inherit_from_resource)
	
	minimum_value_spinbox.changed.connect(func (value):
		attribute_effect.minimum_value = value	
	)
	
	maximum_value_spinbox.changed.connect(func (value):
		attribute_effect.maximum_value = value	
	)
	
	life_time_option_button.item_selected.connect(func (id):
		attribute_effect.life_time = id
		_set_lifetime(id)
	)


func _set_lifetime(value: int) -> void:
	timer_setup_container.visible = value == 1

	if not timer_setup_container.visible:
		application_count_spinbox.value = 0
		timer_spinbox.value = 0.0
