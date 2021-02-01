tool
extends GameplayEffect
class_name TimedGameplayEffect


export(int) var duration = 1


var ticks_performed = 0
var timer: Timer


func setup_effect() -> void:
	.setup_effect()
	timer = Timer.new()
	timer.connect("timeout", self, "_on_timer_ticked")

	add_child(timer)


func _on_timer_ticked() -> void:
	if duration == 0:
		return
  
	ticks_performed += 1


func should_activate(activation_event: int) -> bool:
	if activation_event == EffectActivationEvent.ImmediateActivation:
		if timer.is_stopped():
			timer.start()
	  
		return true

	return false


func should_deactivate() -> bool:
	if duration != 0 and duration == ticks_performed:
		return true
	else:
		return false
