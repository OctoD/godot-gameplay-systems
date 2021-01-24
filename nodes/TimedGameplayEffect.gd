tool
extends "res://addons/gameplay_attributes/nodes/GameplayEffect.gd"
class_name TimedGameplayEffect


var timer: Timer


func _ready():
  .connect_to_parent_signal()
  timer = Timer.new()
  add_child(timer)


# func apply_effect(attribute_name: String, attribute_type: String, attribute_value: float) -> void:
#   if _active
  
#     pass