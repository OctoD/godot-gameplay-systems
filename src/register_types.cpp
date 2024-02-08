/// header for this file
#include "register_types.h"

/// godot stuff
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/editor_plugin_registration.hpp>
#include <godot_cpp/godot.hpp>

/// ggs stuff
#include "resource_manager/resource_manager.h"
#include "system/ability/ability.h"
#include "system/ability/ability_container.h"
#include "system/ability/ability_grant.h"
#include "system/ability/ability_queue.h"
#include "system/attribute/attribute.h"
#include "system/attribute/attribute_container.h"
#include "system/attribute/attribute_effect.h"
#include "system/attribute/attribute_effect_condition.h"
#include "system/attribute/attribute_manager.h"
#include "system/attribute/attribute_project_settings.h"
#include "system/attribute/gameplay_effect.h"
#include "system/attribute/gameplay_effect_stacking_behavior.h"
#include "system/item/equipment.h"
#include "system/item/equipment_manager.h"
#include "system/item/equipment_project_settings.h"
#include "system/item/item.h"
#include "system/item/item_manager.h"
#include "system/item/item_project_settings.h"
#include "system/item/items_pool.h"
#include "system/item/inventory.h"
#include "system/tag/tag_dictionary.h"
#include "system/tag/tag_manager.h"

/// ggs editor stuff
#include "editor_plugin/docks/ability/ability_inspector_plugin_editor.h"
#include "editor_plugin/docks/ability/ability_inspector_plugin.h"
#include "editor_plugin/docks/attribute/attribute_container_inspector_editor.h"
#include "editor_plugin/docks/attribute/attribute_container_inspector.h"
#include "editor_plugin/docks/tag/tag_docks.h"
#include "editor_plugin/ggs_editor_plugin.h"
#include "editor_plugin/main_scene/ggs_main_scene.h"
#include "editor_plugin/main_scene/ggs_new_resource_modal.h"
#include "editor_plugin/main_scene/attribute/ggs_attribute_main_scene.h"
#include "editor_plugin/main_scene/item/ggs_equipment_slot_scene.h"
#include "editor_plugin/main_scene/item/ggs_item_main_scene.h"
#include "editor_plugin/main_scene/item/ggs_item_pool_scene.h"
#include "editor_plugin/main_scene/tag/ggs_tag_dictionary_item.h"
#include "editor_plugin/main_scene/tag/ggs_tag_main_scene.h"

/// ggs scenes stuff
#include "system/tag/tag_tree.h"

/// implementation starts

using namespace godot;

void initialize_ggs_module(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		/// registering classes
		ClassDB::register_class<ggs::Ability>();
		ClassDB::register_class<ggs::AbilityContainer>();
		ClassDB::register_class<ggs::AbilityGrant>();
		ClassDB::register_class<ggs::Attribute>();
		ClassDB::register_class<ggs::AttributeContainer>();
		ClassDB::register_class<ggs::AttributeEffect>();
		ClassDB::register_class<ggs::AttributeEffectCondition>();
		ClassDB::register_class<ggs::AttributeManager>();
		ClassDB::register_class<ggs::Equipment>();
		ClassDB::register_class<ggs::EquipmentManager>();
		ClassDB::register_class<ggs::EquipmentSlot>();
		ClassDB::register_class<ggs::GameplayEffect>();
		ClassDB::register_class<ggs::GameplayEffectStackingBehavior>();
		ClassDB::register_class<ggs::Inventory>();
		ClassDB::register_class<ggs::InventoryItem>();
		ClassDB::register_class<ggs::Item>();
		ClassDB::register_class<ggs::ItemManager>();
		ClassDB::register_class<ggs::ItemSettings>();
		ClassDB::register_class<ggs::ItemTags>();
		ClassDB::register_class<ggs::ItemsPool>();
		ClassDB::register_class<ggs::TagDictionary>();
		ClassDB::register_class<ggs::TagManager>();
		ClassDB::register_class<ggs::TagTree>();

		/// registering internal classes
		ClassDB::register_internal_class<ggs::AbilityQueue>();
		ClassDB::register_internal_class<ggs::AbilityQueueItem>();
		ClassDB::register_internal_class<ggs::AttributeProjectSettings>();
		ClassDB::register_internal_class<ggs::EquipmentProjectSettings>();
		ClassDB::register_internal_class<ggs::ItemProjectSettings>();

		/// registering settings
		ggs::AttributeProjectSettings::setup();
		ggs::EquipmentProjectSettings::setup();
		ggs::ItemProjectSettings::setup();

		/// enabling autoloads
		Engine::get_singleton()->register_singleton("AttributeManager", ggs::AttributeManager::get_singleton());
		Engine::get_singleton()->register_singleton("EquipmentManager", ggs::EquipmentManager::get_singleton());
		Engine::get_singleton()->register_singleton("ItemManager", ggs::ItemManager::get_singleton());
		Engine::get_singleton()->register_singleton("TagManager", ggs::TagManager::get_singleton());
	}
	else if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR)
	{
		ClassDB::register_internal_class<ggs::ResourceManager>();

		Engine::get_singleton()->register_singleton("GGSResourceManager", ggs::ResourceManager::get_singleton());

		ClassDB::register_internal_class<ggs::editor_plugin::NewResourceModal>();
		ClassDB::register_internal_class<ggs::editor_plugin::AbilityInspectorPlugin>();
		ClassDB::register_internal_class<ggs::editor_plugin::AbilityInspectorPluginEditor>();
		ClassDB::register_internal_class<ggs::editor_plugin::AttributeContainerInspector>();
		ClassDB::register_internal_class<ggs::editor_plugin::AttributeContainerInspectorEditor>();
		ClassDB::register_internal_class<ggs::editor_plugin::AttributeMainScene>();
		ClassDB::register_internal_class<ggs::editor_plugin::EquipmentSlotScene>();
		ClassDB::register_internal_class<ggs::editor_plugin::GGSEditorPlugin>();
		ClassDB::register_internal_class<ggs::editor_plugin::ItemMainScene>();
		ClassDB::register_internal_class<ggs::editor_plugin::ItemPoolScene>();
		ClassDB::register_internal_class<ggs::editor_plugin::MainScene>();
		ClassDB::register_internal_class<ggs::editor_plugin::TagDictionaryItem>();
		ClassDB::register_internal_class<ggs::editor_plugin::TagDocks>();
		ClassDB::register_internal_class<ggs::editor_plugin::TagMainScene>();

		EditorPlugins::add_by_type<ggs::editor_plugin::GGSEditorPlugin>();
	}
}

void uninitialize_ggs_module(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		Engine::get_singleton()->unregister_singleton("AttributeManager");
		Engine::get_singleton()->unregister_singleton("EquipmentManager");
		Engine::get_singleton()->unregister_singleton("ItemManager");
		Engine::get_singleton()->unregister_singleton("TagManager");
	}
	else if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR)
	{
		EditorPlugins::remove_by_type<ggs::editor_plugin::GGSEditorPlugin>();
		/// this must be the last
		/// todo: ask the dev if the .ggs folder should be deleted with all the files
		Engine::get_singleton()->unregister_singleton("GGSResourceManager");
	}
}

extern "C"
{
	// Initialization.
	GDExtensionBool GDE_EXPORT ggs_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

		init_obj.register_initializer(initialize_ggs_module);
		init_obj.register_terminator(uninitialize_ggs_module);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
