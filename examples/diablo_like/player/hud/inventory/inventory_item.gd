extends TextureRect

@export var item: DiabloLikeItem


@onready var label: Label = $Label


func set_item(_item: Item) -> void:
	if item:
		texture = item.ui_icon
		label.text = str(item.quantity_current)
		self.item = item
