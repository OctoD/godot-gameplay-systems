extends Control


func _ready() -> void:
	print(ItemManager.get_items())
	print(EquipmentManager.get_slots())
	pass

