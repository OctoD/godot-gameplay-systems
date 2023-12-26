@tool
extends TagTree


func _ready() -> void:
	tag_dictionary = preload("res://new_tag_dictionary.tres")
	render()
