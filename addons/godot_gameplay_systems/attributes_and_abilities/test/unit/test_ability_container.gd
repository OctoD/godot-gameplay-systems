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


func test_granting_issue_23() -> void:
	# refers to issue #23 https://github.com/OctoD/godot-gameplay-systems/issues/23
	
	var ability000 = Ability000.new("000")
	var ability001 = Ability000.new("001")
	var ability002 = Ability000.new("002")
	var ability003 = Ability000.new("003")
	var ability004 = Ability000.new("004")
	var ability005 = Ability000.new("005")

	ability001.grant_tags_required.append("cannot be granted at all")
	ability004.grant_tags_required.append("cannot be granted at all")

	var container = _make([ability000, ability001, ability002, ability003, ability004, ability005])

	container.grant(ability000)
	container.grant(ability001)
	container.grant(ability002)
	container.grant(ability003)
	container.grant(ability004)
	container.grant(ability005)

	assert_eq(container.granted_abilities.has(ability000), true, "ability000 should have been granted")
	assert_eq(container.granted_abilities.has(ability002), true, "ability002 should have been granted")
	assert_eq(container.granted_abilities.has(ability001), false, "ability001 should not have been granted")
	assert_eq(container.granted_abilities.has(ability003), true, "ability003 should have been granted")
	assert_eq(container.granted_abilities.has(ability004), false, "ability004 should not have been granted")
	assert_eq(container.granted_abilities.has(ability005), true, "ability005 should have been granted")

	assert_eq(container.abilities.has(ability000), false, "ability000 should not be there since it's granted")
	assert_eq(container.abilities.has(ability002), false, "ability002 should not be there since it's granted")
	assert_eq(container.abilities.has(ability001), true, "ability001 should be there since it's not granted")
	assert_eq(container.abilities.has(ability003), false, "ability003 should be there since it's not granted")
	assert_eq(container.abilities.has(ability004), true, "ability004 should be there since it's not granted")
	assert_eq(container.abilities.has(ability005), false, "ability005 should not be there since it's granted")


	# it should reach this point to avoid that possible bug about not granting abilities at all if one is not grantable


class _test_Enemy_hairic95 extends Node2D:
	var ability_container: AbilityContainer
	
	func _init(ability: Ability000) -> void:
		ability_container = AbilityContainer.new()
		add_child(ability_container)
		ability_container.grant(ability)


	func fire() -> void:
		ability_container.activate_many()


func test_hairic95_issue() -> void:
	var ability000 = Ability000.new("000")

	ability000.tags_activation.append("started")

	var enemy000 = _test_Enemy_hairic95.new(ability000)
	var enemy001 = _test_Enemy_hairic95.new(ability000)
	var enemy002 = _test_Enemy_hairic95.new(ability000)
	var enemies = [enemy000, enemy001, enemy002]

	add_child_autofree(enemy000)
	add_child_autofree(enemy001)
	add_child_autofree(enemy002)

	enemy000.get("fire").call()

	assert_eq(enemy000.ability_container.tags.has("started"), true, "Ability container should have the tag")
	assert_eq(enemy001.ability_container.tags.has("started"), false, "Ability container should have the tag")
	assert_eq(enemy002.ability_container.tags.has("started"), false, "Ability container should have the tag")

	for e in enemies:
		e.get("fire").call()

	assert_eq(enemy000.ability_container.tags.has("started"), true, "Ability container should have the tag")
	assert_eq(enemy001.ability_container.tags.has("started"), true, "Ability container should have the tag")
	assert_eq(enemy002.ability_container.tags.has("started"), true, "Ability container should have the tag")
