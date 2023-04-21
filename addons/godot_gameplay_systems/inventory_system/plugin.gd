extends EditorPlugin


const equipment_script = preload("res://addons/godot_gameplay_systems/inventory_system/nodes/equipment.gd")
const equipped_item_3d = preload("res://addons/godot_gameplay_systems/inventory_system/nodes/equipped_item_3d.gd")
const inventory_script = preload("res://addons/godot_gameplay_systems/inventory_system/nodes/inventory.gd")
const item_script = preload("res://addons/godot_gameplay_systems/inventory_system/resources/item.gd")
const item_activation_event_script = preload("res://addons/godot_gameplay_systems/inventory_system/objects/item_activation_event.gd")
const pickable_item_2d = preload("res://addons/godot_gameplay_systems/inventory_system/nodes/pickable_item_2d.gd")
const pickable_item_3d = preload("res://addons/godot_gameplay_systems/inventory_system/nodes/pickable_item_3d.gd")


func _enter_tree() -> void:
	add_custom_type("Item", "Resource", item_script, preload("res://addons/godot_gameplay_systems/inventory_system/assets/ItemIcon.png"))
	add_custom_type("ItemActivationEvent", "RefCounted", item_activation_event_script, null)
	add_custom_type("Inventory", "Node", inventory_script, preload("res://addons/godot_gameplay_systems/inventory_system/assets/InventoryIcon.png"))
	add_custom_type("Equipment", "Node", equipment_script, preload("res://addons/godot_gameplay_systems/inventory_system/assets/EquipmentIcon.png"))
	add_custom_type("EquippedItem3D", "Node3D", equipped_item_3d, preload("res://addons/godot_gameplay_systems/inventory_system/assets/Equipped3DIcon.png"))
	add_custom_type("PickableArea2D", "Area2D", pickable_item_2d, null)
	add_custom_type("PickableArea3D", "Area3D", pickable_item_3d, null)


func _exit_tree() -> void:
	remove_custom_type("PickableArea3D")
	remove_custom_type("PickableArea2D")
	remove_custom_type("EquippedItem3D")
	remove_custom_type("Equipment")
	remove_custom_type("Inventory")
	remove_custom_type("ItemActivationEvent")
	remove_custom_type("Item")

