extends BoxContainer


@onready var item_log = $ItemLog


func _make_label(text: String) -> void:
	var label = Label.new()
	var timer = Timer.new()
	
	label.text = text
	timer.autostart = true
	timer.one_shot = true
	timer.timeout.connect(func ():
		label.queue_free()
	)
	
	label.add_child(timer)
	item_log.add_child(label)


func equipment_tag_added(tag: String) -> void:
	_make_label(tag)
