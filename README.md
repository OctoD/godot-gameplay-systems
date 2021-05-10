Gameplay Attributes
===================

Gameplay attributes are a set of nodes used to describe some
characters attributes for both 2D and 3D games made with Godot.

- [Gameplay Attributes](#gameplay-attributes)
- [Install](#install)
- [How it works](#how-it-works)
  - [Example: creating your first Attributes map](#example-creating-your-first-attributes-map)
  - [Creating your own effects](#creating-your-own-effects)
- [Prebuilt gameplay effects](#prebuilt-gameplay-effects)
  - [AttributeConsumeGameplayEffect](#attributeconsumegameplayeffect)
  - [AttributeRegenGameplayEffect](#attributeregengameplayeffect)
  - [DamageGameplayEffect](#damagegameplayeffect)
  - [RestoreGameplayEffect](#restoregameplayeffect)
- [Docs](#docs)
  - [GameplayAttributesMap](#gameplayattributesmap)
      - [methods](#methods)
  - [GameplayAttribute](#gameplayattribute)
      - [members](#members)
  - [GameplayEffect](#gameplayeffect)
      - [methods](#methods-1)
- [Ideas for a next releases](#ideas-for-a-next-releases)
- [Contribution](#contribution)
- [Licence](#licence)

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
func _on_attribute_changed(attribute) -> void:
  print(attribute.name + ":" + str(attribute.current_value))
```

Start your game and watch your mana regen!

## Creating your own effects

`GameplayEffects` (or effects from now) are the primary way to modify attributes.

An effect is simply a node which can be activated (and deactivated) under some
circumstances:

- Immediate activation (`EffectActivationEvent.ImmediateActivation`)
- Attribute changed activation (`EffectActivationEvent.AttributeChanged`)

There are two main effect categories: instants and timed-based.

An instant effect could be a jump, a damage, a permanent boost etc.

A timed effect could be a stamina regen, mana regen, stamina leech, bleeding etc.

There are three functions to take care in an effect:

- `apply_effect` is called when the effect is ready to be applied
- `should_activate` is called when an effect could be applied
- `should_deactivate` is called when an effect could be stopped and removed from it's parent

`apply_effect() -> void` takes no argument and must return nothing. Inside this function you can apply your damage, boost, you can move your character and so on

`should_activate(event_id: int) -> bool` takes an `int` argument (which is the `EffectActivationEvent` enum) to determine when the effect has tried to activate itself.

`should_deactivate` will remove the effect from it's parent if it returns `true`

At this point, I'd suggest you to create your own effects inheriting the existing ones:

- `AttributeConsumeGameplayEffect` applies a timed attribute consumption
- `AttributeRegenGameplayEffect` applies a timed attribute regeneration
- `DamageGameplayEffect` calculates the instant damage with min/max parameters

You can of course create you own starting from the base class `GameplayEffect` or `TimedGameplayEffect`

--------

# Prebuilt gameplay effects

## AttributeConsumeGameplayEffect

Inherits from `TimedGameplayEffect`. You can specify an attribute to consume over time.

Ideal for all *dot* (damage over time) damages

## AttributeRegenGameplayEffect

Inherits from `TimedGameplayEffect`. You can specify an attribute to regenerate over time.

Ideal for:
- mana regen
- slow health regen
- stamina regen

## DamageGameplayEffect

Lowers a `GameplayAttribute` current_value by a given value. 

Ideal for every immediate malus like:
- attributes nerfs
- damage
- fall damage

## RestoreGameplayEffect

Increments a `GameplayAttribute` current_value by a given value.

Ideal for:
- Health restore (potions, medikits, whateverkit)
- Attributes restore
- Xp gain

--------

# Docs

## GameplayAttributesMap

`GameplayAttributesMap` allows you to connect to two `signal`s:

- `attribute_changed` emitted when an attribute changes a current or maximum value. A dictionary will be passed with the previous max/current values and the newly set max/current values
- `effect_activated` emitted when an effect decides to emit the same signal (useful for ui notification)
- `effect_applied` emitted when an effect decides to emit the same signal (useful for ui notification)
- `effect_deactivated` emitted when an effect decides to emit the same signal (useful for ui notification)


#### methods

Here are the public methods in `GameplayAttributesMap`

**`apply_effect(effect: GameplayEffect) -> void`**

Apply an effect

**`get_attribute(attribute_name: String) -> GameplayAttribute`**

Returns a `GameplayAttribute` if there's one named like `attribute_name` inside the `GameplayAttributesMap` tree.

**`get_attribute_value(attribute_name: String) -> float`**

Returns a `GameplayAttribute` current_value if there's one named like `attribute_name` inside the `GameplayAttributesMap` tree.

**`get_attribute_max_value(attribute_name: String) -> float`**

Returns a `GameplayAttribute` max_value if there's one named like `attribute_name` inside the `GameplayAttributesMap` tree.

If no attribute is found, returns 0.0

**`get_effect(effect_name: String) -> GameplayAttribute`**

Returns a `GameplayEffect` if there's one named like `effect_name` inside the `GameplayAttributesMap` tree.

**`get_attributes() -> Array`**

Returns an `Array` of `GameplayAttribute` nested inside the `GameplayAttributesMap` tree.

**`get_effects() -> Array`**

Returns an `Array` of `GameplayEffect` nested inside the `GameplayAttributesMap` tree.

**`play_effect(effect_name: String) -> bool`**

Restarts a `GameplayEffect`  if there's one named like `effect_name` inside the `GameplayAttributesMap` tree.

**`pause_effect(effect_name: String) -> bool`**

Pauses a `GameplayEffect`  if there's one named like `effect_name` inside the `GameplayAttributesMap` tree.

----------

## GameplayAttribute

`GameplayAttribute` allows you to connect to one `signal`:

- `attribute_changed` emitted when the current value or the maximum value of an attribute
changes

#### members

**`current_value`** (`float`)

describes how the attribute is represented at the current time

**`max_value`** (`float`)

describes the attribute's max value (like max health, max mana etc, max level etc)

----------

## GameplayEffect

`GameplayEffect` allows you to connect to three `signal`s:

- `effect_activated` you can emit it when the effect is activated inside the `should_activate` method
- `effect_applied` you can emit it when the effect is applied inside the `apply_effect` method
- `effect_deactivated` you can emit it when the effect is deactivated inside the `should_deactivate` method

#### methods

Here are the `GameplayEffect` public methods



**`apply_effect`**

This is where your effect logic should stay. 

If you need to notify the owning character, emit the signal `effect_applied`



**`setup_effect`** 

This is where you setup your effect. It is called during the `_ready` function but only when in game.


**get_kinematic_owner**

Returns the `KinematicBody` or `KinematicBody3D` owner of the `GameplayAttributeMap` which contains the effect.



**`get_parent_attribute_map`**

Returns the parent `GameplayAttributeMap`



**`should_activate`**

Should return `true` when the effect can be activated. 

If you need to notify the owning character, emit the signal `effect_activated`



**`should_deactivate`**

Should return `true` when the effect can be activated. 

If you need to notify the owning character, emit the signal `effect_deactivated`



# Ideas for a next releases

- [ ] Adds a serialize/deserialize function to `GameplayAttributeMap` node (for savegames, remote savegames etc)
- [ ] Adds multiplayer functionalities to `GameplayAttributeMap` node
- [ ] Adds high level configurable `GameplayAttributeMap` (maybe with a tool? So you can config attributes via parameters on `GameplayAttributeMap`)

# Contribution

Every contribution is really welcome, feel free to contribute!

You can open PR, issues or you can suggest features

# Licence

MIT licence