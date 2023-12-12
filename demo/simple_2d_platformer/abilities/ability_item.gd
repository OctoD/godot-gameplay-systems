extends Area2D

@export_category("Ability")
@export var granted_ability: Ability


func _ready() -> void:
	body_entered.connect(func (player: Player):
		if player and granted_ability:
			player.ability_container.ability_granted.connect(func (x):
				if x == granted_ability:
					queue_free()	
			)
			
			player.ability_container.grant(granted_ability)
	)
