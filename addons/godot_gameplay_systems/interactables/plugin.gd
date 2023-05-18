extends EditorPlugin


func _enter_tree() -> void:
	add_custom_type("InteractableArea2D", "Area2D", load("res://addons/godot_gameplay_systems/interactables/nodes/2d/interactable_area_2d.gd"), load("res://addons/godot_gameplay_systems/interactables/assets/InteractableArea2D.png"))
	add_custom_type("InteractableArea3D", "Area3D", load("res://addons/godot_gameplay_systems/interactables/nodes/3d/interactable_area_3d.gd"), load("res://addons/godot_gameplay_systems/interactables/assets/InteractableArea2D.png"))
	add_custom_type("InteractionRayCast2D", "RayCast2D", load("res://addons/godot_gameplay_systems/interactables/nodes/2d/interaction_raycast_2d.gd"), load("res://addons/godot_gameplay_systems/interactables/assets/InteractionRayCast2DIcon.png"))
	add_custom_type("InteractionRayCast3D", "RayCast3D", load("res://addons/godot_gameplay_systems/interactables/nodes/3d/interaction_raycast_3d.gd"), load("res://addons/godot_gameplay_systems/interactables/assets/InteractionRayCast3DIcon.png"))
	add_custom_type("InteractionManager", "Node", load("res://addons/godot_gameplay_systems/interactables/nodes/interaction_manager.gd"), load("res://addons/godot_gameplay_systems/interactables/assets/InteractionIcon.png"))
	add_custom_type("Interaction", "Resource", load("res://addons/godot_gameplay_systems/interactables/resources/interaction.gd"), load("res://addons/godot_gameplay_systems/interactables/assets/InteractionIcon.png"))


func _exit_tree() -> void:
	remove_custom_type("Interaction")
	remove_custom_type("InteractionManager")
	remove_custom_type("InteractableArea2D")
	remove_custom_type("InteractableArea3D")
	remove_custom_type("InteractionRayCast2D")
	remove_custom_type("InteractionRayCast3D")

