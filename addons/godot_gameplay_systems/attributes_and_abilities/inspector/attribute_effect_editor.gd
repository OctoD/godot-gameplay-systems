@tool
extends EditorProperty

var add_row_button := Button.new()
var scroll_container := VBoxContainer.new()
var resource_input := EditorResourcePicker.new()
var row_editor_scene = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/inspector/components/attribute_effect_editor_row.tscn")
var vbox_container := VBoxContainer.new()


func _draw_effects_row(table: AttributeTable, res: AttributeEffect, index: int) -> Control:
	var instance = row_editor_scene.instantiate()
	
	instance.set_values(table, res)
	
	instance.removed.connect(func ():
		var target = get_edited_object() as GameplayEffect
		target.attributes_affected.erase(res)
		_update_ui()
	)
	
	res.changed.connect(func ():
		var prop = get_edited_property()
		var target = get_edited_object()
		
		target[prop][index] = res;
	)
	
	return instance


func _draw_effects_rows() -> void:
	var target = get_edited_object() as GameplayEffect
	var index = 0

	_empty_scroll_container()
	
	if target and target.attributes_affected:
		for eff in target.attributes_affected:
			scroll_container.add_child(_draw_effects_row(target.table, eff, index))
			index += 1


func _handle_add_attribute_effect() -> void:
	var target = get_edited_object() as GameplayEffect
	
	target.attributes_affected.append(AttributeEffect.new())	
	
	_update_ui()


func _init() -> void:
	add_row_button.text = "Add effect"
	add_row_button.hide()
	
	resource_input.base_type = "AttributeTable"
	
	vbox_container.add_child(resource_input)
	vbox_container.add_child(scroll_container)
	vbox_container.add_child(add_row_button)
	
	add_row_button.pressed.connect(_handle_add_attribute_effect)
	
	resource_input.resource_changed.connect(func (res):
		_handle_attribute_table_changed(res)
	)
	
	resource_input.resource_selected.connect(func (res, inspector):
		_handle_attribute_table_changed(res)
	)
	
	add_child(vbox_container)

	_update_ui()


func _empty_scroll_container() -> void:
	for child in scroll_container.get_children():
		scroll_container.remove_child(child)


func _handle_attribute_table_changed(res: AttributeTable) -> void:
	get_edited_object().table = res
	
	if res:
		add_row_button.show()
	else:
		add_row_button.hide()
	

func _update_property() -> void:
	var target = get_edited_object() as GameplayEffect
	
	resource_input.edited_resource = target.table

	_update_ui()


func _update_ui() -> void:
	var target = get_edited_object()
	
	_empty_scroll_container()
	_draw_effects_rows()
	
	if target and target.table:
		add_row_button.show()
	else:
		add_row_button.hide()
