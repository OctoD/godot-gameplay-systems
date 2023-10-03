extends EditorPlugin


const slideshow_script = preload("./slide_show.gd")


func _enter_tree() -> void:
	add_custom_type("SlideShow", "Node2D", slideshow_script, null)
	
	
func _exit_tree() -> void:
	remove_custom_type("SlideShow")

