extends EditorPlugin


const TurnBasedGameScript = preload("res://addons/godot_gameplay_systems/turn_based/nodes/TurnBasedGame.gd")
const TurnSubscriberScript = preload("res://addons/godot_gameplay_systems/turn_based/nodes/TurnSubscriber.gd")


func _enter_tree() -> void:
	add_autoload_singleton("TurnManager", "res://addons/godot_gameplay_systems/turn_based/autoloads/turn_manager.gd")
	add_custom_type("TurnBasedGame", "Node", TurnBasedGameScript, null)
	add_custom_type("TurnSubscriber", "Node", TurnSubscriberScript, null)


func _exit_tree() -> void:
	remove_autoload_singleton("TurnManager")
	remove_custom_type("TurnBasedGame")
	remove_custom_type("TurnSubscriber")

