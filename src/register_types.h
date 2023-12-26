/* godot-cpp integration testing project.
 *
 * This is free and unencumbered software released into the public domain.
 */

#ifndef GGS_REGISTER_TYPES_H
#define GGS_REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void initialize_ggs_module(ModuleInitializationLevel p_level);
void uninitialize_ggs_module(ModuleInitializationLevel p_level);

#endif
