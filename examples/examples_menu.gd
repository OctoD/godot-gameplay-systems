extends Node2D


signal scene_selected(scene: Variant)


@onready var camera: Camera2D = $Camera2D
@onready var menu_control: Control = $ExamplesMenu
@onready var button_group: VBoxContainer = $ExamplesMenu/ExampleButtons
@onready var quit_button: Button = $ExamplesMenu/QuitButton


func _ready() -> void:
	for button in button_group.get_children():
		if button is ExampleButton:
			button.scene_selected.connect(func (scene):
				scene_selected.emit(scene)	
			)

	quit_button.pressed.connect(func ():
		get_tree().quit(0)	
	)


func hide_menu() -> void:
	camera.enabled = false
	hide()


func show_menu() -> void:
	camera.enabled = true
	show()
