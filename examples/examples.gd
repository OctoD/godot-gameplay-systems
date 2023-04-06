extends Node


@onready var running_example: Node = $RunningExample
@onready var examples_menu = $ExamplesMenu



func _input(event: InputEvent) -> void:
	if event.is_action_pressed("close_example"):
		for child in running_example.get_children():
			running_example.remove_child(child)
		examples_menu.show_menu()


func _ready() -> void:
	examples_menu.scene_selected.connect(func (scene):
		examples_menu.hide_menu()
		running_example.add_child(scene)
	)
