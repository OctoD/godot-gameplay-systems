#ifndef GGS_ATTRIBUTE_CONTAINER_H
#define GGS_ATTRIBUTE_CONTAINER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/timer.hpp>

#include "attribute_effect.h"
#include "attribute.h"
#include "gameplay_effect.h"

using namespace godot;

namespace ggs
{
	class AttributeContainer : public Node
	{
		GDCLASS(AttributeContainer, Node);

	private:
		float _process_delta;

		/// @brief Handles the given gampeplay effect.
		/// @param p_node The node that received the gampeplay effect.
		void _handle_attribute_owner_received_node(Node *p_node);

	protected:
		friend class GGSAttributeContainerInspectorEditor;

		static void _bind_methods();
		/// @brief The attributes of the container.
		TypedArray<Attribute> attributes;
		/// @brief The ongoing attributes' effects of the container.
		TypedArray<AttributeEffect> ongoing_effects;
		/// @brief The owner of the attributes.
		Node *attributes_owner;
		/// @brief The dictionary used to store the timeouts count of the time_based effects.
		Dictionary timeouts_count;
		/// @brief Applies the given attribute effect.
		/// @param attribute_effect The attribute effect to apply.
		/// @param attribute The attribute to apply the effect to.
		void apply_attribute_effect(AttributeEffect *attribute_effect, Ref<Attribute> &attribute);
		/// @brief Checks if the attribute effect conditions are met.
		/// @param attribute_effect The attribute effect to check.
		/// @return True if the attribute effect conditions are met, false otherwise.
		bool are_attribute_conditions_met(AttributeEffect *attribute_effect);
		/// @brief Counts the number of times the given effect has been applied.
		/// @param p_id The id of the attribute effect.
		int increase_attribute_effect_timer_count(AttributeEffect *p_attribute_effect);

	public:
		/// @brief Default constructor.
		AttributeContainer();
		/// @brief A constructor.
		/// @param attributes
		AttributeContainer(Array p_attributes);
		/// @brief The constructor.
		/// @param attributes The attributes of the container.
		AttributeContainer(TypedArray<Attribute> p_attributes);
		/// @brief The constructor.
		/// @param attributes The attributes of the container.
		AttributeContainer(Node *p_attributes_owner, TypedArray<Attribute> p_attributes);
		/// @brief Destructor.
		~AttributeContainer();

		/// @brief Handles the process of the node.
		/// @param delta
		void _process(float delta);
		/// @brief Called when the node enters the scene tree for the first time.
		void _ready() override;

		/// @brief Applies the given effect.
		/// @param p_effect The effect to activate.
		void apply_effect(GameplayEffect *p_effect);
		/// @brief Returns how many times the given effect has been applied.
		/// @param p_effect The effect to count.
		/// @return The number of times the given effect has been applied.
		int count_timeouts(AttributeEffect *p_effect);
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
		Ref<Attribute> get_attribute(StringName p_attribute_name) const;
		/// @brief Gets the ongoing attributes' effects of the container.
		/// @return The ongoing attributes' effects of the container.
		TypedArray<AttributeEffect> get_ongoing_effects() const;
        /// @brief Returns the attributes as a dictionary. It is a dictionary where keys are the Attribute's tag_name and the value is the Attribute value.
        /// @return The attributes as a dictionary.
        Dictionary get_attributes_as_dictionary() const;
        /// @brief Gets the owner of the attributes.
        /// @return The owner of the attributes.
        Node *get_attributes_owner() const;
		/// @brief Get the attributes of the container.
		/// @return The attributes of the container.
		TypedArray<Attribute> get_attributes() const;
		/// @brief Set the attributes of the container.
		/// @param attributes The attributes to set.
		void set_attributes(const TypedArray<Attribute> &attributes);
		/// @brief Set the owner of the attributes.
		/// @param p_attributes_owner The owner of the attributes.
		void set_attributes_owner(Node *p_attributes_owner);
	};
}

#endif
