@tool
class_name DragInteraction extends Interaction


const DRAG_INTERACTABLE_TAG = "dragging"


func _init() -> void:
	tags_added_on_start.append(DRAG_INTERACTABLE_TAG)
	tags_removed_on_end.append(DRAG_INTERACTABLE_TAG)


# func on_before_interaction_start(_manager: InteractionManager, interacted_node: Node) -> void:
# 	# we only want to drag nodes that have the DRAG_INTERACTABLE_TAG
# 	if interacted_node is SotLikeCrate:
# 		interacted_node.dragged = true



# func on_before_interaction_end(_manager: InteractionManager, interacted_node: Node) -> void:
# 	# we only want to drag nodes that have the DRAG_INTERACTABLE_TAG
# 	if interacted_node is SotLikeCrate:
# 		interacted_node.dragged = false


func handle_physics_process(_delta: float, manager: InteractionManager, interacted_node: Node) -> void:
	# it's dead simple, just assign the manager.interacting_owner.center_equipped_item.global_transform to the interacted_node.global_transform
	interacted_node.global_transform = manager.interacting_owner.center_equipped_item.global_transform
