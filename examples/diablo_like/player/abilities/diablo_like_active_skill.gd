@tool
class_name DiabloLikeActiveAbility extends DiabloLikeSkill


@export_category("Active Ability")
@export var cast_scene: PackedScene = null
@export var resource_cost: float = 0.0
@export var projectile_velocity: float = 1000.0


func activate(event: ActivationEvent) -> void:
	var attribute_effect = AttributeEffect.new()
	var cost_effect = GameplayEffect.new()
	var player = event.character as DiabloLikePlayer
	
	attribute_effect.attribute_name = "mana"
	attribute_effect.maximum_value = -resource_cost
	attribute_effect.minimum_value = -resource_cost
	
	cost_effect.attributes_affected.append(attribute_effect)

	event.character.add_child(cost_effect)

	if cast_scene != null and cast_scene.can_instantiate():
		var scene = cast_scene.instantiate() as Node2D

		player.get_tree().root.add_child(scene)

		if grant_tags.has("ranged"):
			scene.look_at(player.get_global_mouse_position())
			scene.position = player.global_position
			scene.speed = projectile_velocity
			scene.velocity = (player.get_global_mouse_position() - player.position).normalized()
		elif grant_tags.has("summon"):
			scene.position = player.cursor_position
		else:
			scene.position = player.position


func can_activate(event: ActivationEvent) -> bool:
	var player = event.character as DiabloLikePlayer
	
	if player == null or not event.has_ability_container:
		return false
		
	var mana = player.gameplay_attribute_map.get_attribute_by_name("mana")
	
	if mana == null:
		return false
		
	var deducted = mana.current_value - resource_cost

	if deducted < 0.0:
		return false
	
	return true
