class_name DropGroup extends Resource

## Represents a drop rule.
##
## 

@export_category("Drop")
## Represents the pool of droppable [Item]s.
@export var items_pool: Array[Item] = []
## Represents the chance of dropping one item from the [member DropGroup.items_pool] pool.
## [br]The higher the value, the higher the chances.
@export_range(0.0, 100.0, 0.01) var drop_chance: float = 50.0


## Returns if the group can drop an item from the [member DropGroup.items_pool] pool.
## [br]It accepts an optional argument [code]drop_modifier[/code] which increases (or decreases if negative) drop chances.
## [br]The greater the modifier, the higher the chances to drop an [Item] from the pool.
func can_be_dropped(modifier: float = 0.0) -> bool:
	return drop_chance + modifier >= randf_range(0.0, 100.0)


## Drops an [Item]. 
## [br]If the drop is unsuccessfull, it returns [code]null[/code].
## [br]It accepts an optional argument [code]drop_modifier[/code] which increases (or decreases if negative) drop chances.
## [br]The greater the modifier, the higher the chances to drop an [Item] from the pool.
func drop(drop_modifier: float = 0.0) -> Item:
	if can_be_dropped(drop_modifier):
		return items_pool.pick_random()

	return null
