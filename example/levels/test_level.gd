extends Node2D


@onready var hud: Hud = $Hud
@onready var player: Player = $Player


func _ready() -> void:
	for attribute in player.gameplay_attribute_map._attributes_dict.values():
		_setup_attribute(attribute)
	
	player.gameplay_attribute_map.attribute_changed.connect(_setup_attribute)


func _setup_attribute(attribute):
	if attribute.attribute_name == "health":
		hud.handle_attribute_changed("Health", attribute.current_value, 0)
	elif attribute.attribute_name == "score":
		hud.handle_attribute_changed("Score", attribute.current_value, 0)	
