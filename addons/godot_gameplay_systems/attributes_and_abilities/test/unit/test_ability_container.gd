extends GutTest


class Ability000 extends  Ability:
	func can_activate(evt: ActivationEvent) -> bool:
		return evt != null and not evt.tags.has("001.start")

	func _init(id: String) -> void:
		ui_name = id + ".myname"
		grant_tags.append(id)
		tags_activation.append(id + ".start")
		tags_to_remove_on_end.append(id + "start")


class Ability001 extends Ability:
	func _init(activation: String, block: String) -> void:
		tags_activation.append(activation)
		tags_block.append(block)


class CooldownPoisonAbility extends Ability:
	var start_tagname = "poisoned"
	var end_tagname = "cured"

	func _init() -> void:
		cooldown_continuos = true
		cooldown_duration = 10.0
		tags_activation.append(start_tagname)
		tags_cancellation_required.append("cured")
		tags_to_remove_on_cancellation.append_array([start_tagname, end_tagname])


	func activate(event: ActivationEvent) -> void:
		var effect = GameplayEffect.new()
		var attribute_effected = AttributeEffect.new()
		
		attribute_effected.attribute_name = "health"
		attribute_effected.apply_every_second = 1.0
		attribute_effected.life_time = 1
		attribute_effected.max_applications = 10
		attribute_effected.maximum_value = -1.0
		attribute_effected.minimum_value = -1.0

		effect.attributes_affected.append(attribute_effected)
		event.attribute_map.apply_effect(effect)


func _ability000(id: String) -> Ability:
	var a = Ability.new()
	
	a.grant_tags.append(id)
	a.tags_activation.append(id + ".start")
	a.tags_to_remove_on_end.append(id + "start")
	
	return a


func _make(abilities: Array[Ability] = []) -> AbilityContainer:
	var container = AbilityContainer.new()
	
	container.abilities = abilities
	
	var attributes = GameplayAttributeMap.new()
	
	attributes.table = AttributeTable.new()
	attributes.table.attributes.append("health")
	attributes.table.attributes.append("mana")
	
	var health = AttributeResource.new()
	var mana = AttributeResource.new()
	
	health.attribute_name = "health"
	mana.attribute_name = "mana"
	health.maximum_value = 100.0
	health.current_value = 100.0
	mana.maximum_value = 100.0
	mana.current_value = 50.0

	attributes.attributes.append_array([health, mana])

	add_child_autofree(attributes)
	
	container.gameplay_attribute_map_path = attributes.get_path()
	
	add_child_autofree(container)
	
	watch_signals(attributes)
	watch_signals(container)
	
	return container


func test_tag_system() -> void:
	var container = _make()
	var tag000 = "tag000"
	var tag001 = "tag001"
	
	container.add_tag(tag000)
	container.add_tag(tag000)
	container.add_tag(tag000)

	assert_signal_emitted(container, "tags_updated", "signal tags_updated should have been emitted")
	assert_signal_emit_count(container, "tags_updated", 1, "signal tags_updated should have been emitted only once")

	assert_eq(container.tags.size(), 1, "duped tags should not be added")
	
	container.add_tag(tag001)
	
	assert_eq(container.has_tag(tag001), true, "should contain tag001 it")

	assert_signal_emitted(container, "tags_updated", "signal tags_updated should have been emitted")
	
	container.remove_tag(tag000)
	
	assert_ne(container.has_tag(tag000), true, "should not contain tag000 anymore")

	assert_signal_emitted(container, "tags_updated", "signal tags_updated should have been emitted")
	
	assert_eq(container.tags.size(), 1, "tags should have been removed properly")
	assert_eq(container.tags.has(tag001), true, "tags should have been updated properly")
	

func test_granting() -> void:
	var a000 = Ability000.new("000")
	var a001 = Ability000.new("001")
	var c = _make([a000, a001])
	var d = _make()
	
	assert_ne(c.can_grant(a000), true, "a000 should have been already granted")
	assert_ne(c.can_grant(a001), true, "a001 should have been already granted")
	assert_eq(d.can_grant(a000), true, "a000 should have not been already granted")
	assert_eq(d.can_grant(a001), true, "a001 should have not been already granted")

	assert_eq(d.granted_abilities.size(), 0, "granted_abilities should be 0")
	d.grant(a000)
	assert_eq(d.granted_abilities.size(), 1, "granted_abilities should be 1")
	d.grant(a001)
	assert_eq(d.granted_abilities.size(), 2, "granted_abilities should be 2")
	
	assert_signal_emitted(d, "ability_granted", "ability_granted should have been emitted")
	assert_signal_emit_count(d, "ability_granted", 2, "ability_granted should have been emitted twice")

	c.revoke(a000)
	c.revoke(a001)
	
	assert_signal_emitted(c, "ability_revoked", "ability_revoked should have been emitted")
	assert_signal_emit_count(c, "ability_revoked", 2, "ability_revoked should have been emitted twice")
	assert_eq(c.granted_abilities.size(), 0, "granted_abilities should be 0")


func test_cooldown_ability() -> void:
	var a000 = CooldownPoisonAbility.new()
	var a = _make([a000])

	a.activate_one(a000)

	await wait_seconds(10)

	assert_eq(a.gameplay_attribute_map.get_attribute_by_name("health").current_value, 90.0, "attribute_should have been decreased")

	a.remove_tag(a000.end_tagname)


func test_activate_many() -> void:
	var a000 = Ability001.new("000", "001")
	var a001 = Ability001.new("001", "000")
	var a = _make([a000, a001])

	assert_signal_emit_count(a, "ability_activated", 0, "ability_activated never called")

	a.activate_many()

	assert_signal_emit_count(a, "ability_activated", 1, "ability_activated called only once because one ability is blocked")
	
	# now lets test the paralled mode
	var b000 = Ability001.new("000", "001")
	var b001 = Ability001.new("001", "000")
	var b = _make([a000, a001])
	
	assert_signal_emit_count(b, "ability_activated", 0, "ability_activated never called")

	b.activate_many(true)

	assert_signal_emit_count(b, "ability_activated", 2, "ability_activated called twice")
