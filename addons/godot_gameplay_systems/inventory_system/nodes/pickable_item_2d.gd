@tool
extends Area2D


## It represents an [Item] which can be picked in a 2D world.


@export_category("Item Pick")
## Automatically triggers a pick if the collision layer hits this area.
@export var automatically_pick: bool = false
## The item to pick.
@export var item: Item = null:
	get:
		return item
	set(value):
		item = value
		_render()


## A reference to the rendered [Item].
var rendered_item: Node2D


## Handles the collision
func _handle_collision(body: Node2D) -> void:
	if automatically_pick:
		if body.has_meta("ggsInventory"):
			pick(body.get_meta("ggsInventory", null))
		elif body.has_meta("ggsEquipment"):
			pick(body.get_meta("ggsEquipment", null))


## Renders the bound [Item] only if it has a valid [member Item.scene] member.
func _render() -> void:
	if item and item.scene and item.scene.can_instantiate():
		if rendered_item:
			rendered_item.queue_free()
		
		rendered_item = item.scene.instantiate()
		add_child(rendered_item)


func _ready() -> void:
	if not Engine.is_editor_hint():
		area_entered.connect(_handle_collision)
		body_entered.connect(_handle_collision)


## Triggers the pick mechanism programmatically.
func pick(by: Node) -> void:
	assert(item != null, "item should not be null")

	if by is Inventory:
		if by.can_add(item):
			by.add_item(item)
			queue_free()
	elif by is Equipment:
		## Adds tags because it "picked" the item.
		by.add_tags(item.tags_added_on_add)

		for slot in by.slots:
			if slot.can_equip(item):
				slot.equip(item)

		queue_free()

