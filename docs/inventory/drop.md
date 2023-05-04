Drop system
===========

Drop system is made easily with three nodes:

- Drop
- Drop2D
- Drop3D

#### Drop

`Drop` is the node responsible to actuate a drop. A drop consist in spawning a number `n` of `Item` resources in a 2D or 3D world.

To setup, it requires a `DropTable` resource and a path to the owner which drops. 
The path is the most important part since, if it inherits from `Node2D`, the drop will try to occur in a 2D world, 3D otherwise if it inherits from `Node3D`.

Once the `Drop.drop_items` method is called, the system will lookup for the nearest `Drop2D` or `Drop3D` node in the world and append the dropped `Item`s' scenes into it.

Note that all dropped items will inherit the `Drop` owner's position (the one specified as the Owning Node Path property `owning_node_path`).

Once the items are dropped in a Drop2D or Drop3D, the signal `item_dropped` is emitted by one of these nodes. The arguments passed to the signal callback are `Item` and the related `Node2D` or `Node3D` corresponding to the `Item.scene` property.