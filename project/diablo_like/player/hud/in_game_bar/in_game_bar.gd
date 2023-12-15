class_name DiabloLikeInGameBar extends HBoxContainer


@onready var health: ProgressBar = $HealthMana/Health
@onready var mana: ProgressBar = $HealthMana/Mana
@onready var skill_1 = $SelectedSkills/Skill0
@onready var skill_2 = $SelectedSkills/Skill1
@onready var skill_3 = $SelectedSkills/Skill2
@onready var skill_4 = $SelectedSkills/Skill3


func _set_progress_bar(bar: ProgressBar, attribute_spec: AttributeSpec) -> void:
	if attribute_spec == null:
		return
	
	bar.min_value = attribute_spec.minimum_value
	bar.max_value = attribute_spec.maximum_value
	bar.value = attribute_spec.current_value


func activate_ability_on_slot(slot_number: int) -> void:
	match slot_number:
		1: skill_1.activate()
		2: skill_1.activate()
		3: skill_1.activate()
		4: skill_1.activate()


func handle_ability_activated(_ability: Ability) -> void:
	pass


func handle_ability_granted(_skill: Ability) -> void:
	pass


func setup_ability_container(ability_container: AbilityContainer) -> void:
	ability_container.ability_activated.connect(handle_ability_activated)
	ability_container.ability_granted.connect(handle_ability_granted)

	for child in $SelectedSkills.get_children():
		child.ability_container = ability_container


func setup_gameplay_attribute_map(gameplay_attribute_map: GameplayAttributeMap) -> void:
	const health_attribute_name = "health"
	const mana_attribute_name = "mana"
	
	gameplay_attribute_map.attribute_changed.connect(func (attribute_spec: AttributeSpec) -> void:
		match attribute_spec.attribute_name:
			health_attribute_name:
				_set_progress_bar(health, attribute_spec)
			mana_attribute_name:
				_set_progress_bar(mana, attribute_spec)
	)
	
	# initial setup
	_set_progress_bar(health, gameplay_attribute_map.get_attribute_by_name(health_attribute_name))
	_set_progress_bar(mana, gameplay_attribute_map.get_attribute_by_name(mana_attribute_name))

