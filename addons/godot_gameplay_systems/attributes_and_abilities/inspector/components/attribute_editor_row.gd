@tool
extends VBoxContainer


signal attribute_updated(key: String, value: float)


@export_category("Attribute")
@export var attribute: AttributeResource = null:
	get:
		return attribute
	set(value):
		attribute = value
		_update_ui()


@onready var label: Label = $Label
@onready var max_value: SpinBox = $GridContainer/MaximumValue/SpinBox
@onready var min_value: SpinBox = $GridContainer/MinimumValue/SpinBox
@onready var cur_value: SpinBox = $GridContainer/CurrentValue/SpinBox


var _updating_ui = false


func _init() -> void:
	pass


func _ready() -> void:
	max_value.step = 0.01
	min_value.step = 0.01
	cur_value.step = 0.01
	max_value.value_changed.connect(func (value):
		if not _updating_ui:
			attribute_updated.emit("maximum_value", value)
	)
	min_value.value_changed.connect(func (value):
		if not _updating_ui:
			attribute_updated.emit("minimum_value", value)
	)
	cur_value.value_changed.connect(func (value):
		if not _updating_ui:
			attribute_updated.emit("current_value", value)
	)
	
	_update_ui()


func _update_ui() -> void:
	if attribute != null:
		_updating_ui = true
		label.text = attribute.attribute_name
		max_value.value = attribute.maximum_value
		min_value.value = attribute.minimum_value
		cur_value.value = attribute.current_value
		_updating_ui = false


func set_values(res: AttributeResource) -> void:
	await ready
	attribute = res
