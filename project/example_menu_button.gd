class_name ExampleButton extends Button


signal scene_selected(node)


@export_category("Example")
@export_file("*.tscn") var scene_to_load



func _ready() -> void:
	pressed.connect(func ():
		if scene_to_load != null:
			var scene = load(scene_to_load) as PackedScene
			
			if scene and scene.can_instantiate():
				scene_selected.emit(scene.instantiate())
	)
