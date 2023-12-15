extends Control


@onready var health: Label = $HBoxContainer/Health
@onready var score: Label = $HBoxContainer/Score
@onready var tags: Label = $"DebugTags"


func initialize_abilities(container: AbilityContainer) -> void:
	container.tags_updated.connect(func (list: Array[String]):
		tags.text = str(list)
	)


func initialize_attributes(map: GameplayAttributeMap) -> void:
	handle_attribute_changed(map.get_attribute_by_name("health"))
	handle_attribute_changed(map.get_attribute_by_name("score"))


func handle_attribute_changed(spec: AttributeSpec) -> void:
	match spec.attribute_name:
		"health":
			set_health(spec.current_value)
		"score":
			set_score(spec.current_value)


func set_health(value: float = 0.0) -> void:
	health.text = "Health: {0}".format({"0": str(value)})


func set_score(value: float = 0.0) -> void:
	score.text = "Score: {0}".format({"0": str(value)})

