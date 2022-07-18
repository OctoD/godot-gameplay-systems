@tool
extends EditorPlugin

var attribute_node_icon = preload("assets/attribute_icon.png");
var gameplay_effect_icon = preload("assets/timed_icon.png")
var damage_effect_icon = preload("assets/damage_gameplay_effect.png")
var restore_effect_icon = preload("assets/restore_attribute_icon.png")

var gameplayAttributeMap = preload("nodes/GameplayAttributeMap.gd")
var gameplayAttribute = preload("nodes/GameplayAttribute.gd")
var gameplayEffect = preload("nodes/GameplayEffect.gd")
var timedGameplayEffect = preload("nodes/TimedGameplayEffect.gd")
var attributeConsumeGameplayEffect = preload("premade_gameplay_effects/AttributeConsumeGameplayEffect.gd")
var attributeRegenGameplayEffect = preload("premade_gameplay_effects/AttributeRegenGameplayEffect.gd")
var damageGameplayEffect = preload("premade_gameplay_effects/DamageGameplayEffect.gd")
var restoreGameplayEffect = preload("premade_gameplay_effects/RestoreGameplayEffect.gd")

func _enter_tree():
	
	# basenodes
	add_custom_type("GameplayAttributeMap", "Node", gameplayAttributeMap, attribute_node_icon);
	add_custom_type("GameplayAttribute", "Node", gameplayAttribute, attribute_node_icon);
	add_custom_type("GameplayEffect", "Node", gameplayEffect, gameplay_effect_icon);
	add_custom_type("TimedGameplayEffect", "GameplayEffect", timedGameplayEffect, gameplay_effect_icon);

	# premade gameplay effects
	add_custom_type("AttributeConsumeGameplayEffect", "TimedGameplayEffect", attributeConsumeGameplayEffect, gameplay_effect_icon);
	add_custom_type("AttributeRegenGameplayEffect", "TimedGameplayEffect", attributeRegenGameplayEffect, gameplay_effect_icon);
	add_custom_type("DamageGameplayEffect", "GameplayEffect", damageGameplayEffect, damage_effect_icon);
	add_custom_type("RestoreGameplayEffect", "GameplayEffect", restoreGameplayEffect, restore_effect_icon);
		

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
