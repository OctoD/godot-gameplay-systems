class_name DiabloLikePassiveSkill extends DiabloLikeSkill


@export_category("Passive Skill")
@export var granted_effects: Array[GameplayEffect] = []


func activate(event: ActivationEvent) -> void:
	super.activate(event)

	if event.character != null:
		for effect in granted_effects:
			event.character.add_child(effect.duplicate())


func can_end(event: ActivationEvent) -> bool:
	if event.has_ability_container:
		return event.ability_container.tags.has(DiabloLikeSkill.DEAD_TAG)

	return super.can_end(event)
