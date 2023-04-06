@tool
class_name DoomLikeFPSShotgun extends DoomLikeFPSWeaponItem


func _init() -> void:
	scene = preload("res://examples/doom_like_fps/items/weapons/Shotgun/fps_shotgun.tscn")
	name = "shotgun"
	bullet_damage = 120
	bullet_speed  = 20
	tags_removed_on_activation.append(_can_shoot_tag)
	super._init()
