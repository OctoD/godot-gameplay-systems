class_name DiabloLikeHud extends BoxContainer


@onready var character_stuff: HBoxContainer = $CharacterStuff
@onready var skill_tree
@onready var inventory
@onready var in_game_bar: DiabloLikeInGameBar = $InGameBar


var inventory_visible: bool = false


func _ready() -> void:
	hide_inventory()


func handle_attribute_changed(attribute: AttributeSpec) -> void:
	pass


func hide_inventory() -> void:
	in_game_bar.show()
	character_stuff.hide()
	inventory_visible = false


func show_inventory() -> void:
	in_game_bar.hide()
	character_stuff.show()
	inventory_visible = true


func toggle() -> void:
	show_inventory() if not inventory_visible else hide_inventory()
