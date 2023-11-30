extends EditorPlugin


func _enter_tree() -> void:
	add_custom_type("InteractableArea2D", "Area2D",preload("./nodes/2d/interactable_area_2d.gd"),preload("./assets/InteractableArea2D.png"))
	add_custom_type("InteractableArea3D", "Area3D",preload("./nodes/3d/interactable_area_3d.gd"),preload("./assets/InteractableArea2D.png"))
	add_custom_type("InteractionRayCast2D", "RayCast2D",preload("./nodes/2d/interaction_raycast_2d.gd"),preload("./assets/InteractionRayCast2DIcon.png"))
	add_custom_type("InteractionRayCast3D", "RayCast3D",preload("./nodes/3d/interaction_raycast_3d.gd"),preload("./assets/InteractionRayCast3DIcon.png"))
	add_custom_type("InteractionManager", "Node",preload("./nodes/interaction_manager.gd"),preload("./assets/InteractionIcon.png"))
	add_custom_type("Interaction", "Resource",preload("./resources/interaction.gd"),preload("./assets/InteractionIcon.png"))


func _exit_tree() -> void:
	remove_custom_type("Interaction")
	remove_custom_type("InteractionManager")
	remove_custom_type("InteractableArea2D")
	remove_custom_type("InteractableArea3D")
	remove_custom_type("InteractionRayCast2D")
	remove_custom_type("InteractionRayCast3D")

