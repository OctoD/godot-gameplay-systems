extends RestoreGameplayEffect
class_name RestoreHealthEffect

func setup_effect() -> void:
	.setup_effect()
	attribute_name = "Health"
	value = 10
