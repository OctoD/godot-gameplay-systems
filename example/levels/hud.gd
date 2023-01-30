extends Control
class_name Hud


func handle_attribute_changed(attribute_name: String, new_value: float, _old_value: float) -> void:
	$HBoxContainer.get_node(attribute_name).text = attribute_name + ": " + str(new_value)
