class_name DoomLikeEnemySpawner extends Node3D

@export_category("Enemies")
@export_node_path("Node3D") var spawn_on_node_path: NodePath = NodePath()


const enemy_scene = preload("res://examples/doom_like_fps/enemies/doom_like_enemy_3d.tscn")


var spawn_on_node: Node3D


func _ready() -> void:
	spawn_on_node = get_node(spawn_on_node_path)

	if owner != null:
		await owner.ready
		spawn()


func spawn() -> void:
	if spawn_on_node != null:
		var enemy = enemy_scene.instantiate() as DoomLikeEnemy3D
		spawn_on_node.add_child(enemy)
		
		enemy.global_position = global_position
		
		enemy.died.connect(func ():
			var timer = Timer.new()
			
			timer.autostart = true
			timer.one_shot = true
			timer.wait_time = 5.0
			
			timer.timeout.connect(func ():
				spawn()
				timer.queue_free()	
			)
			
			add_child(timer)
		)
