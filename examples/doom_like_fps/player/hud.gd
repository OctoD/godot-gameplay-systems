extends BoxContainer

## Note: this code is not the best practice. It should be handled separately without knowing it's own context.
## It's just for demonstration purpose.

@onready var item_log = $ItemLog
@onready var armor_bar: ProgressBar = $HBoxContainer/VBoxContainer/Armor
@onready var health_bar: ProgressBar = $HBoxContainer/VBoxContainer/Health
@onready var weapon_icon: TextureRect = $HBoxContainer/HBoxContainer/AspectRatioContainer/WeaponIcon


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


func _set_bar(progress_bar: ProgressBar, spec: AttributeSpec) -> void:
	progress_bar.max_value = spec.maximum_value
	progress_bar.min_value = spec.minimum_value
	progress_bar.value = spec.current_value
	

func equipment_tag_added(tag: String) -> void:
	_make_label(tag)


func handle_attribute_changed(spec: AttributeSpec) -> void:
	match spec.attribute_name:
		"health":
			_set_bar(health_bar, spec)
		"armor":
			_set_bar(armor_bar, spec)


func handle_equipped(item: DoomLikeFPSWeaponItem) -> void:
	if item:
		weapon_icon.texture = item.icon
