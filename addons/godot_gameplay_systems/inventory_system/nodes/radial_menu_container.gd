@tool
extends Container


func _draw() -> void:
	var child_count = get_child_count()
	var pie_slice_radians = 2 * PI / child_count
	var child_index = 0

	for child in get_children():
		if child is Control:
			# move child to a pie slice starting from the center of the container
			var child_angle = child_index * pie_slice_radians
			var child_radius = min(size.x, size.y) / 2
			var child_position = Vector2(
				child_radius * cos(child_angle),
				child_radius * sin(child_angle)
			)

			child_position.x += size.x / 2 - child.size.x / 2
			child_position.y += size.y / 2 - child.size.y / 2

			child.set_position(child_position)

			child_index += 1


func _enter_tree() -> void:
	child_entered_tree.connect(_handle_child_entered_tree)
	child_exiting_tree.connect(_handle_child_exiting_tree)


func _handle_child_entered_tree(child: Node) -> void:
	_draw()


func _handle_child_exiting_tree(child: Node) -> void:
	_draw()


func _process(delta: float) -> void:
	if Engine.is_editor_hint():
		_draw()