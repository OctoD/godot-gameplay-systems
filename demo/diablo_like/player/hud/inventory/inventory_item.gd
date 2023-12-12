extends TextureRect

@export var item: DiabloLikeItem


@onready var label: Label = $Label


func set_item(_item: Item) -> void:
	if _item:
		texture = _item.ui_icon
		label.text = str(_item.quantity_current)
		self.item = _item
