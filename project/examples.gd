extends Node


@onready var intro: SlideShow = $Intro
@onready var running_example: Node = $RunningExample
@onready var examples_menu = $ExamplesMenu



func _input(event: InputEvent) -> void:
	if event.is_action_pressed("close_example") and intro == null:
		for child in running_example.get_children():
			running_example.remove_child(child)
			Input.mouse_mode = Input.MOUSE_MODE_CONFINED
		examples_menu.show_menu()
	elif event.is_action_pressed("close_example") and intro != null and intro.playing:
		intro.skip_slide_to_next()


func _ready() -> void:
	Input.mouse_mode = Input.MOUSE_MODE_CONFINED
	
	examples_menu.modulate.a = 0.0
	examples_menu.scene_selected.connect(func (scene):
		examples_menu.hide_menu()
		running_example.add_child(scene)
	)

	intro.finished.connect(func ():
		create_tween().tween_property(examples_menu, "modulate:a", 1.0, 1.0)	
		intro.queue_free()
	)
