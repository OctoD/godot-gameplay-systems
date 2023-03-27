@tool
class_name FireballAbility extends Ability


const fireball_scene = preload("res://example/abilities/fireball/fireball_projectile.tscn")

@export_category("Fireball")
@export var min_speed := 5.0
@export var max_speed := 10.0

const cooldown_tag = "fireball.cooldown"


func _init() -> void:
	ui_name = "Fireball"
	cooldown_duration = 1.0
	tags_block.append(cooldown_tag)
	tags_block.append(ResurrectAbility.dead_tag)
	tags_end_blocking.append(cooldown_tag)
	tags_cooldown_start.append(cooldown_tag)
	tags_to_remove_on_cooldown_end.append(cooldown_tag)


func activate(event: ActivationEvent) -> void:
	super.activate(event)
	var player = event.character as Player
	
	if player:
		print("player wants to do some damage, casting fireball")
		var instance = fireball_scene.instantiate()
		var speed = randf_range(min_speed, max_speed)
		
		instance.global_position = player.global_position
		instance.direction = Vector2.RIGHT if player.flipped else Vector2.LEFT
		instance.speed = speed
		
		player.get_tree().root.add_child(instance)
		
		event.ability_container.remove_tags(tags_activation_required)
