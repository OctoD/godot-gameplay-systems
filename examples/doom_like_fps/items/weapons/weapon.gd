@tool
class_name DoomLikeFPSWeaponItem extends Item


@export_category("UI")
@export var icon: Texture = null


@export_category("Bullets")
@export var bullet_damage: float = 10.0
@export var bullet_speed: float = 10.0
@export var reload_time: float = 0.0
@export var recoil: float = 0.05


const bullet_scene = preload("res://examples/doom_like_fps/items/weapons/bullet.tscn")

var _has_weapon_tag: String:
	get:
		return "has." + name
var _equipped_tag: String:
	get:
		return name + ".equipped"
var _reloading_tag: String:
	get:
		return "reloading." + name


func _activate(evt: ItemActivationEvent) -> void:
	if not evt.has_owner:
		return

	var bullet = bullet_scene.instantiate()
	var player = evt.owner as DoomLikeFPSExamplePlayer

	bullet.damage = bullet_damage
	bullet.speed = bullet_speed

	if player:
		print("bullet fired from " + name)
		
		if player.active_weapon_0.current:
			bullet.transform = player.active_weapon_0.global_transform
		elif player.active_weapon_1.current:
			bullet.transform = player.active_weapon_1.global_transform
		else:
			bullet.transform = player.global_transform

		bullet.velocity = -bullet.transform.basis.z * bullet.speed

		player.get_tree().root.add_child(bullet)

		_handle_reload(evt)


func _handle_reload(evt: ItemActivationEvent) -> void:
	if reload_time <= 0.0:
		return

	var timer = Timer.new()

	timer.autostart = true
	timer.one_shot = true
	timer.wait_time = reload_time
	timer.timeout.connect(func ():
		## If the weapon is equipped when the timeout ends, we can remove the "reloading" tag.
		if evt.equipment.has_tag(_equipped_tag):
			evt.equipment.remove_tag(_reloading_tag)
		timer.queue_free()
	)

	evt.owner.add_child(timer)


func _can_activate(evt: ItemActivationEvent) -> bool:
	return not evt.equipment.has_tag(_reloading_tag)


func _equip(equipment: Equipment, _slot: EquipmentSlot) -> void:
	## Reload if the equipment has a reloading.[thisweapon] tag
	if equipment.has_tag(_reloading_tag):
		_handle_reload(ItemActivationEvent.new(equipment, -1))


func _init() -> void:
	tags_added_on_add.append_array([_has_weapon_tag])

	tags_added_on_activation.append(_reloading_tag)
	tags_added_on_equip.append(_equipped_tag)
	tags_required_to_equip.append(_has_weapon_tag)
	tags_removed_on_unequip.append(_equipped_tag)

	tags_required_to_activate.append_array([_has_weapon_tag, _equipped_tag])

