Camera Shake
============

Well, you all know what a camera shake is and why is it important (at least, for a majority of games).

To implement this feature, add a `CameraShake` node into your character and point to your current character's camera.

In the code, you can trigger the shake with

```gdscript
var strength = 1.0 # the maximum shake strenght. The higher, the messier
var shake_time = 1.0 # how much it will last
var shake_frequency = 250 # will apply 250 shakes per `shake_time`

$CameraShake.shake(strength, shake_time, shake_frequency)
```

It works on both `Camera2D` and `Camera3D` nodes.

You can browse the examples in [simple_2d](https://github.com/OctoD/godot-gameplay-attributes/blob/b376e4bed656bea643ac04e2d9e0f4098febfed4/examples/simple_2d_platformer/player/player.gd) or [doom_like](https://github.com/OctoD/godot-gameplay-attributes/blob/a51cdb77d8f6f58f7239f3cf952dc170a367e136/examples/doom_like_fps/player/Player.gd)

