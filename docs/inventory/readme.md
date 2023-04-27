Inventory System
================

Table of contents

#### Nodes

- [Equipment](equipment.md)
- [Inventory](inventory.md)
- [EquippedItem3D](equipped_item_3d.md)
- [PickableArea2D](pickable_area_2d.md)
- [PickableArea3D](pickable_area_3d.md)

#### Resources

- [Item](item.md)
- [EquipmentSlot](equipment_slot.md)

## Taggings system

Both `Inventory` and `Equipment` nodes have a tagging system bound to them. Items can be activated, equipped, removed based on their tags requirements. 

For example, an Item called `shotgun` with `tags_required_to_equip` containing `has.shotgun` will be equipped only if `Equipment` has a tag `has.shotgun` and the item itself is allowed in at least one `EquipmentSlot`. 

If the item has a tag `tags_required_to_activate` containing `can.shoot` the `Inventory` or the `Equipment` will be able to activate this item only if the `can.shoot` tag is present.

Both `Inventory` and `Equipment` can "talk" to each other if both node_paths are specified, so you can have an automatic equip item on pick.

## Pickable items

There are two premade nodes (one for 2D and another one for 3D worlds) which enables you to pickup items.

