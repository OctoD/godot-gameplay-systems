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
		/// @brief Handles the given gampeplay effect.
		/// @param p_node The node that received the gampeplay effect.
		void _handle_attribute_owner_received_node(Node *p_node);
		/// @brief Called when the timer used to count the number of times the given effect has been applied times out.
		/// @param p_id The timer id.
		void _handle_timer_timeout(Timer *timer, Ref<AttributeEffect> &attribute_effect, Ref<Attribute> &attribute);

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
		void apply_attribute_effect(Ref<AttributeEffect> &attribute_effect, Ref<Attribute> &attribute);
		/// @brief Counts the number of times the given effect has been applied.
		/// @param p_id
		int increase_attribute_effect_timer_count(int p_id);
		/// @brief Setups the timer used to count the number of times the given effect has been applied.
		/// @return The timer used to count the number of times the given effect has been applied.
		Timer *setup_attribute_effect_timer(Ref<AttributeEffect> &attribute_effect, Ref<Attribute> &attribute);
		/// @brief Returns true if the attribute effect should be broken, false otherwise.
		/// @param attribute_effect The attribute effect to check.
		/// @param p_game_effect The gameplay effect that contains the attribute effect.
		/// @param break_effect The boolean that will be set to true if the effect should be broken.
		/// @return
		bool should_break_attribute_effect(Ref<AttributeEffect> &attribute_effect);

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

		/// @brief Called when the node enters the scene tree for the first time.
		void _ready() override;

		/// @brief Applies the given effect.
		/// @param p_effect The effect to activate.
		void apply_effect(GameplayEffect *p_effect);
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
