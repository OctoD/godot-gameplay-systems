extends InteractableArea3D


@export_node_path("Node3D") var sail_path := NodePath()

var sail: Node3D


func _ready() -> void:
	assert(not sail_path.is_empty(), "sails path must not be empty")
	
	sail = get_node(sail_path)
	
	assert(sail != null, "sail node not found")
