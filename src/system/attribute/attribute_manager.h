#ifndef GGS_ATTRIBUTE_MANAGER_H
#define GGS_ATTRIBUTE_MANAGER_H

#include <godot_cpp/classes/node.hpp>

#include "attribute.h"
#include "attribute_container.h"
#include "system/tag/tag_dictionary.h"

using namespace godot;

namespace ggs
{
	class TagDictionary;

	class AttributeManager : public Node
	{
		GDCLASS(AttributeManager, Node);

	private:
        void _handle_tag_dictionary_changed();

	protected:
        /// @brief Binds methods to the Godot engine.
        static void _bind_methods();
		/// @brief The singleton instance of this manager.
		static AttributeManager *_singleton;
		/// @brief The attributes managed by this manager.
		PackedStringArray attributes;
		TagDictionary *tag_dictionary;

	public:
		AttributeManager();
		~AttributeManager();

		/// @brief Gets the singleton instance of this manager.
		static AttributeManager *get_singleton();
		/// @brief Gets the attributes managed by this manager.
		/// @return The attributes managed by this manager.
		PackedStringArray get_attributes();
		/// @brief Gets the tag dictionary used by this manager.
		/// @return 
		TagDictionary* get_tag_dictionary() const;
		/// @brief Called when the node enters the scene tree for the first time.
		void _ready() override;
		/// @brief Loads attributes from the given tag dictionary.
		TagDictionary* load_attributes();
		/// @brief Sets the attributes managed by this manager.
		/// @param p_attributes The attributes managed by this manager.
		void set_attributes(const PackedStringArray &p_attributes);
		/// @brief Sets the tag dictionary used by this manager.
		/// @param p_tag_dictionary 
		void set_tag_dictionary(TagDictionary *p_tag_dictionary);
	};
}

#endif // GGS_ATTRIBUTE_MANAGER_H