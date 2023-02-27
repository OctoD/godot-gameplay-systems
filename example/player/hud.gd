extends Control


@onready var health = $HBoxContainer/Health
@onready var score = $HBoxContainer/Score


func initialize(map: GameplayAttributeMap) -> void:
	handle_attribute_changed(map.get_attribute_by_name("health"))
	handle_attribute_changed(map.get_attribute_by_name("score"))


func handle_attribute_changed(spec: GameplayAttributeMap.AttributeSpec) -> void:
	match spec.attribute_name:
		"health":
			set_health(spec.current_value)
		"score":
			set_score(spec.current_value)


func set_health(value: float = 0.0) -> void:
	health.text = "Health: {0}".format({"0": str(value)})


func set_score(value: float = 0.0) -> void:
	score.text = "Score: {0}".format({"0": str(value)})

