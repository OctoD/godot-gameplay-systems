extends GutTest


const drop_scene = preload("res://addons/godot_gameplay_systems/inventory_system/test/unit/fixtures/test_drop_scene.tscn")


var level = Node2D.new()


func after_all():
	level = null
	clear_signal_watcher()


func before_all():
	level = Node2D.new()
	
	add_child_autofree(level)


func make_drop_2d(x: float, y: float) -> Drop2D:
	var d2d = Drop2D.new()

	level.add_child(d2d)
	d2d.position = Vector2(x, y)

	watch_signals(d2d)

	return d2d


func make_foe(x: float, y: float) -> Node2D:
	var foe = drop_scene.instantiate()
	
	foe.position = Vector2(x, y)
	add_child_autofree(foe)

	return foe


func test_drop() -> void:
	var drop_2d_000 = make_drop_2d(10.0, 10.0)
	var drop_2d_001 = make_drop_2d(5.0, 5.0)
	var drop_2d_002 = make_drop_2d(2.5, 2.5)
	var drop_2d_003 = make_drop_2d(0.0, 0.0)

	var foe_000 = make_foe(7, 7)
	var foe_001 = make_foe(8, 8)

	watch_signals(foe_000.drop)

	foe_000.die()
	foe_001.die()

	assert_signal_emitted(foe_000.drop, "items_dropped")

	assert_eq(drop_2d_000.get_child_count(), 1, "item should have been dropped here since it's the nearest drop point to foe_001")
	assert_eq(drop_2d_001.get_child_count(), 1, "item should have been dropped here since it's the nearest drop point to foe_000")
	assert_eq(drop_2d_002.get_child_count(), 0, "item should have not been dropped here since it's far from foes")
	assert_eq(drop_2d_003.get_child_count(), 0, "item should have not been dropped here since it's far from foes")
