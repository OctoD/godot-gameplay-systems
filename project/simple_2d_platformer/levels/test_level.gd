extends Node2D


@onready var death_floor: EffectedArea2D = $hazards/death_floor
@onready var spawn_point: Node2D = $SpawnPoint


func _ready() -> void:
	scale *= 2
	death_floor.body_entered.connect(func (body: Player):
		if body:
			body.global_position = spawn_point.global_position	
	)
