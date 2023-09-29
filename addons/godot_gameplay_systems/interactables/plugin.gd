extends EditorPlugin


func _enter_tree() -> void:
	add_custom_type("InteractableArea2D", "Area2D", load("./nodes/2d/interactable_area_2d.gd"), load("./assets/InteractableArea2D.png"))
	add_custom_type("InteractableArea3D", "Area3D", load("./nodes/3d/interactable_area_3d.gd"), load("./assets/InteractableArea2D.png"))
	add_custom_type("InteractionRayCast2D", "RayCast2D", load("./nodes/2d/interaction_raycast_2d.gd"), load("./assets/InteractionRayCast2DIcon.png"))
	add_custom_type("InteractionRayCast3D", "RayCast3D", load("./nodes/3d/interaction_raycast_3d.gd"), load("./assets/InteractionRayCast3DIcon.png"))
	add_custom_type("InteractionManager", "Node", load("./nodes/interaction_manager.gd"), load("./assets/InteractionIcon.png"))
	add_custom_type("Interaction", "Resource", load("./resources/interaction.gd"), load("./assets/InteractionIcon.png"))


func _exit_tree() -> void:
	remove_custom_type("Interaction")
	remove_custom_type("InteractionManager")
	remove_custom_type("InteractableArea2D")
	remove_custom_type("InteractableArea3D")
	remove_custom_type("InteractionRayCast2D")
	remove_custom_type("InteractionRayCast3D")

