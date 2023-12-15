extends Panel


@onready var back_button: Button = $Preferences/BackButton
@onready var full_screen_button: CheckButton = $Preferences/FullScreenButton


func _ready() -> void:
	back_button.pressed.connect(func ():
		hide()	
	)
	
	full_screen_button.toggled.connect(func (button_pressed: bool):
		if button_pressed:
			DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_MAXIMIZED)
		else:
			DisplayServer.window_set_mode(DisplayServer.WINDOW_MODE_WINDOWED)
	)
