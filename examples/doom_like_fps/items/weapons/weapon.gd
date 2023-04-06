@tool
class_name DoomLikeFPSWeaponItem extends Item


@export_category("Bullets")
@export var bullet_damage: float = 10.0
@export var bullet_speed: float = 10.0
@export var reload_time: float = 0.0


const bullet_scene = preload("res://examples/doom_like_fps/items/weapons/bullet.tscn")

var _has_weapon_tag: String:
	get:
		return "has." + name
var _can_shoot_tag: String:
	get:
		return "can.shoot." + name
var _equipped_tag: String:
	get:
		return name + ".equipped"
var _reloading_tag: String:
	get:
		return "reloading." + name


func _activate(evt: ItemActivationEvent) -> void:
	if evt.has_owner:
		var bullet = bullet_scene.instantiate()
		var player = evt.owner as DoomLikeFPSExamplePlayer

		bullet.damage = bullet_damage
		bullet.speed = bullet_speed

		if player:
			print("bullet fired from " + name)
			bullet.transform = player.active_weapon.global_transform
			bullet.velocity = -bullet.transform.basis.z * bullet.speed
			player.get_tree().root.add_child(bullet)

		if reload_time > 0.0 and not evt.equipment.tags.has(_reloading_tag):
			var timer = Timer.new()

			evt.equipment.add_tag(_reloading_tag)
			timer.autostart = true
			timer.one_shot = true
			timer.wait_time = reload_time
			timer.timeout.connect(func ():
				evt.equipment.add_tag(_can_shoot_tag)
				evt.equipment.remove_tag(_reloading_tag)
				timer.queue_free()	
			)
			
			player.add_child(timer)
			evt.equipment.remove_tag(_can_shoot_tag)


func _init() -> void:
	tags_added_on_add.append_array([_has_weapon_tag, _can_shoot_tag])

	tags_added_on_equip.append(_equipped_tag)
	tags_required_to_equip.append(_has_weapon_tag)
	tags_removed_on_unequip.append(_equipped_tag)

	tags_required_to_activate.append_array([_can_shoot_tag, _has_weapon_tag, _equipped_tag])

