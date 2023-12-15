class_name DiabloLikePlayer extends CharacterBody2D


const gold = preload("res://examples/diablo_like/items/gold/gold_coin.tres")


@onready var hud: DiabloLikeHud = $CanvasLayer/DiabloLikeHud
@onready var ability_container: AbilityContainer = $AbilityContainer
@onready var gameplay_attribute_map: GameplayAttributeMap = $GameplayAttributeMap
@onready var inventory: Inventory = $Inventory
@onready var equipment: Equipment = $Equipment
@onready var point_and_click: PointAndClick2D = $PointAndClick2D


var movement_speed: AttributeSpec:
	get:
		if movement_speed == null:
			movement_speed = gameplay_attribute_map.get_attribute_by_name("movement_speed")
		return movement_speed
	set(value):
		movement_speed = value


func _input(event: InputEvent) -> void:
	if event.is_action_pressed("diablo_like_inventory"):
		hud.toggle()
		point_and_click.active = !point_and_click.active
		point_and_click.stop_movement()
	elif event.is_action_pressed("diablo_like_ability_1"):
		hud.activate_ability_on_slot(1)
		point_and_click.stop_movement()
	elif event.is_action_pressed("diablo_like_ability_2"):
		hud.activate_ability_on_slot(2)
		point_and_click.stop_movement()
	elif event.is_action_pressed("diablo_like_ability_3"):
		hud.activate_ability_on_slot(3)
		point_and_click.stop_movement()
	elif event.is_action_pressed("diablo_like_ability_4"):
		hud.activate_ability_on_slot(4)
		point_and_click.stop_movement()
	elif Input.is_action_just_pressed("diablo_like_move_to"):
		point_and_click.set_new_movement_position()
	elif event.is_action_pressed("diablo_like_add_gold"):
		var _gold = gold.duplicate()
		_gold.quantity_current = randi_range(1, 200)
		inventory.add_item(_gold)


func _ready() -> void:
	hud.setup_ability_container(ability_container)
	hud.setup_gameplay_attribute_map(gameplay_attribute_map)
	hud.setup_equipment(equipment)
	hud.setup_inventory(inventory)

	gameplay_attribute_map.attribute_changed.connect(func (attribute_spec: AttributeSpec) -> void:
		if attribute_spec.attribute_name == "health" and attribute_spec.current_value <= 0.0:
			ability_container.add_tag(DiabloLikeSkill.DEAD_TAG)
	)
	
	ability_container.tags_updated.connect(func (newtags, _oldtags):
		point_and_click.active = not newtags.has(DiabloLikeSkill.DEAD_TAG)
	)

	point_and_click.movement_speed = movement_speed.current_buffed_value
