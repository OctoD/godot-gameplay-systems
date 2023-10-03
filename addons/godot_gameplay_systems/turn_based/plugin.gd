extends EditorPlugin


const TurnBasedGameScript = preload("./nodes/TurnBasedGame.gd")
const TurnSubscriberScript = preload("./nodes/TurnSubscriber.gd")


func _enter_tree() -> void:
	add_autoload_singleton("TurnManager", "./autoloads/turn_manager.gd")
	add_custom_type("TurnBasedGame", "Node", TurnBasedGameScript, null)
	add_custom_type("TurnSubscriber", "Node", TurnSubscriberScript, null)


func _exit_tree() -> void:
	remove_autoload_singleton("TurnManager")
	remove_custom_type("TurnBasedGame")
	remove_custom_type("TurnSubscriber")

