#include <godot_cpp/classes/engine.hpp>

#include "attribute.h"

using namespace ggs;

void Attribute::_bind_methods()
{
	/// methods binding
	ClassDB::bind_method(D_METHOD("add_buff", "buff"), &Attribute::add_buff);
	ClassDB::bind_method(D_METHOD("add_value", "value"), &Attribute::add_value);
	ClassDB::bind_method(D_METHOD("has_tag_name"), &Attribute::has_tag_name);
	ClassDB::bind_method(D_METHOD("get_allow_negative"), &Attribute::get_allow_negative);
	ClassDB::bind_method(D_METHOD("get_buff"), &Attribute::get_buff);
	ClassDB::bind_method(D_METHOD("get_initial_value"), &Attribute::get_initial_value);
	ClassDB::bind_method(D_METHOD("get_max_value"), &Attribute::get_max_value);
	ClassDB::bind_method(D_METHOD("get_min_value"), &Attribute::get_min_value);
	ClassDB::bind_method(D_METHOD("get_tag_name"), &Attribute::get_tag_name);
	ClassDB::bind_method(D_METHOD("get_value"), &Attribute::get_value);
	ClassDB::bind_method(D_METHOD("set_buff", "buff"), &Attribute::set_buff);
	ClassDB::bind_method(D_METHOD("set_initial_value", "initial_value"), &Attribute::set_initial_value);
	ClassDB::bind_method(D_METHOD("set_max_value", "max_value"), &Attribute::set_max_value);
	ClassDB::bind_method(D_METHOD("set_min_value", "min_value"), &Attribute::set_min_value);
	ClassDB::bind_method(D_METHOD("set_tag_name", "tag_name"), &Attribute::set_tag_name);
	ClassDB::bind_method(D_METHOD("set_value", "current_value"), &Attribute::set_value);
	ClassDB::bind_method(D_METHOD("subtract_buff", "buff"), &Attribute::subtract_buff);
	ClassDB::bind_method(D_METHOD("subtract_value", "value"), &Attribute::subtract_value);

	/// properties binding
	ADD_PROPERTY(PropertyInfo(Variant::STRING_NAME, "tag_name"), "set_tag_name", "get_tag_name");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "buff"), "set_buff", "get_buff");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "value"), "set_value", "get_value");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "initial_value"), "set_initial_value", "get_initial_value");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "max_value"), "set_max_value", "get_max_value");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "min_value"), "set_min_value", "get_min_value");

	/// signals binding
	ADD_SIGNAL(MethodInfo("buff_changed", PropertyInfo(Variant::FLOAT, "previous_buff"), PropertyInfo(Variant::FLOAT, "current_buff")));
	ADD_SIGNAL(MethodInfo("value_changed", PropertyInfo(Variant::FLOAT, "previous_value"), PropertyInfo(Variant::FLOAT, "current_value")));
}

Attribute::Attribute()
{

}

Attribute::Attribute(StringName p_tag_name)
{
	tag_name = p_tag_name;
	current_value = 0.0f;
	initial_value = 0.0f;
	max_value = 0.0f;
	min_value = 0.0f;
	set_local_to_scene(true);
}

Attribute::Attribute(Attribute &p_attribute)
{
	buff = p_attribute.buff;
	current_value = p_attribute.current_value;
	initial_value = p_attribute.initial_value;
	max_value = p_attribute.max_value;
	min_value = p_attribute.min_value;
	tag_name = p_attribute.tag_name;
	set_local_to_scene(true);
}

Attribute::Attribute(Ref<Attribute> p_attribute)
{
	buff = p_attribute->buff;
	current_value = p_attribute->current_value;
	initial_value = p_attribute->initial_value;
	max_value = p_attribute->max_value;
	min_value = p_attribute->min_value;
	tag_name = p_attribute->tag_name;
	set_local_to_scene(true);
}

Attribute::Attribute(Dictionary p_dictionary)
{
	buff = p_dictionary.has("buff") ? static_cast<int>(p_dictionary["buff"]) : 0;
	current_value = p_dictionary.has("current_value") ? static_cast<int>(p_dictionary["current_value"]) : 0;
	initial_value = p_dictionary.has("initial_value") ? static_cast<int>(p_dictionary["initial_value"]) : 0;
	max_value = p_dictionary.has("max_value") ? static_cast<int>(p_dictionary["max_value"]) : 0;
	min_value = p_dictionary.has("min_value") ? static_cast<int>(p_dictionary["min_value"]) : 0;
	tag_name = p_dictionary.has("tag_name") ? static_cast<StringName>(p_dictionary["tag_name"]) : StringName();
	set_local_to_scene(true);
}

Attribute::~Attribute()
{
}

bool Attribute::has_tag_name(StringName p_tag_name) const
{
    return tag_name == p_tag_name;
}

bool Attribute::get_allow_negative() const
{
	return min_value < 0;
}

float Attribute::get_buff() const
{
	return buff;
}

float Attribute::get_initial_value() const
{
	return initial_value;
}

float Attribute::get_max_value() const
{
	return max_value;
}

float Attribute::get_min_value() const
{
	return min_value;
}

StringName Attribute::get_tag_name() const
{
	return tag_name;
}

float Attribute::get_value() const
{
	return current_value + buff;
}

void Attribute::add_buff(float p_buff)
{
	float copy = buff;
	buff += p_buff;

	if (buff != copy)
	{
		emit_signal("buff_changed", copy, buff);
		emit_changed();
	}
}

void Attribute::add_value(float p_value)
{
	float copy = current_value;
	float result = current_value + p_value;
	current_value = result > max_value ? max_value : result;

	if (current_value != copy)
	{
		emit_signal("value_changed", copy, current_value);
		emit_changed();
	}
}

void Attribute::set_buff(float p_buff)
{
	float copy = buff;
	buff = p_buff;

	if (buff != copy)
	{
		emit_signal("buff_changed", copy, buff);
		emit_changed();
	}
}

void Attribute::set_initial_value(float p_initial_value)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		initial_value = p_initial_value;
		current_value = initial_value;
		emit_changed();
	}
}

void Attribute::set_max_value(float p_max_value)
{
	max_value = p_max_value;
	emit_changed();
}

void Attribute::set_min_value(float p_min_value)
{
	min_value = p_min_value;
	emit_changed();
}

void Attribute::set_tag_name(StringName p_tag_name)
{
	if (Engine::get_singleton()->is_editor_hint())
	{
		tag_name = p_tag_name;
		emit_changed();
	}
}

void Attribute::set_value(float p_value)
{
	float copy = current_value;
	current_value = p_value;
	emit_signal("value_changed", copy, current_value);
	emit_changed();
}

void Attribute::subtract_buff(float p_buff)
{
	float copy = buff;
	float result = buff - Math::abs(p_buff);
	buff = result < 0 ? 0 : result;

	if (buff != copy)
	{
		emit_signal("buff_changed", copy, buff);
		emit_changed();
	}
}

void Attribute::subtract_value(float p_value)
{
	float copy = current_value;
	float result = current_value - Math::abs(p_value);
	current_value = result > min_value ? result : min_value;

	if (current_value != copy)
	{
		emit_signal("value_changed", copy, current_value);
		emit_changed();
	}
}
