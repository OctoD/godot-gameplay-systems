Point and click nodes
=====================

Point and click nodes are simple 2D/3D nodes which expose an easy-to-use api to handle
point and click games like ARPG.

Both share the same API.

Usually, you should put them as childs of a `CharacterBody2D` or `CharacterBody3D`.

These character nodes require a `NavigationAgent2D` or `NavigationAgent3D` as direct child and the world requires a `NavigationRegion2D` or `NavigationRegion3D` to work properly.

Once you have set these nodes, you have to link them inside the `PointAndClick2D` or `PointAndClick3D` and then you can make your character moving like this:

```gdscript
class_name MyPlayer extends CharacterPlayer2D


@onready var point_and_click_2d: PointAndClick2D = $PointAndClick2D


func _input(event: InputEvent) -> void:
    if event.is_action_pressed("click_action"):
        point_and_click_2d.set_new_movement_position()
```

The character should be moving correcly.

In the 3D version, the api is the same but you must remember to bake the `NavigationRegion3D`, otherwise it will not work.

To see how them work, you can browse both

- examples/diablo_like/player/diablo_like_player.gd
- examples/top_down_3d/player/top_down_player.gd


## Handling clicks in multiplayer

Remember to set the character as owned by your current peer, then add a `MultiplayerSynchronizer` node and replicate the `NavigationAgent2/3D` `target` property.

It should work seamlessly (otherwise I will implement an ad-hoc solution for it).