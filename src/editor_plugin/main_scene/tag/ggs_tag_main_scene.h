#ifndef GGS_TAG_MAIN_SCENE_H
#define GGS_TAG_MAIN_SCENE_H

#include <godot_cpp/classes/confirmation_dialog.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/editor_file_dialog.hpp>
#include <godot_cpp/classes/tree.hpp>
#include <godot_cpp/classes/v_box_container.hpp>

using namespace godot;

namespace ggs
{
    class TagDictionary;

    namespace editor_plugin
    {
        class TagMainScene : public Control
        {
            GDCLASS(TagMainScene, Control);

        public:
            void _ready() override;

        protected:
            static void _bind_methods();
            /// @brief Renders the tag dictionaries.
            void render_tag_dictionaries();

            void _handle_add_tag_dictionary_requested(String p_name);

        private:
            VBoxContainer *_dictionaries_container;
            ConfirmationDialog *_confirmation_dialog;
            /// @brief Called when the user presses the add tag dictionary button.
            /// @param p_dictionary The dictionary to add the tag to.
            /// @param p_tag_path_input The line edit containing the tag path.
            void _handle_add_tag(TagDictionary *p_dictionary, LineEdit *p_tag_path_input);
            /// @brief Called when the user presses the edit tag button.
            /// @param p_dictionary The dictionary to add the tag to.
            /// @param p_tag_path_input The line edit containing the tag path.
            /// @param old_path The old path of the tag.
            void _handle_edit_tag(TagDictionary *p_dictionary, LineEdit *p_tag_path_input, String old_path);
            /// @brief Called when the user presses the add tag dictionary button.
            void _handle_delete_tag(TagDictionary *p_dictionary, String p_tag_path);
            /// @brief Called when the user presses the remove tag dictionary button.
            /// @param p_dictionary
            void _handle_remove_tag_dictionary_pressed(TagDictionary *p_dictionary);
            /// @brief Called when the user presses the add tag button on the line.
            /// @param p_dictionary the dictionary to add the tag to.
            /// @param p_tag_path the path of the tag to add.
            void _handle_tag_add_requested(TagDictionary *p_dictionary, String p_tag_path);
            /// @brief Called when the user presses the edit tag button on the line.
            /// @param p_dictionary the dictionary to edit the tag to.
            /// @param p_tag_path the path of the tag to edit.
            void _handle_tag_edit_requested(TagDictionary *p_dictionary, String p_tag_path);
            /// @brief Called when the user presses the remove tag button.
            /// @param p_dictionary
            /// @param p_tag_path
            void _handle_remove_tag_requested(TagDictionary *p_dictionary, String p_tag_path);
        };
    }
} // namespace ggs

#endif