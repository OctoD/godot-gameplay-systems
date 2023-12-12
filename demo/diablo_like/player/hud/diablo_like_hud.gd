class_name DiabloLikeHud extends BoxContainer


@onready var character_stuff: HBoxContainer = $CharacterStuff
@onready var skill_tree: DiabloLikeSkillTree = $CharacterStuff/skill_tree
@onready var inventory_hud: DiabloLikeInventory = $CharacterStuff/inventory
@onready var in_game_bar: DiabloLikeInGameBar = $InGameBar


var inventory_visible: bool = false


func _ready() -> void:
	hide_inventory()


func activate_ability_on_slot(slot_number: int) -> void:
	in_game_bar.activate_ability_on_slot(slot_number)


func hide_inventory() -> void:
	in_game_bar.show()
	character_stuff.hide()
	inventory_visible = false


func setup_ability_container(ability_container: AbilityContainer) -> void:
	in_game_bar.setup_ability_container(ability_container)


func setup_equipment(_equipment: Equipment) -> void:
	pass


func setup_gameplay_attribute_map(gameplay_attribute_map: GameplayAttributeMap) -> void:
	in_game_bar.setup_gameplay_attribute_map(gameplay_attribute_map)


func setup_inventory(inventory: Inventory) -> void:
		inventory_hud.setup_inventory(inventory)


func show_inventory() -> void:
	in_game_bar.hide()
	character_stuff.show()
	inventory_visible = true


func toggle() -> void:
	show_inventory() if not inventory_visible else hide_inventory()
