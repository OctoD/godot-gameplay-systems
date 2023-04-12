class_name DoomLikeEnemy3D extends CharacterBody3D


signal died()


@onready var attributes: GameplayAttributeMap = $GameplayAttributeMap
@onready var collision_shape_3d: CollisionShape3D = $CollisionShape3D
@onready var inventory: Inventory = $Inventory


func _ready() -> void:
	attributes.attribute_changed.connect(func (attribute_spec: AttributeSpec):
		if attribute_spec.attribute_name == "health" and attribute_spec.current_value <= 0.0:
			dead()
	)


func dead() -> void:
	if is_queued_for_deletion():
		return
	
	var random_item = inventory.items.pick_random() as Item
	var item_to_drop = random_item.scene.instantiate()
	
	item_to_drop.position = position

	get_tree().root.add_child(item_to_drop)
	
	died.emit()

	get_parent().remove_child(self)
