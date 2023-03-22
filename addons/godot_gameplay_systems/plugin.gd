@tool
extends EditorPlugin

const ATTRIBUTE_SPEC_NAME = "AttributeSpec"
const ABILITY_CONTAINER_NAME = "AbilityContainer"
const ACTIVATION_EVENT_NAME = "ActivationEvent"
const ATTRIBUTE_RESOURCE_NAME = "AttributeResource"
const ATTRIBUTE_TABLE_RESOURCE_NAME = "AttributeTableResource"
const ATTRIBUTE_EFFECT_RESOURCE_NAME = "AttributeEffectResource"
const ATTRIBUTE_EFFECT_CONDITION_RESOURCE_NAME = "AttributeEffectCondition"
const GAMEPLAY_EFFECT_NAME = "GameplayEffect"
const GAMEPLAY_ATTRIBUTE_MAP_NAME = "GameplayAttributeMap"
const EFFECTED_AREA2D = "EffectedArea2D"
const EFFECTED_AREA3D = "EffectedArea3D"
const STOP_EFFECT_IF0_RESOURCE_NAME = "StopEffectIfAttributeIs0"

const attribute_spec_script = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/objects/attribute_spec.gd")
const ability_container_resource = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/nodes/ability_container.gd")
const activation_event_script = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/objects/activation_event.gd")
const attributes_table_resource = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/resources/attribute_table.gd")
const attribute_resource = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/resources/attribute.gd")
const attribute_effect_resource = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/resources/attribute_effect.gd")
const attribute_effect_condition_resource = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/resources/attribute_effect_condition.gd")
const effected_area2d = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/nodes/effected_area2d.gd")
const effected_area3d = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/nodes/effected_area3d.gd")
const gameplay_effect = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/nodes/gameplay_effect.gd")
const gameplay_attribute_map = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/nodes/gameplay_attribute_map.gd")
const stop_effect_if0_resource = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/resources/stop_effect_if_0.gd")

const attribute_inspector_plugin_script = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/inspector/gameplay_attribute_map_inspector_plugin.gd")
const effect_inspector_plugin_script = preload("res://addons/godot_gameplay_systems/attributes_and_abilities/inspector/gameplay_effect_inspector_plugin.gd")


var attribute_inspector_plugin: EditorInspectorPlugin
var effect_inspector_plugin: EditorInspectorPlugin


func _enter_tree():
	add_custom_type(ACTIVATION_EVENT_NAME, "RefCounted", activation_event_script, null)
	add_custom_type(ATTRIBUTE_SPEC_NAME, "RefCounted", attribute_spec_script, null)
	
	add_custom_type(ATTRIBUTE_RESOURCE_NAME, "Resource", attribute_resource, preload("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/Attribute@0.15x.png"))
	add_custom_type(ATTRIBUTE_TABLE_RESOURCE_NAME, "Resource", attributes_table_resource, preload("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/AttributeTable@0.15x.png"))
	add_custom_type(ATTRIBUTE_EFFECT_RESOURCE_NAME, "Resource", attribute_effect_resource, preload("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/GameplayEffect@0.15x.png"))
	add_custom_type(ATTRIBUTE_EFFECT_CONDITION_RESOURCE_NAME, "Resource", attribute_effect_condition_resource, null)
	add_custom_type(GAMEPLAY_ATTRIBUTE_MAP_NAME, "Node", gameplay_attribute_map, preload("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/GameplayAttributeMap@0.15x.png"))
	add_custom_type(GAMEPLAY_EFFECT_NAME, "Node", gameplay_effect, preload("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/GameplayEffect@0.15x.png"))
	add_custom_type(EFFECTED_AREA2D, "Area2D", effected_area2d, null)
	add_custom_type(EFFECTED_AREA3D, "Area3D", effected_area3d, null)
	add_custom_type(STOP_EFFECT_IF0_RESOURCE_NAME, ATTRIBUTE_EFFECT_CONDITION_RESOURCE_NAME, stop_effect_if0_resource, null)

	add_custom_type(ABILITY_CONTAINER_NAME, "Node",	ability_container_resource, preload("res://addons/godot_gameplay_systems/attributes_and_abilities/assets/AbilityContainer@0.15x.png"))

	attribute_inspector_plugin = attribute_inspector_plugin_script.new()
	effect_inspector_plugin = effect_inspector_plugin_script.new()
	
	add_inspector_plugin(attribute_inspector_plugin)
	add_inspector_plugin(effect_inspector_plugin)


func _exit_tree():
	remove_custom_type(ATTRIBUTE_RESOURCE_NAME)
	remove_custom_type(ATTRIBUTE_TABLE_RESOURCE_NAME)
	remove_custom_type(ATTRIBUTE_EFFECT_RESOURCE_NAME)
	remove_custom_type(ATTRIBUTE_EFFECT_CONDITION_RESOURCE_NAME)
	remove_custom_type(GAMEPLAY_ATTRIBUTE_MAP_NAME)
	remove_custom_type(GAMEPLAY_EFFECT_NAME)
	remove_custom_type(EFFECTED_AREA2D)
	remove_custom_type(EFFECTED_AREA3D)
	remove_custom_type(STOP_EFFECT_IF0_RESOURCE_NAME)
	
	remove_custom_type(ABILITY_CONTAINER_NAME)
	
	remove_custom_type(ATTRIBUTE_SPEC_NAME)
	remove_custom_type(ACTIVATION_EVENT_NAME)
	
	remove_inspector_plugin(attribute_inspector_plugin)
	remove_inspector_plugin(effect_inspector_plugin)
