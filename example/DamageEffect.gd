extends DamageGameplayEffect
class_name TestDamage

func setup_effect() -> void:
	.setup_effect()
	attribute_name = "Health"
	damage_min = 5
	damage_max = 10
