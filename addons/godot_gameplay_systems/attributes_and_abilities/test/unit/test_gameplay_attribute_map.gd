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
	effect
	owner_character.add_child(effect)

	assert_signal_emitted(gam, "attribute_changed", "attribute_changed should have been called")
	assert_eq(gam._attributes_dict[health_attribute_name].current_value, 95, "attribute should have been modified by the effect")

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


func test_buff_and_debuff() -> void:
	var gam = _make_gam()
	var effect = _make_effect(5, 5)
	var attr = gam.get_attribute_by_name(health_attribute_name)
	var damage_effect = _make_effect(-10, -10)

	effect.attributes_affected[0].applies_as = 1 # marking it as a buff

	gam.apply_effect(effect)

	assert_eq(attr.current_value, 100.0, "current_value should not have been affected")
	assert_eq(attr.current_buffed_value, 105.0, "current_buffed_value should have been affected")

	gam.apply_effect(damage_effect)

	assert_eq(attr.buffing_value, 0.0, "buffing value should be decreased before current_value")
	assert_eq(attr.current_value, 95.0, "current_value should be correct")
	assert_eq(attr.current_buffed_value, 95.0, "value should be correct")
	
	var damage_effect_duplicate = damage_effect.duplicate()

	owner_character.add_child(damage_effect_duplicate)	

	assert_eq(attr.buffing_value, 0.0, "buffing value should be decreased before current_value")
	assert_eq(attr.current_value, 85.0, "current_value should be correct")
	assert_eq(attr.current_buffed_value, 85.0, "value should be correct")

	assert_eq(damage_effect_duplicate.is_queued_for_deletion(), true, "the instant effect should have been removed from the tree")
	
	var child_nodes = owner_character.get_children()

	await wait_for_signal(owner_character.child_exiting_tree, 100.0, "waiting for effect to be removed")

	assert_eq(child_nodes.has(damage_effect_duplicate), false, "the node should have been removes")

#	assert_freed(damage_effect_duplicate.is_queued_for_deletion(), "the instant effect should have been removed from the tree")


func test_get_attributes_dict() -> void:
	var gam = _make_gam()

	assert_true(gam.get_attributes_dict().has(health_attribute_name), "the dictionary should have the attribute")
	assert_eq(gam.get_attributes_dict()[health_attribute_name], 100, "the dictionary should have the correct value")
