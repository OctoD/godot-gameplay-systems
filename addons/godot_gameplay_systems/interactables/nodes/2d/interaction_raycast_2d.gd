@tool
@icon("res://addons/godot_gameplay_systems/interactables/assets/InteractionRayCast2DIcon.png")
class_name InteractionRayCast2D extends RayCast2D


## Emitted when an [InteractableArea2D] is detected.
signal interactable_detected(interactable: InteractableArea2D)


@export_category("Interaction owner")
@export_node_path("InteractionManager") var interaction_manager_path := NodePath()


var manager: Node = null
var interacting := false
var previous_collider: Object = null


func _get_configuration_warnings() -> PackedStringArray:
	if interaction_manager_path == null or interaction_manager_path.is_empty():
		return ["Tag manager path cannot be empty"]
	return []


func _ready() -> void:
	collide_with_areas = true
	manager = get_node(interaction_manager_path)


func _physics_process(delta: float) -> void:
	var collider = get_collider()

	if collider is InteractableArea2D:
		interactable_detected.emit(collider)
	
	if manager != null and interacting:
		manager.handle_interaction(self)


func interact() -> void:
	manager.handle_interaction(self)
	interacting = true
