@tool
extends TextureButton

@export_category("Skill button")
@export var ability: Ability = null:
	get:
		return ability
	set(value):
		ability = value
		
		if value != null:
			draw_ability()
		
@export_range(1, 4) var skill_number: int = 1


@onready var label: Label = $Label
var ability_container: AbilityContainer


const noskillset_icon = preload("res://examples/diablo_like/player/hud/in_game_bar/noskillset_icon.png")


func _on_pressed() -> void:
	if ability != null and ability_container != null:
		ability_container.activate_one(ability)


func _ready() -> void:
	label.text = str(skill_number)	
	pressed.connect(_on_pressed)
	

func _process(delta: float) -> void:
	if Engine.is_editor_hint():
		label.text = str(skill_number)
		draw_ability()


func activate() -> void:
	if ability != null and ability_container != null:
		ability_container.activate_one(ability)


func draw_ability() -> void:
	if ability != null:
		texture_normal = ability.ui_icon
	else:
		texture_normal = noskillset_icon
