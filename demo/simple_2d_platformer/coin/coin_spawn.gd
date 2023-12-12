@tool
class_name CoinSpawn extends Path2D


@export_category("Spawing rules")
@export var max_stages := 1:
	get:
		return max_stages
	set(value):
		max_stages = value
		_spawn_coin()
@export var spacing_x := 1.0:
	get:
		return spacing_x
	set(value):
		spacing_x = value
		_spawn_coin()


const coin_scene = preload("res://examples/simple_2d_platformer/coin/coin.tscn")


func _ready() -> void:
	if Engine.is_editor_hint():
		set_owner(get_tree().edited_scene_root)
	_spawn_coin()


func _spawn_coin() -> void:
	var points = curve.tessellate_even_length(max_stages, spacing_x)
	
	for child in get_children():
		child.queue_free()
	
	for i in points:
		var instance = coin_scene.instantiate()

		instance.position = i

		add_child(instance)
