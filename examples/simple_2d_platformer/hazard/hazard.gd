extends EffectedArea2D


@onready var attributes: GameplayAttributeMap = $GameplayAttributeMap


func _ready() -> void:
	super._ready()
	
	attributes.attribute_changed.connect(func (attribute):
		if attribute.attribute_name == "health":
			if attribute.current_value == 0.0:
				queue_free()	
	)
	
