⚔️ Gameplay Attributes ⚔️
=========================

Gameplay attributes are a set of nodes used to describe some
characters attributes for both 2D and 3D games made with Godot.

- [⚔️ Gameplay Attributes ⚔️](#️-gameplay-attributes-️)
- [Install](#install)
- [How it works](#how-it-works)
- [Api/methods/classes](#apimethodsclasses)
  - [GameplayAttributeMap](#gameplayattributemap)
      - [signals](#signals)
      - [methods](#methods)
- [Contribution](#contribution)
- [Licence](#licence)

# Install

Clone this repo inside your `addons` directory.

Enable this plugin by going to `project settings/plugins`.

Enjoy!

# How it works

It is very simple (dead simple enough I would say, longer to write and read than to use):

You in-game entities which should have some kind of attributes (life, endurance, mana, stamina, jump force etc) must have a `GameplayAttributeMap` node.

You have to specify both a `owning character` property assigning a node.

This node accepts an `AttributeTable` resource as value. This resource specifies which attributes the entity has.

Once specified a table, the inspector will show you these attributes, where you can set a:

- minimum value: which usually is zero
- maximum value: if you set it to zero, there will be not a maximum
- current value: the starting value for the entity

Now, to change these attributes, you will need some kind of "effects", in the form of `GameplayEffect` nodes.

A `GameplayEffect` requires an `AttributeTable` resource (like `GameplayAttributeMap`) and can specify an unlimited number of attributes alterations to it.

Once you setupped your `GameplayEffect`, you can add it to the character and here the magic happens, the attributes are changed magically.

You can use `EffectedArea2D` or `EffectedArea3D` to automatically apply effects on collisions (although you should extend them to validate to who you should apply the effect)

Done, more simple than previous versions.

You can check this repository example project to better understand and play directly with the addon.

# Api/methods/classes

## GameplayAttributeMap

#### signals

```gdscript
# called when an attribute changes
signal attribute_changed(attribute: AttributeSpec)
# called each time an attribute is changed by an attribute effect
attribute_effect_applied(attribute_effect: AttributeEffect)
# called each time an attribute effect is removed
attribute_effect_removed(attribute_effect: AttributeEffect)
# called when a gameplay effect is applied
effect_applied(effect: GameplayEffect)
```

#### methods

```gdscript
# applies an effect to the owning character
func apply_effect(effect: GameplayEffect) -> void:

# searches an attribute by name
# returns an instance of AttributeSpec or null if none
func get_attribute_by_name(attribute_name: String) -> AttributeSpec
```


# Contribution

Every contribution is really welcome, feel free to contribute!

You can open PR, issues or you can suggest features. Have a good day you wonderful Godot people!

# Licence

MIT licence
