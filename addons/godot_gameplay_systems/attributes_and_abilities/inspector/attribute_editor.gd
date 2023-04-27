@tool
extends EditorProperty

var resource_input := EditorResourcePicker.new()
var vbox_container := VBoxContainer.new()
var scroll_container := VBoxContainer.new()
var row_scene = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/inspector/components/attribute_editor_row.tscn")

var updating := false


func _init() -> void:
	resource_input.base_type = "AttributeTable"
	
	vbox_container.add_child(resource_input)
	vbox_container.add_child(scroll_container)

	add_child(vbox_container)
	
	resource_input.resource_changed.connect(func (res):
		get_edited_object().table = res
		if res != null:
			_draw_attributes_rows(res)	
		else:
			_empty_attributes()
			_empty_scroll_container()	
	)
	resource_input.resource_selected.connect(func (res, inspect):
		get_edited_object().table = res
		if res != null:
			_draw_attributes_rows(res)	
		else:
			_empty_attributes()
			_empty_scroll_container()
	)

	property_changed.connect(func (property: StringName, value: Variant, field: StringName, changing: bool):
		if property == "attributes" and value == null:
			var target = get_edited_object()
			target.attributes = []
			target.table = null
			resource_input.edited_resource = null
			_empty_scroll_container()
	)


func _draw_attributes_rows(resource: AttributeTable) -> void:
	_empty_scroll_container()

	if resource == null:
		return

	var index = 0

	for attribute in resource.attributes:
		scroll_container.add_child(_make_row(attribute, index))
		index += 1


func _empty_attributes() -> void:
	get_edited_object().attributes = []


func _empty_scroll_container() -> void:
	for child in scroll_container.get_children():
		scroll_container.remove_child(child)


func _make_row(attribute_name: String, index: int) -> Control:
	var gameplay_attributes = get_edited_object() as GameplayAttributeMap
	var spec = gameplay_attributes._get_attribute_at(index)
	var row = row_scene.instantiate()
	
	spec.attribute_name = attribute_name

	row.attribute_updated.connect(func (key, value):
		gameplay_attributes._update_attribute(index, key, value)
	)
	
	row.set_values(spec)
	
	return row


func _update_property() -> void:
	var target = get_edited_object()
	_draw_attributes_rows(target.table)
	resource_input.edited_resource = target.table
