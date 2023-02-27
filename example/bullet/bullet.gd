@tool
class_name Bullet extends EffectedArea2D

@export_category("Bullet")

@export var bullet_direction := Vector2.DOWN:
	get:
		return bullet_direction
	set(value):
		bullet_direction = value
@export var bullet_trail_length := 10.0
@export_flags_2d_navigation var can_damage_layers


@onready var particle: GPUParticles2D = $GPUParticles2D


func _process(delta: float) -> void:
	if Engine.is_editor_hint():
		var mat = particle.process_material as ParticleProcessMaterial
		
		if mat:
			var dir = 1.0 if bullet_direction.x < 0 else -1.0
			mat.gravity.x = dir * bullet_trail_length
		pass


func _physics_process(delta: float) -> void:
	if not Engine.is_editor_hint():
		position += bullet_direction * delta


func fly(direction: Vector2) -> void:
	bullet_direction = direction
#	particle.process_material.direction = direction
