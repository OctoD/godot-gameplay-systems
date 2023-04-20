extends GutTest


const health_attribute_name = "health"


var owner_path: NodePath = NodePath()
var owner_character: CharacterBody2D


func _make_attribute_effect(minimum_value: float, maximum_value: float) -> AttributeEffect:
	var af = AttributeEffect.new()
	
	af.attribute_name = health_attribute_name
	af.minimum_value = minimum_value
	af.maximum_value = maximum_value
	
	return af


func _make_effect(minimum_value: float, maximum_value: float) -> GameplayEffect:
	var ge = GameplayEffect.new()
	var af = _make_attribute_effect(minimum_value, maximum_value)
	
	ge.attributes_affected.append(af)
	
	return ge


func _make_gam() -> GameplayAttributeMap:
	owner_character = CharacterBody2D.new()
	
	add_child_autofree(owner_character)
	
	owner_path = owner_character.get_path()
	
	var gam = GameplayAttributeMap.new()
	var attribute_table = AttributeTable.new()
	var attribute = AttributeResource.new()
	
	attribute_table.attributes.append(health_attribute_name)
	attribute.attribute_name = health_attribute_name
	attribute.current_value = 100
	attribute.maximum_value = 100
	attribute.minimum_value = 0
	
	gam.owning_character = owner_path
	gam.table = attribute_table
	gam.attributes.append(attribute)

	add_child_autofree(gam)
	watch_signals(gam)
	
	return gam


func after_each() -> void:
	clear_signal_watcher()


func test_has_owner_character() -> void:
	assert_ne(_make_gam().owning_character, null, "owning character should not be null")


func test_attribute_dict() -> void:
	var gam = _make_gam()
	
	assert_eq(gam._attributes_dict.has(health_attribute_name), true, "attribute dict should have health")
	
	var attr = gam._attributes_dict.get(health_attribute_name)
	
	assert_eq(attr.current_value, 100, "health should have current_value set to 100")
	assert_eq(attr.maximum_value, 100, "health should have maximum_value set to 100")
	assert_eq(attr.minimum_value, 0, "health should have minimum_value set to 0")


func test_attribute_getter() -> void:
	var gam = _make_gam()
	
	assert_ne(gam.get_attribute_by_name(health_attribute_name), null, "attribute should have been found")
	assert_eq(gam.get_attribute_by_name(health_attribute_name).current_value, 100, "attribute should have value set")

	
func test_attribute_change() -> void:
	var gam = _make_gam()
	var effect = GameplayEffect.new()
	var attribute_effect = _make_attribute_effect(-5, -5)
	
	effect.attributes_affected.append(attribute_effect)

	owner_character.add_child(effect)

	assert_signal_emitted(gam, "attribute_changed", "attribute_changed should have been called")
	assert_eq(gam._attributes_dict[health_attribute_name].current_value, 95, "attribute should have been modified by the effect")
	assert_eq(owner_character.get_children().has(attribute_effect), false, "gameplay_effect node should have been removed from owner_character")

	gam.apply_effect(effect)
	
	assert_eq(gam._attributes_dict[health_attribute_name].current_value, 90, "attribute should have been modified by the effect")


func test_lifetimed_effects() -> void:
	var gam = _make_gam()
	var effect = _make_effect(-10, -10)
	var attr = effect.attributes_affected[0] as AttributeEffect
	
	attr.life_time = 1
	attr.max_applications = 2
	
	gam.apply_effect(effect)

	await wait_seconds(5)

	assert_signal_emit_count(gam, "attribute_changed", 2, "attribute_changed should have been called only twice")
	assert_eq(gam.get_attribute_by_name(health_attribute_name).current_value, 80, "effect should have been applied twice")

