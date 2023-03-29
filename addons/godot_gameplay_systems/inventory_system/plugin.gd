extends EditorPlugin


const inventory_script = preload("res://addons/godot_gameplay_systems/inventory_system/nodes/inventory.gd")
const item_script = preload("res://addons/godot_gameplay_systems/inventory_system/resources/item.gd")
const item_activation_event_script = preload("res://addons/godot_gameplay_systems/inventory_system/objects/item_activation_event.gd")

func _enter_tree() -> void:
	add_custom_type("Item", "Resource", item_script, preload("res://addons/godot_gameplay_systems/inventory_system/assets/ItemIcon.png"))
	add_custom_type("ItemActivationEvent", "RefCounted", item_activation_event_script, null)
	add_custom_type("Inventory", "Node", inventory_script, preload("res://addons/godot_gameplay_systems/inventory_system/assets/InventoryIcon.png"))

func _exit_tree() -> void:
	remove_custom_type("Inventory")
	remove_custom_type("ItemActivationEvent")
	remove_custom_type("Item")
