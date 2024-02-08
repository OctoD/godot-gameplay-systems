#ifndef GGS_RESOURCE_MANAGER_H
#define GGS_RESOURCE_MANAGER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/resource.hpp>
#include "system/item/equipment_slot.h"
#include "system/item/items_pool.h"
#include "system/tag/tag_dictionary.h"

using namespace godot;

namespace ggs
{
	namespace editor_plugin
	{
		class EquipmentSlotScene;
		class GGSEditorPlugin;
		class ItemPoolScene;
		class TagMainScene;
	}

	class ResourceManager : public Node
	{
		GDCLASS(ResourceManager, Node);

		static const char *EQUIPMENT_DIR;
		static const char *ITEMS_DIR;
		static const char *TAGS_DIR;

	protected:
		friend class editor_plugin::EquipmentSlotScene;
		friend class editor_plugin::GGSEditorPlugin;
		friend class editor_plugin::ItemPoolScene;
		friend class editor_plugin::TagMainScene;

		/// @brief The resource manager's initialization method.
		static void _bind_methods();
		/// @brief The singleton instance of the resource manager.
		static ResourceManager *instance;

		/// @brief Creates a new equipment slot resource.
		/// @return The new equipment slot resource.
		Ref<EquipmentSlot> create_equipment_slot_resource(String p_file_name) const;
		/// @brief Creates a new items pool resource.
		/// @return The new items pool resource.
		Ref<ItemsPool> create_items_pool_resource(String p_file_name) const;
		/// @brief Creates a new tag dictionary resource.
		/// @return The new tag dictionary resource.
		Ref<TagDictionary> create_tag_resource(String p_file_name) const;
		/// @brief Gets all the resources in the given directory.
		/// @param p_dir The directory to get the resources from.
		/// @return The resources in the given directory.
		TypedArray<Resource> get_resources(const String &p_dir) const;
		/// @brief Ensures that the given directory exists, if not, it is created.
		void ensure_directory(const String &p_dir) const;
		/// @brief Ensures that the directories for the ggs resources exist, if not, they are created.
		void ensure_directories() const;
        /// @brief Removes the given resource from the file system.
        /// @param p_ref The resource to remove.
        /// @return The error code.
        Error remove_resource(Ref<Resource> p_ref) const;
        /// @brief Saves the given resource to the file system.
        /// @param p_dirname The directory to save the resource to.
        /// @param p_ref The resource to save.
        Error save_resource(const String &p_dirname, Ref<Resource> p_ref) const;

	public:
		ResourceManager();
		~ResourceManager();

		/// @brief Gets the singleton instance of the resource manager.
		/// @return The singleton instance of the resource manager.
		static ResourceManager *get_singleton();

		static String get_resource_name_from_name(const String &p_string);

		/// @brief Gets all the resources in the abilities directory.
		/// @return The resources in the abilities directory.
		TypedArray<EquipmentSlot> get_equipment_slot_resources() const;
		/// @brief Gets all the resources in the items directory.
		/// @return The resources in the items directory.
		TypedArray<ItemsPool> get_items_pool_resources() const;
		/// @brief Gets all the resources in the tags directory.
		/// @return The resources in the tags directory.
		TypedArray<TagDictionary> get_tag_resources() const;
		/// @brief Saves the given resource to the file system.
		/// @param p_ref The resource to save.
		bool save_resource(Ref<EquipmentSlot> p_ref) const;
		/// @brief Saves the given resource to the file system.
		/// @param p_ref The resource to save.
		bool save_resource(Ref<ItemsPool> p_ref) const;
		/// @brief Saves the given resource to the file system.
		/// @param p_ref The resource to save.
		bool save_resource(Ref<TagDictionary> p_ref) const;
	};
}

#endif
