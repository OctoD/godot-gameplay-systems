class_name DiabloLikePlayer extends CharacterBody2D


@onready var hud: DiabloLikeHud = $DiabloLikeHud
@onready var ability_container: AbilityContainer = $AbilityContainer
@onready var gameplay_attribute_map: GameplayAttributeMap = $GameplayAttributeMap
@onready var inventory: Inventory = $Inventory
@onready var equipment: Equipment = $Equipment


func _input(event: InputEvent) -> void:
	if event.is_action_pressed("diablo_like_inventory"):
		hud.toggle()


func _ready() -> void:
	gameplay_attribute_map.attribute_changed.connect(func (attribute_spec: AttributeSpec) -> void:
		hud.handle_attribute_changed(attribute_spec)	
	)
