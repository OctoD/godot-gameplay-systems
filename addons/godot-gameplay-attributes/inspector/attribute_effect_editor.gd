@tool
extends EditorProperty


var resource_input := EditorResourcePicker.new()
var vbox_container := VBoxContainer.new()
var scroll_container := ScrollContainer.new()
var row_editor_scene = preload("res://addons/godot-gameplay-attributes/inspector/components/attribute_effect_row.tscn")


func _init() -> void:
	resource_input.base_type = "AttributeTable"
	
	vbox_container.add_child(resource_input)
	vbox_container.add_child(scroll_container)
	
	resource_input.resource_changed.connect(func (res):
		get_edited_object().table = res	
	)
	
	resource_input.resource_selected.connect(func (res, inspector):
		get_edited_object().table = res	
	)
	
	add_child(vbox_container)


func _make_row(res: AttributeEffect) -> Control:
	var instance = row_editor_scene.instantiate()
	instance.attribute_effect = res
	return instance
	

func _update_property() -> void:
	var target = get_edited_object()
	
	resource_input.edited_resource = target.table
