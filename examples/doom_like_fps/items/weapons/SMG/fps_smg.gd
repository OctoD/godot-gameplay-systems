@tool
class_name DoomLikeFPSSMG extends DoomLikeFPSWeaponItem


func _init() -> void:
	scene = preload("res://examples/doom_like_fps/items/weapons/SMG/fps_smg.tscn")
	name = "smg"
	bullet_damage = 15
	bullet_speed = 115
	super._init()
