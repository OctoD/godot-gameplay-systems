#ifndef GGS_ATTRIBUTE_CONTAINER_H
#define GGS_ATTRIBUTE_CONTAINER_H

#include <godot_cpp/classes/node.hpp>

#include "attribute.h"

using namespace godot;

namespace ggs
{
	class AttributeContainer : public Node
	{
		GDCLASS(AttributeContainer, Node);

	protected:
		static void _bind_methods();
		/// @brief The attributes of the container.
		TypedArray<Attribute> attributes;

	public:
		/// @brief Default constructor.
		AttributeContainer();
		/// @brief The constructor.
		/// @param attributes The attributes of the container.
		AttributeContainer(TypedArray<Attribute> p_attributes);
		/// @brief Destructor.
		~AttributeContainer();

		/// @brief Called when the node enters the scene tree for the first time.
		void _ready() override;

		/// @brief Ensures that the container has the attributes defined in the given array.
		/// @param p_attributes The attributes to ensure.
		void ensure_attributes(PackedStringArray p_attributes);
		/// @brief Checks if the container has an attribute with the given tag name.
		/// @param p_attribute_name The attribute tag name.
		/// @return Returns true if the container has an attribute with the given tag name, false otherwise.
		bool has_attribute(StringName p_attribute_name) const;
		/// @brief Get the attribute with the given tag name.
		/// @param p_attribute_name The attribute tag name.
		/// @return Returns the attribute with the given tag name.
		Attribute *get_attribute(StringName p_attribute_name) const;
		/// @brief Get the attributes of the container.
		/// @return The attributes of the container.
		TypedArray<Attribute> get_attributes() const;
		/// @brief Set the attributes of the container.
		/// @param attributes The attributes to set.
		void set_attributes(const TypedArray<Attribute> &attributes);
	};
}

#endif
