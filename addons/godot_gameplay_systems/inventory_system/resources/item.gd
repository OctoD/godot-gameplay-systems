@tool
class_name Item extends Resource


signal activated(item: Item, activation_type: int)


@export_category("Item")
## Name given to this item.
## [br]Use it just for your internal purpose, you should use a dictionary of name->i18n values for multilanguage purpose
@export var name: StringName = ""

@export_group("Tags", "tags")
## The tags associated to an item. 
## [br]Use them to describe 
@export var tags: Array[String] = []
## Tags which the item requires in order to be activated.
## [br]If the [member Item.tags] array is empty but the [member Item.tags_required_for_activation] is not, the item will never be activated and will log an error.
## [br]Note: all tags specified are required
@export var tags_required_for_activation: Array[String] = []


## Returns if the item has the right tags to be activated
func can_activate() -> bool:
	if tags.is_empty() and tags_required_for_activation.is_empty():
		return true
	elif tags.is_empty() and not tags_required_for_activation.is_empty():
		printerr("Item cannot be activated since Item.tags are empty but tags_required_for_activation are not. Item is ", self)
		return false
	else:
		for t in tags_required_for_activation:
			if not tags.has(t):
				return false
		return true


## Tries to activate the item
func try_activate(activation_type: int = 0) -> void:
	if can_activate():
		if has_method("activate"):
			call("activate", activation_type)
		
		activated.emit(self, activation_type)

