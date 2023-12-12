extends Node2D


const contributors_list = "https://api.github.com/repos/octod/godot-gameplay-systems/contributors?per_page=10000&page=1"


@onready var http_request: HTTPRequest = $HTTPRequest
@onready var contributors_container: VBoxContainer = $VBoxContainer/VBoxContainer


func _ready() -> void:
	http_request.request_completed.connect(func (result: int, response_code: int, headers: PackedStringArray, body: PackedByteArray):
		_render_contributors(JSON.parse_string(body.get_string_from_utf8()))
	)
	http_request.request(contributors_list)


func _render_contributors(json: Variant) -> void:
	if json == null:
		return
		
	for contributor in json:
		if str(contributor.login).to_lower() == "octod":
			continue
		
		var label = Label.new()
		
		label.text = contributor.login
		label.horizontal_alignment = HORIZONTAL_ALIGNMENT_CENTER
		label.theme_type_variation = "HeaderMedium"
		
		contributors_container.add_child(label)
