@tool
class_name DoomLikeFPSShotgun extends DoomLikeFPSWeaponItem


func _init() -> void:
	icon = preload("res://examples/doom_like_fps/items/weapons/Shotgun/assets/shotgun.png")
	scene = preload("res://examples/doom_like_fps/items/weapons/Shotgun/fps_shotgun.tscn")
	name = "shotgun"
	bullet_damage = 120
	bullet_speed  = 20
	## one shot per second
	reload_time = 1.0
	super._init()
