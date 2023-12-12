class_name DoomLikeEnemy3D extends CharacterBody3D


signal died()


@onready var attributes: GameplayAttributeMap = $GameplayAttributeMap
@onready var collision_shape_3d: CollisionShape3D = $CollisionShape3D
@onready var drop: Drop = $Drop


func _ready() -> void:
	attributes.attribute_changed.connect(func (attribute_spec: AttributeSpec):
		if attribute_spec.attribute_name == "health" and attribute_spec.current_value <= 0.0:
			dead()
	)
	
	drop.items_dropped.connect(func (items): print(items))


func dead() -> void:
	if is_queued_for_deletion():
		return
	
	drop.drop_items()
	died.emit()

	get_parent().remove_child(self)
