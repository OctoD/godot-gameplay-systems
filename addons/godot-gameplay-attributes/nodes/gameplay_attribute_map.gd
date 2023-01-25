@tool
class_name GameplayAttributeMap extends Node


signal attribute_changed(attribute: AttributeSpec)
signal effect_applied(effect: GameplayEffect)
signal effect_paused(effect: GameplayEffect)
signal effect_removed(effect: GameplayEffect)


@export_category("Owner")
@export_node_path var owning_character = NodePath()


@export_category("Attributes")
@export var attributes: Array[Attribute] = []
@export var table: AttributeTable = null


var _attributes_dict: Dictionary = {}


func _add_attribute_spec(spec: Attribute) -> void:
	if Engine.is_editor_hint():
		attributes.append(spec)


func _handle_character_child_entered_tree(node: Node) -> void:
	if node is GameplayEffect and node.owner:
		node.owner.remove_child(node)
		add_child(node)
	elif node is GameplayEffect:
		add_child(node)


func _handle_character():
	if owning_character != null and not owning_character.is_empty():
		var node = get_node(owning_character)
		
		if node != null:
			if not node.child_entered_tree.is_connected(_handle_character_child_entered_tree):
				node.child_entered_tree.connect(_handle_character_child_entered_tree)


func _get_attribute_at(index: int) -> Attribute:
	if Engine.is_editor_hint():
		if attributes.size() > index:
			return attributes[index]

		attributes.append(Attribute.new())
		return attributes[index]
	else:
		return null


func _ready() -> void:
	_handle_character()
	
	if not Engine.is_editor_hint():
		_setup_attributes()


func _setup_attributes() -> void:
	_attributes_dict = {}

	for attribute in attributes:
		var previous = get_attribute_by_name(attribute.attribute_name)
		
		if previous:
			previous.free()
		
		var spec = AttributeSpec.from_attribute(attribute)
		
		spec.changed.connect(func (attribute): 
			attribute_changed.emit(attribute)	
		)
		
		_attributes_dict[spec.attribute_name] = spec


func _update_attribute(index: int, key: String, value: float) -> void:
	if Engine.is_editor_hint():
		if attributes.size() >= index:
			if key in attributes[index]:
				attributes[index][key] = value


func get_attribute_by_name(attribute_name: String) -> AttributeSpec:
	if _attributes_dict.has(attribute_name):
		return _attributes_dict.get(attribute_name)
	
	return null


class AttributeSpec extends Object:
	signal changed(spec: AttributeSpec)
	signal minimum_value_changed(from: float, to: float)
	signal maximum_value_changed(from: float, to: float)
	
	var __setup := false
	var attribute_name := ""
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
				current_value = clampf(value, maximum_value, minimum_value)
			if not __setup:
				changed.emit(self)
	var maximum_value := 0.0:
		get:
			return maximum_value
		set(value):
			var previous_value = maximum_value
			maximum_value = value
			
			if not __setup:
				maximum_value_changed.emit(previous_value, value)
	var minimum_value := 0.0:
		get: 
			return minimum_value
		set(value):
			var previous_value = minimum_value
			minimum_value = value
			
			if not __setup:
				minimum_value_changed.emit(previous_value, value)


	static func from_attribute(attribute: Attribute) -> AttributeSpec:
		var instance = AttributeSpec.new()
		instance.__setup = true
		instance.attribute_name = attribute.attribute_name
		instance.maximum_value = attribute.maximum_value
		instance.minimum_value = attribute.minimum_value
		instance.current_value = attribute.current_value
		instance.__setup = false
		return instance
