class_name Drop3D extends Node3D

## Is a drop zone in a 3D world


# Emitted when items are dropped in this node.
signal item_dropped(item: Item, node: Node3D)


func _ready() -> void:	
	add_to_group("ggs.drop-node")
