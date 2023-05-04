extends Node2D


@onready var drop: Drop = $Drop


func die() -> void:
	drop.drop_items()
