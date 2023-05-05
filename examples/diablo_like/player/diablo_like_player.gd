class_name DiabloLikePlayer extends CharacterBody2D


const gold = preload("res://examples/diablo_like/items/gold/gold_coin.tres")


@onready var hud: DiabloLikeHud = $CanvasLayer/DiabloLikeHud
@onready var ability_container: AbilityContainer = $AbilityContainer
@onready var gameplay_attribute_map: GameplayAttributeMap = $GameplayAttributeMap
@onready var inventory: Inventory = $Inventory
@onready var equipment: Equipment = $Equipment


var cursor_position: Vector2 = Vector2.ZERO
var next_position: Vector2 = Vector2.ZERO


func _input(event: InputEvent) -> void:
	if event.is_action_pressed("diablo_like_inventory"):
		hud.toggle()
	elif event.is_action_pressed("diablo_like_ability_1"):
		hud.activate_ability_on_slot(1)
	elif event.is_action_pressed("diablo_like_ability_2"):
		hud.activate_ability_on_slot(2)
	elif event.is_action_pressed("diablo_like_ability_3"):
		hud.activate_ability_on_slot(3)
	elif event.is_action_pressed("diablo_like_ability_4"):
		hud.activate_ability_on_slot(4)
	elif event.is_action_pressed("diablo_like_move_to"):
		next_position = cursor_position
	elif event.is_action_pressed("diablo_like_add_gold"):
		var _gold = gold.duplicate()
		_gold.quantity_current = randi_range(1, 200)
		inventory.add_item(_gold)
	

func _physics_process(_delta: float) -> void:
	if ability_container.tags.has(DiabloLikeSkill.DEAD_TAG):
		# sorry, your character is dead, cannot move it anymore
		return
	
	if next_position != Vector2.ZERO:
		pass # get path, move toward path at it's movement speed

	cursor_position = get_global_mouse_position()


func _ready() -> void:
	hud.setup_ability_container(ability_container)
	hud.setup_gameplay_attribute_map(gameplay_attribute_map)
	hud.setup_equipment(equipment)
	hud.setup_inventory(inventory)

	gameplay_attribute_map.attribute_changed.connect(func (attribute_spec: AttributeSpec) -> void:
		if attribute_spec.attribute_name == "health" and attribute_spec.current_value <= 0.0:
			ability_container.add_tag(DiabloLikeSkill.DEAD_TAG)
	)


func go_to_position(_position: Vector2) -> void:
	pass
