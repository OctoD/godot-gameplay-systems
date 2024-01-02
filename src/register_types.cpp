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
#include "system/tag/tag_dictionary.h"
#include "system/tag/tag_manager.h"
#include "system/tag/tag_project_settings.h"

/// ggs editor stuff
#include "editor_plugin/docks/tag/tag_docks.h"
#include "editor_plugin/ggs_editor_plugin.h"
#include "editor_plugin/main_scene/ggs_main_scene.h"
#include "editor_plugin/main_scene/tag/ggs_tag_dictionary_item.h"
#include "editor_plugin/main_scene/tag/ggs_tag_main_scene.h"

/// ggs scenes stuff
#include "scene/tag/tag_tree.h"

/// implementation starts

using namespace godot;

void initialize_ggs_module(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		/// registering settings
		TagProjectSettings::setup();

		/// registering classes
		ClassDB::register_class<TagDictionary>();
		ClassDB::register_class<TagManager>();
		ClassDB::register_class<TagTree>();

		/// initializing settings
		TagProjectSettings::setup();

		/// enabling autoloads
		Engine::get_singleton()->register_singleton("TagManager", memnew(TagManager));
	}
	else if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR)
	{
		ClassDB::register_internal_class<GGSTagDocks>();
		ClassDB::register_internal_class<GGSTagDictionaryItem>();
		ClassDB::register_internal_class<GGSTagMainScene>();
		ClassDB::register_internal_class<GGSMainScene>();
		ClassDB::register_internal_class<GGSEditorPlugin>();
		EditorPlugins::add_by_type<GGSEditorPlugin>();
	}
}

void uninitialize_ggs_module(ModuleInitializationLevel p_level)
{
	if (p_level == MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		Engine::get_singleton()->unregister_singleton("TagManager");
	}
	else if (p_level == MODULE_INITIALIZATION_LEVEL_EDITOR)
	{
		EditorPlugins::remove_by_type<GGSEditorPlugin>();
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
