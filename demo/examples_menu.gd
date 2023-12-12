extends Node2D


signal scene_selected(scene: Variant)


@onready var camera: Camera2D = $Camera2D
@onready var menu_control: Control = $ExamplesMenu
@onready var button_group: VBoxContainer = $ExamplesMenu/ExampleButtons
@onready var preferences: Control = $CanvasLayer/Preferences
@onready var preferences_button: Button = $ExamplesMenu/PreferencesButton
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
	
	preferences_button.pressed.connect(func ():
		preferences.show()
	)


func _process(_delta: float) -> void:
	if preferences.visible and Input.is_action_just_pressed("close_example"):
		preferences.hide()


func hide_menu() -> void:
	camera.enabled = false
	hide()


func show_menu() -> void:
	camera.enabled = true
	show()
