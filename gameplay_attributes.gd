tool
extends EditorPlugin


func _enter_tree():
	var icon = load("res://addons/gameplay_attributes/assets/attribute_icon.png");
	
	add_custom_type("GameplayAttributeMap", "Node", load("res://addons/gameplay_attributes/nodes/GameplayAttributeMap.gd"), icon);
	add_custom_type("GameplayAttribute", "Node", load("res://addons/gameplay_attributes/nodes/GameplayAttribute.gd"), icon);
	add_custom_type("GameplayEffect", "Node", load("res://addons/gameplay_attributes/nodes/GameplayEffect.gd"), icon);
	add_custom_type("TimedGameplayEffect", "Node", load("res://addons/gameplay_attributes/nodes/TimedGameplayEffect.gd"), icon);


func _exit_tree():
	remove_custom_type("GameplayAttribute")
	remove_custom_type("GameplayAttributeMap")
	remove_custom_type("GameplayEffect")
	remove_custom_type("TimedGameplayEffect")
	
