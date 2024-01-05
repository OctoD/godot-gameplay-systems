extends Node


func _ready() -> void:
	TagDictionary.new()
	
	var a = Attribute.new()
	var x = AttributeEffect.new()
	var y = AttributeEffectCondition.new()	
	
	x.conditions.append(y)
