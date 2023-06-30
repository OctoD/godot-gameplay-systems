class_name SlideShow extends Node2D


## The initial slideshow in a videogame
##
## This is made easy


enum  {
	SKIP_PREV = -1,
	SKIP_NEXT = +1,
}

## Emitted when the slideshow is finished
signal finished()
## Emitted when a slide is skipped
signal slide_skipped(skip_direction: int)

@export_category("Presentation settings")
## Starts the presentation automatically when ready
@export var autoplay: bool = true
## How much long the slide is shown. It does not take in the [member SlideShow.slide_fade_duration] fadein/fadeout time.
@export_range(1.0, 10.0, 0.1) var slide_duration: float = 6.0
@export_range(0.0, 3.0) var slide_fade_duration: float = 1.0

## Current slide index.
var current_slide: int = 0
## Is [code]true[/code] if there is a previous slide, [code]false[/code] otherwise.
var has_prev: bool:
	get:
		return current_slide > 0 and slides.size() > 0
## Is [code]true[/code] if there is a next slide, [code]false[/code] otherwise.
var has_next: bool:
	get:
		return current_slide < slides.size()
## If [code]true[/code] the slide is playing, [code]false[/code] otherwise.
var playing: bool = true:
	get:
		return playing
	set(value):
		playing = value
		
		if value and autoplay:
			_handle_next_slide()
var slides: Array[Node2D]:
	get:
		var _s = [] as Array[Node2D]
		
		for child in get_children():
			if child is Node2D:
				_s.append(child)
		
		return _s


func _handle_slide_in(slide: Node2D) -> void:
	if slide.has_method("_slide_in"):
		slide.call("_slide_in")


func _handle_slide_out(slide: Node2D) -> void:
	if slide.has_method("_slide_out"):
		slide.call("_slide_out")


## Forcefully 
func _forcefully_fade_current() -> Tween:
	var tween = create_tween()
	var slide = slides[current_slide] as Node2D
	
	tween.tween_property(slide, "modulate:a", 0.0, slide_fade_duration)
	
	return tween


## Handles next slide. Called internally, use [method SlideShow.skip_to_prev], [method SlideShow.skip_to_next], [method SlideShow.skip_to_nth] or [method SlideShow.skip_all] 
func _handle_next_slide(direction: int = SKIP_NEXT) -> void:
	if current_slide >= slides.size():
		finished.emit()
	else:
		var tween = create_tween()
		var slide = slides[current_slide] as Node2D
		
		if slide == null:
			printerr("This should NEVER happen, what have you done?")
			_handle_next_slide()

		_handle_slide_in(slide)

		tween.tween_property(slide, "modulate:a", 1.0, slide_fade_duration)
		tween.tween_interval(slide_duration - (slide_fade_duration * 2))
		tween.tween_property(slide, "modulate:a", 0.0, slide_fade_duration)

		tween.finished.connect(func ():
			_handle_slide_out(slide)
			current_slide += direction
			_handle_next_slide()
		)

## Ready fn
func _ready() -> void:
	playing = autoplay
	
	for slide in slides:
		slide.modulate.a = 0.0


## Sets [member SlideShow.playing] to [code]true[/code]
func play() -> void:
	current_slide = 0
	playing = true


## Skips all slides and the [signal SlideShow.finished] is emitted.
## [br]
## GG mate, we worked hard for this.
func skip_all() -> void:
	skip_slide_to_nth(get_child_count() + 1)


## Skips to the next slide if any, otherwise the slideshow ends and the [signal SlideShow.finished] is emitted.
func skip_slide_to_next() -> void:
	skip_slide_to_nth(current_slide + 1)


## Skips to a nth slide. If out of bound, the slideshow ends and the [signal SlideShow.finished] is emitted.
func skip_slide_to_nth(slide_index: int) -> void:
	var direction = SKIP_NEXT if slide_index > current_slide else SKIP_PREV
	var inbound = slide_index >= 0 and slide_index <= slides.size()

	if not inbound:
		playing = false
		finished.emit()
		return
	
	if current_slide >= slides.size():
		finished.emit()
	else:
		var tween = create_tween()
		var slide = slides[current_slide] as Node2D

		slide_skipped.emit(direction)

		## Forcefully fades out current slide. You asked for it, do not complain plis.
		tween.tween_property(slide, "modulate:a", 0.0, slide_fade_duration)

		tween.finished.connect(func ():
			current_slide += direction
			_handle_slide_out(slide)
			_handle_next_slide(direction)
		)


## Skips to the previous slide if any, otherwise the slideshow ends and the [signal SlideShow.finished] is emitted.
func skip_slide_to_prev() -> void:
	skip_slide_to_nth(current_slide - 1)


