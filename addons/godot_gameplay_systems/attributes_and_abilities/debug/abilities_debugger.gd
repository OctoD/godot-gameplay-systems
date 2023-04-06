extends Control

@export_category("Debug UI")
@export_node_path("AbilityContainer") var ability_container_path := NodePath()
@export var persist_messages_for := 15.0


@onready var ability_container: AbilityContainer
@onready var labels: VBoxContainer = $Labels
@onready var timer: Timer = $Timer


func _ready() -> void:
	ability_container = get_node(ability_container_path) as AbilityContainer
	
	timer.timeout.connect(func ():
		var children = labels.get_children()
		
		if children:
			labels.remove_child(children[0])
	)
	
	assert(ability_container != null, "ability_container is null")
	
	ability_container.ability_activated.connect(_handle_activated)
	ability_container.ability_blocked.connect(_handle_blocked)
	ability_container.ability_cancelled.connect(_handle_cancelled)
	ability_container.ability_ended.connect(_handle_ended)
	ability_container.ability_granted.connect(_handle_granted)
	ability_container.ability_revoked.connect(_handle_revoked)
	ability_container.cooldown_started.connect(_handle_cooldown_started)
	ability_container.cooldown_ended.connect(_handle_cooldown_ended)


func _handle_activated(ability: Ability, e: ActivationEvent) -> void:
	_make_label("activated", ability, e)


func _handle_blocked(ability: Ability, e: ActivationEvent) -> void:
	_make_label("blocked", ability, e)


func _handle_cancelled(ability: Ability, e: ActivationEvent) -> void:
	_make_label("cancelled", ability, e)


func _handle_cooldown_ended(ability: Ability) -> void:
	_make_label("cooldown_ended", ability, ActivationEvent.new(ability_container))


func _handle_cooldown_started(ability: Ability) -> void:
	_make_label("cooldown_started", ability, ActivationEvent.new(ability_container))


func _handle_ended(ability: Ability, e: ActivationEvent) -> void:
	_make_label("ended", ability, e)


func _handle_granted(ability: Ability) -> void:
	_make_label("granted", ability, ActivationEvent.new(ability_container))


func _handle_revoked(ability: Ability) -> void:
	_make_label("revoked", ability, ActivationEvent.new(ability_container))


func _make_label(event: String, ability: Ability, e: ActivationEvent) -> void:
	var label = Label.new()
	var timer = Timer.new()
	
	timer.one_shot = true
	timer.wait_time = persist_messages_for
	
	label.text = "{0} is {1} with tags {2}".format({
		"0": ability.ui_name,
		"1": event,
		"2": str(e.tags)
	})
	
	labels.add_child(label)
	
