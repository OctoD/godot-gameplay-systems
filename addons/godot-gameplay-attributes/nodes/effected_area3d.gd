@tool
class_name EffectedArea3D extends Area3D


@export_category("Gameplay Effect Handling")
@export var remove_self_on_apply := true
@export var remove_effects_on_apply := true


var effects: Array[GameplayEffect] = []:
	get:
		var _effects: Array[GameplayEffect] = []
		
		for child in get_children():
			if child is GameplayEffect:
				_effects.append(child)
		
		return _effects


func _ready() -> void:
	if not Engine.is_editor_hint():
		body_entered.connect(func (body: Node3D):
			if should_apply_effect(body):
				for effect in effects:
					if remove_effects_on_apply:
						remove_child(effect)
						body.add_child(effect)
					else:
						body.add_child(effect.duplicate())

				if remove_self_on_apply:
					queue_free()
		)


func should_apply_effect(node: Node3D) -> bool:
	return true
