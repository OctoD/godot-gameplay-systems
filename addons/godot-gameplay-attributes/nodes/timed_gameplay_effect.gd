extends GameplayEffect
class_name TimedGameplayEffect


const MILLISECOND = 0.001
const SECOND = 1.0
const MINUTE = 60.0


@export_category("Timed gameplay effect")
@export_enum("Millisecond", "Second", "Minute") var tick_type : int = MILLISECOND
@export var activate_effect_every := 1.0
@export var one_shot := false


var _multiplier: float = 0.0:
	get:
		match tick_type:
			0: return MILLISECOND
			1: return SECOND
			2: return MINUTE
		return SECOND
var timer: Timer


func _ready():
	super._ready()
	activation_event = ActivationEvent.ON_ENTER_TREE
	instant = false
	_setup_timer()


func _enter_tree():
	super._enter_tree()
	_setup_timer()
	timer.start()


func _setup_timer() -> void:
	if not timer:
		timer = Timer.new()
		add_child(timer)
		timer.autostart = false
		timer.one_shot = one_shot
		timer.wait_time = _multiplier * activate_effect_every
		timer.timeout.connect(handle_timeout)


func handle_timeout() -> void:
	apply(ActivationEvent.ON_ENTER_TREE)

