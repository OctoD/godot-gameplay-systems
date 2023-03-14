@tool
class_name ResurrectAbility extends Ability

@export_category("Resurrection")
@export var health_added := 2.0
@export var score_removed := 5.0


func _make_effect() -> GameplayEffect:
	var effect = GameplayEffect.new()
	var health_effect = AttributeEffect.new()
	var score_effect = AttributeEffect.new()

	health_effect.attribute_name = "health"
	health_effect.minimum_value = health_added
	health_effect.maximum_value = health_added
	
	score_effect.attribute_name = "score"
	score_effect.minimum_value = -score_removed
	score_effect.maximum_value = -score_removed
	
	effect.attributes_affected.append(health_effect)
	effect.attributes_affected.append(score_effect)
	
	return effect
	

func _init() -> void:
	ui_name = "Resurrect"
	cooldown_duration = 5.0
	tags_activation_required.append("dead")
	tags_activation_required.append("resurrect.start")
	tags_block.append("resurrect.cooldown")
	tags_cooldown_start.append("resurrect.cooldown")
	tags_to_remove_on_activation.append("dead")
	tags_to_remove_on_cooldown_start.append("resurrect.start")
	tags_to_remove_on_cooldown_end.append("resurrect.cooldown")


func activate(event: ActivationEvent) -> void:
	var player = event.character as Player

	super.activate(event)

	if player != null:
		print("player asks for resurrection, poor player :(")
		event.character.add_child(_make_effect())
		player.animated_sprite.play("default")


func can_activate(event: ActivationEvent) -> bool:
	var attribute = event.get_attribute("health")
	return super.can_activate(event) and attribute and attribute.current_value <= 0.0
