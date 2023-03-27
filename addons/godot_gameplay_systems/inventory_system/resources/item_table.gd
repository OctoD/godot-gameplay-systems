@tool
class_name ItemTable extends Resource


@export_category("Item table")
## A list of items bound to this table.
@export var items: Array[Item] = []


func filter_by_tags(tags: Array[String], match_all: bool = false) -> Array[Item]:
	var filtered: Array[Item] = []

	for item in items:
		if not item.tags.is_empty():
			if match_all:
				var count := 0
				
				for tag in tags:
					if item.tags.has(tag):
						count += 1
						
				if count == tags.size():
					filtered.append(item)
			else:
				for tag in tags:
					if item.tags.has(tag):
						filtered.append(item)

	return filtered
