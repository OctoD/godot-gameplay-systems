Equipment
=========

The Equipment node is responsible for handling equipping and unequipping some items.

A lot of games have an equipment system (from classic Doom, to Sea Of Thieves, to Diablo-like etc).

The difference between the equipment and the inventory rely on the capability of organizing and activating a single item per slot.

The Equipment is structured in this way:

```
Equipment
  EquipmentSlot
    Item
    Item
    Item
  EquipmentSlot
    Item
    Item
  EquipmentSlot
    Item
  ...
```

An Equipment can have multiple `EquipmentSlot` Resources. Each represents a usable slot of your equipment (it could be a radial menu or an equipment as seen in Borderlands series).

Each `EquipmentSlot` can whitelist one or more `Item` resources to determine which `Item` can be equipped in a certain slot.

An `Item` can be equipped or not based on it's own tags requiring.

## EquipmentSlot

An Equipment slot is a `Resource` which can accept many `Item`.

Based on the items it accept, you can programmatically choose to equip an item.

## Example

A good example of the use of equipment is the `doom_like` example located in `examples` folder.