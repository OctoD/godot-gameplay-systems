class_name Drop2D extends Node2D


## Is a drop zone in a 2D world


# Emitted when items are dropped in this node.
signal item_dropped(item: Item, node: Node2D)


func _ready() -> void:	
	add_to_group("ggs.drop-node")
