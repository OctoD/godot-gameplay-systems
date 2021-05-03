tool
extends EditorPlugin


func _enter_tree():
	var attribute_node_icon = load("res://addons/godot-gameplay-attributes/assets/attribute_icon.png");
	var gameplay_effect_icon = load("res://addons/godot-gameplay-attributes/assets/timed_icon.png")
	var damage_effect_icon = load("res://addons/godot-gameplay-attributes/assets/damage_gameplay_effect.png")
	var restore_effect_icon = load("res://addons/godot-gameplay-attributes/assets/restore_attribute_icon.png")
	
	# basenodes
	add_custom_type("GameplayAttributeMap", "Node", load("res://addons/godot-gameplay-attributes/nodes/GameplayAttributeMap.gd"), attribute_node_icon);
	add_custom_type("GameplayAttribute", "Node", load("res://addons/godot-gameplay-attributes/nodes/GameplayAttribute.gd"), attribute_node_icon);
	add_custom_type("GameplayEffect", "Node", load("res://addons/godot-gameplay-attributes/nodes/GameplayEffect.gd"), gameplay_effect_icon);
	add_custom_type("TimedGameplayEffect", "GameplayEffect", load("res://addons/godot-gameplay-attributes/nodes/TimedGameplayEffect.gd"), gameplay_effect_icon);

	# premade gameplay effects
	add_custom_type("AttributeConsumeGameplayEffect", "TimedGameplayEffect", load("res://addons/godot-gameplay-attributes/premade_gameplay_effects/AttributeConsumeGameplayEffect.gd"), gameplay_effect_icon);
	add_custom_type("AttributeRegenGameplayEffect", "TimedGameplayEffect", load("res://addons/godot-gameplay-attributes/premade_gameplay_effects/AttributeRegenGameplayEffect.gd"), gameplay_effect_icon);
	add_custom_type("DamageGameplayEffect", "GameplayEffect", load("res://addons/godot-gameplay-attributes/premade_gameplay_effects/DamageGameplayEffect.gd"), damage_effect_icon);
	add_custom_type("RestoreGameplayEffect", "GameplayEffect", load("res://addons/godot-gameplay-attributes/premade_gameplay_effects/RestoreGameplayEffect.gd"), restore_effect_icon);
		

func _exit_tree():
	# basenodes
	
	remove_custom_type("GameplayAttribute")
	remove_custom_type("GameplayAttributeMap")
	remove_custom_type("GameplayEffect")
	remove_custom_type("TimedGameplayEffect")

	# premade gameplay effects
	remove_custom_type("AttributeConsumeGameplayEffect")
	remove_custom_type("AttributeRegenGameplayEffect")
	remove_custom_type("DamageGameplayEffect")
	remove_custom_type("RestoreGameplayEffect")
