@tool
class_name SailInteraction extends Interaction


const tag = "sailing"


func _init() -> void:
	super._init()
	tags_added_on_start.append(tag)
	tags_required_to_end.append(tag)
	tags_removed_on_end.append(tag)


func handle_physics_process(delta: float, manager: InteractionManager, interacted_node: Node) -> void:
	super.handle_physics_process(delta, manager, interacted_node)

	var movement := Input.get_vector("fps_strafe_left", "fps_strafe_right", "fps_move_forward", "fps_move_backward")

	if interacted_node is SailControl:
		interacted_node.sail.set_movement(movement)
