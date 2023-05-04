@tool
class_name Drop extends Node

## It is the node responsible for dropping an array of [Items].
##

## Emitted when some [Item]s have been dropped.
signal items_dropped(items: Array[Item], drop_owner: Node)


@export_category("Drop")
## The table used to drop items
@export var drop_table: DropTable = null
## The path to the owning node. This will determine if the drop will be performed in a 2D or 3D world.
## [br]Note that the drop will occur at the same position of the owning node.
@export_node_path("Node2D", "Node3D") var owning_node_path := NodePath()


## It could be either a [Node2D] or [Node3D]
var owning_node: Variant:
	get:
		if owning_node_path != null and not owning_node_path.is_empty():
			return get_node(owning_node_path)
		return null


## Called when some [Item]s have been dropped.
func _drop(items: Array[Item]) -> void:
	var instances: Array[Node] = []
	var _owning_node = owning_node

	if _owning_node == null:
		return

	for item in items:
		if item.scene and item.scene.can_instantiate():
			var instance = item.scene.instantiate()
			var nearest_drop = find_nearest_drop()

			instance.position = _owning_node.position

			if nearest_drop:
				nearest_drop.add_child(instance)
				nearest_drop.item_dropped.emit(item, instance)


## It gets the droppable [Item]s from the [DropTable].
## [br]It accepts an optional argument [code]drop_modifier[/code] which increases (or decreases if negative) drop chances for each [DropGroup] pool.
## [br]The greater the modifier, the higher the chances to drop an [Item] from the [member DropTable.pools].
func drop_items(drop_modifier: float = 0.0) -> void:
	var items = drop_table.drop(drop_modifier)

	if items.size() > 0:
		# Who knows what happens in this method. Let's await it.
		await _drop(items)

		items_dropped.emit(items)


## Finds the nearest [Drop2D] or [Drop3D] node.
## [br]This could be useful in a world-partitioned scenario (like open world rpgs).
func find_nearest_drop() -> Node:
	var owner_node = owning_node

	if owner_node == null:
		return null

	# gets all dropzones
	var dropzones = get_tree().get_nodes_in_group("ggs.drop-node").duplicate()
	var position = owner_node.position
	var is_2d = (owner_node as Node2D) != null
	var is_3d = (owner_node as Node3D) != null
	
	if dropzones.size() == 0:
		return null


	# the sorting function, we will take the nearest [Drop2D] or [Drop3D] node.
	dropzones.sort_custom(func (a: Variant, b: Variant) -> bool:
		if a is Node2D and b is Node2D and is_2d:
			return b.position.distance_to(position) > a.position.distance_to(position)
		elif a is Node3D and b is Node3D and is_3d:
			return b.position.distance_to(position) > a.position.distance_to(position)

		return false
	)

	return dropzones[0]

