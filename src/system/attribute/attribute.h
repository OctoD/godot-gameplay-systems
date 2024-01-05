#ifndef GGS_ATTRIBUTE_H
#define GGS_ATTRIBUTE_H

#include <godot_cpp/classes/resource.hpp>

using namespace godot;

namespace ggs
{
	class Attribute : public Resource
	{
		GDCLASS(Attribute, Resource);

	protected:
		/// @brief Binds methods to the Godot engine.
		static void _bind_methods();
		/// @brief The tag name associated with this attribute.
		StringName tag_name;

		/// @brief The buff applied to this attribute.
		float buff;
		/// @brief The current value of this attribute.
		float current_value;
		/// @brief The initial value of this attribute.
		float initial_value;
		/// @brief The maximum value of this attribute.
		float max_value;
		/// @brief The minimum value of this attribute.
		float min_value;

	public:
		Attribute();
		Attribute(StringName p_tag_name);
		Attribute(Attribute &p_attribute);
		Attribute(Ref<Attribute> p_attribute);
		Attribute(Dictionary p_dictionary);
		~Attribute();

		/// @brief Adds a buff to this attribute.
		/// @param p_buff The buff to add.
		void add_buff(float p_buff);
		/// @brief Adds a value to this attribute.
		/// @param p_value The value to add.
		void add_value(float p_value);
		/// @brief Checks if this attribute allows negative values (aka the min_value set to negative).
		/// @param p_tag_name The tag name to check.
		/// @return True if this attribute allows negative values, false otherwise.
		bool has_tag_name(StringName p_tag_name) const;
		/// @brief Returns whether or not this attribute allows negative values (aka the min_value set to negative).
		/// @return
		bool get_allow_negative() const;
		/// @brief Gets the buff applied to this attribute.
		/// @return
		float get_buff() const;
		/// @brief Gets the initial value of this attribute.
		/// @return
		float get_initial_value() const;
		/// @brief Gets the maximum value of this attribute.
		/// @return
		float get_max_value() const;
		/// @brief Gets the minimum value of this attribute.
		/// @return
		float get_min_value() const;
		/// @brief Gets the tag name associated with this attribute.
		/// @return
		StringName get_tag_name() const;
		/// @brief Gets the value of this attribute. This is the current value plus the buff.
		/// @return
		float get_value() const;
		/// @brief Sets the buff applied to this attribute.
		/// @param p_buff
		void set_buff(float p_buff);
		/// @brief Sets the initial value of this attribute.
		/// @param p_initial_value
		void set_initial_value(float p_initial_value);
		/// @brief Sets the maximum value of this attribute.
		/// @param p_max_value
		void set_max_value(float p_max_value);
		/// @brief Sets the minimum value of this attribute.
		/// @param p_min_value
		void set_min_value(float p_min_value);
		/// @brief Sets the tag name associated with this attribute.
		/// @param p_tag_name
		void set_tag_name(StringName p_tag_name);
		/// @brief Sets the current value of this attribute.
		/// @param p_value The value to set.
		void set_value(float p_value);
		/// @brief Subtracts a buff from this attribute.
		/// @param p_buff The buff to subtract.
		void subtract_buff(float p_buff);
		/// @brief Subtracts a value from this attribute.
		/// @param p_value The value to subtract.
		void subtract_value(float p_value);
	};
}

#endif
