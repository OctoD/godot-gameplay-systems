extends GutTest


func _add_slides(slideshow: SlideShow, count: int) -> void:
	for x in range(0, count):
		var slide = Node2D.new()
		slide.name = "Slide" + str(count)
		slideshow.add_child(slide)


func _slideshow() -> SlideShow:
	var slideshow = SlideShow.new()
	add_child_autofree(slideshow)
	return slideshow



func test_normal_flow() -> void:
	var s = _slideshow()

	watch_signals(s)

	s.slide_duration = 1.0
	s.slide_fade_duration = 1.0
	s.autoplay = true
	
	assert_eq(s.current_slide, 0, "it should always start from the beginning")
	
	_add_slides(s, 3)

	s.skip_slide_to_nth(0)

	assert_eq(s.current_slide, 0, "even after adding slides programmatically, it should always start from the beginning")

	s.skip_slide_to_next()

	assert_signal_not_emitted(s, "finished", "finished should not have been emitted")
	assert_signal_emitted(s, "slide_skipped", "slide_skipped should have been emitted")

	s.skip_slide_to_next()
	s.skip_slide_to_next()
	s.skip_slide_to_next()
	s.skip_slide_to_next()
	s.skip_slide_to_next()
	
	await wait_seconds(4.0)

	assert_signal_emitted(s, "finished", "finished should have been emitted")
	
	# wow, it worked


func test_trying_to_break_everything() -> void:
	var s = _slideshow()

	watch_signals(s)
	
	# Let's add unusable children
	
	s.add_child(Node3D.new())
	s.add_child(Node.new())
	
	# copy and paste of the "good" scenario test

	s.slide_duration = 1.0
	s.slide_fade_duration = 1.0
	s.autoplay = true

	assert_eq(s.current_slide, 0, "it should always start from the beginning")
	
	_add_slides(s, 3)
	
	assert_eq(s.slides.size(), 3, "slides should be only 3")

	s.skip_slide_to_nth(0)

	assert_eq(s.current_slide, 0, "even after adding slides programmatically, it should always start from the beginning")

	s.skip_slide_to_next()

	assert_signal_not_emitted(s, "finished", "finished should not have been emitted")
	assert_signal_emitted(s, "slide_skipped", "slide_skipped should have been emitted")

	s.skip_slide_to_next()
	s.skip_slide_to_next()
	s.skip_slide_to_next()
	s.skip_slide_to_next()
	s.skip_slide_to_next()
	
	await wait_seconds(4.0)

	assert_signal_emitted(s, "finished", "finished should have been emitted")

