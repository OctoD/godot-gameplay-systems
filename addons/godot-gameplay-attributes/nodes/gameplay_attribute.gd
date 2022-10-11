extends Node
class_name GameplayAttribute


signal attribute_changed(name: String, current_value: float, previous_value: float)


var _underlying_value := 0.0
var _underlying_max := 0.0
var _underlying_min := 0.0


@export_category("Gameplay attribute")

@export var max_value := 0.0:
	get:
		return _underlying_max
	set(value):
		_underlying_max = value
		
		if _underlying_value > _underlying_max:
			var prev = _underlying_value
			_underlying_value = _underlying_max
			attribute_changed.emit(self.name, _underlying_value, prev)
@export var min_value := 0.0:
	get:
		return _underlying_min
	set(value):
		_underlying_min = value
		
		if _underlying_value < _underlying_min:
			var prev = _underlying_value
			_underlying_value = _underlying_min
			attribute_changed.emit(self.name, _underlying_value, prev)
@export var current_value := 0.0:
	get:
		return _underlying_value
	set(value):
		if value != _underlying_value:
			var prev = _underlying_value
			_underlying_value = clampf(value, _underlying_min, _underlying_max)
			attribute_changed.emit(self.name, _underlying_value, prev)


func deserialize(dictionary: Dictionary) -> void:
	var instance = dict_to_inst(dictionary) as GameplayAttribute
	max_value = instance.max_value
	min_value = instance.min_value
	_underlying_value = instance.current_value


func serialize() -> Dictionary:
	return inst_to_dict(self)
