@tool
class_name DoomLikeFPSSMG extends DoomLikeFPSWeaponItem


func _init() -> void:
	icon = preload("res://examples/doom_like_fps/items/weapons/SMG/assets/uzi.png")
	scene = preload("res://examples/doom_like_fps/items/weapons/SMG/fps_smg.tscn")
	name = "smg"
	bullet_damage = 15
	bullet_speed = 115
	## four shots per second
	reload_time = 0.25
	super._init()
	tags.append("left.handed")
