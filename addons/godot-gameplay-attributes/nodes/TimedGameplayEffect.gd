tool
extends GameplayEffect
class_name TimedGameplayEffect

enum DurationType {
	Milliseconds,
	Seconds,
	Minutes,
}

export(int) var duration = 1
export(DurationType) var duration_type = DurationType.Seconds
export(DurationType) var apply_effect_every = DurationType.Seconds

var timer: Timer
var ticks_left = 0
var single_tick = 0

func _get_tick_unit(type: int) -> int:
	match (type):
		DurationType.Milliseconds:
			return 1
		DurationType.Seconds:
			return 1000
		DurationType.Minutes:
			return 6000
		_:
			return 0

func _get_timer_wait_time() -> float:
	return 0.001 * float(_get_tick_unit(apply_effect_every))

func _get_max_ticks() -> int:
	return duration * _get_tick_unit(duration_type)

func _should_apply_effect() -> bool:
	return ticks_left % single_tick == 0

func play_effect() -> void:
	if timer.is_stopped():
		timer.start()

func pause_effect() -> void:
	timer.stop()


func setup_effect() -> void:
	.setup_effect()
	ticks_left = _get_max_ticks()
	single_tick = _get_tick_unit(apply_effect_every)
	timer = Timer.new()
	timer.wait_time = _get_timer_wait_time()
	timer.connect("timeout", self, "_on_timer_ticked")

	add_child(timer)


func _on_timer_ticked() -> void:
	if should_deactivate():
		queue_free()

	ticks_left -= single_tick
	if _should_apply_effect():
		apply_effect()


func should_activate(activation_event: int) -> bool:
	if activation_event == EffectActivationEvent.ImmediateActivation:
		if timer.is_stopped() and is_inside_tree():
			timer.start()
	  
		emit_signal("effect_activated", self)
		
		return true

	return false


func should_deactivate() -> bool:
	if duration != 0 and ticks_left == 0:
		emit_signal("effect_deactivated", self)
		return true
	else:
		return false
