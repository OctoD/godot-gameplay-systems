extends Node2D

onready var attributes = $KinematicBody2D/GameplayAttributeMap
onready var healthlabel = $KinematicBody2D/Control/Health
onready var manalabel = $KinematicBody2D/Control/Mana


func _ready() -> void:
	_set_health_label()
	_set_mana_label()


func _unhandled_input(event: InputEvent) -> void:
	if Input.is_action_pressed("consumehealth"):
		attributes.add_child(TestDamage.new())
	if Input.is_action_pressed("consumemana"):
		attributes.get_attribute("Mana").current_value -= 50
	if Input.is_action_pressed("heal"):
		attributes.add_child(RestoreHealthEffect.new())
	get_tree().set_input_as_handled()


func _set_health_label() -> void:
	healthlabel.text = "Health: " + str(attributes.get_attribute_value("Health"))


func _set_mana_label() -> void:
	manalabel.text = "Mana: " + str(attributes.get_attribute_value("Mana"))


func _on_GameplayAttributeMap_attribute_changed(attribute) -> void:
	print(attribute)
	if attribute.name == "Health":
		_set_health_label()
	elif attribute.name == "Mana":
		_set_mana_label()
