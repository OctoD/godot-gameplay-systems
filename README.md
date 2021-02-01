Gameplay Attributes
===================

Gameplay attributes are a set of nodes used to describe some
characters attributes.

# Install

Clone this repo inside your `addons` directory.

Enable this plugin by going to `project settings/plugins`.

Enjoy!

# How it works

There are three main **nodes** types:

- `GameplayAttributesMap`: it is the wrapper around a set of attributes
- `GameplayAttribute`: describes an attribute (current value, max value)
- `GameplayEffect`: is where the magic happens, it describes how attributes work
together and how to change them.

A character should have one `GameplayAttributesMap`. 

A `GameplayAttributesMap` can have many `GameplayAttribute` (like health, mana, shield, movement speed, strength etc).

A character could be affected by many `GameplayEffect`s (like direct damage, attributes regen over time, attributes consumption over time etc)

## Example: creating your first Attributes map

The first thing I'd suggest, is to create a new `scene`, save it and name **CharacterAttributes** which inherits directly from `GameplayAttributesMap`.

Add some `GameplayAttribute` to your new scene and rename them to `Health` and `Mana`.

Set Health params to `50`/`50` (**Current value**/**Maximum Value**)
Set Mana params to `5`/`50` (**Current value**/**Maximum Value**)

Now add an `AttributeRegenGameplayEffect` node to your scene, and set the **Attribute Name** to `Mana`. Change the **Increment Per Second** to 1

Add your new created `scene` **CharacterAttributes** to your character.

Connect `CharacterAttributes`'s signal `attribute_changed` to a function

```gdscript
func _on_attribute_changed(attribute, value, attribute_map) -> void:
  print(attribute.attribute_name + ":" + str(attribute.current_value))
```

Start your game and watch your mana regen!

# Contribution

Every contribution is really welcome, so feel free to contribute!
