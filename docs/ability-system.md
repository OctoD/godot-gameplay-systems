Ability System
==============

The Ability System (AS) is a set of nodes and resources useful to define and handle your abilities.

It's reccomended to use it with the `GameplayAttributeMap` for a better and easier result, but it's not required.

There are three main concepts to grasp:

- `Ability` is the resource type which describes when an ability can be activated (using a tagging system) and what can do (using it's own methods).
- `AbilityContainer` is the node which adds the capability to contain and use abilities.
- `Tags` are an array of strings, used to sets arbitrary attributes to an `AbilityContainer` (like dead, jumped, reloading, cooldowns, shot etc)

`Ability` and `AbilityContainer` talk to each other using signals (internally) and a tagging system. It's easier to explain with a simple example (see below).

All abilities must be granted to the owning `AbilityContainer` and can be granted only if `AbilityContainer` has all the tags required by `Ability.grant_tags_required`.

In this way, you can create a skill tree by simply adding tags.

You can also revoke abilities from an `AbilityContainer` at any time.

## Example/Tutorial

You have your character, which can move (thanks to `CharactedBody2D`/`CharactedBody3D`) and which can perform certain actions. 

One action could be the ability to cast a fireball, while another one could be the ability to resurrect itself when it's dead.

Using a traditional approach, you would have to write **every** behavior using imperative code or using a state machine.

With the **AS**, you can describe what an ability can do and at what circumstance it can be activated, blocked, cancelled or ends.

This example will use both `AS` and `GameplayAttributes` to work.

#### Pre-requisites.

Create a scene called `Character` (which extends `CharactedBody2D` or `CharactedBody3D`) and use the base template.

Bind one key to kill you character (like `0` to `killme` command) and another one to resurrect (like `r` to `resurrect` command).

Add a `GameplayAttributeMap` node and an `AbilityContainer` node.

Set the `GameplayAttributeMap.owning_character` to the parent node (`CharactedBody2D` or `CharactedBody3D`) and set `AbilityContainer.gameplay_attribute_map` selecting the `GameplayAttributeMap` node.

Now create an `AttributeTable` resource and add `health`.

Load the previously created attribute table from the `GameplayAttributeMap`.

Sets the attribute values to:

- maximum: 5
- minimum: 0
- current: 5

It's now time to write your first ability.

#### Writing our first ability

Let's start creating the resurrection ability (the easiest between the two).

First you need to create a script (gdscript) extending the class `Ability`

```gdscript
@tool
class_name Resurrect extends Ability
```

Then you have to implement the `activate` method (which is called when the ability activates).


```gdscript
class_name Resurrect extends Ability

@export_group("Health", "health_")
@export var health_minimum_restored := 2.0
@export var health_maximum_restored := 2.0

func activate(event: ActivationEvent) -> void:
  # remember to call always parent functions
  super.activate(event) 

  # let's check if the character is bound correctly to the [GameplayAttributeMap] node
  if event.character:
    # creating a new [GameplayEffect] node
    var effect = GameplayEffect.new()
    # creating a new [AttributeEffect] resource
    var health_effect = AttributeEffect.new()

    # assigning values. Presuming your [GameplayAttributeMap] has an attribute called health.
    health_effect.attribute_name = "health"
    # assigning export var (optional, you can even hardcode stuff here)
    health_effect.minimum_value = health_minimum_restored
    health_effect.maximum_value = health_maximum_restored

    # adding the affected attribute to the [GameplayEffect]
    effect.attributes_affected.append(heath_effect)

    # adding the effect to the character, so the [GameplayAttributeMap] can do the job for you to update the attribute(s) and do the effect handling.
    event.character.add_child(effect)


func can_activate(event: ActivationEvent) -> bool:
  var health_attribute = event.get_attribute("health")

  if health_attribute:
    return super.can_activate(event) and health_attribute.current_buffed_value <= 0.0
  else:
    return super.can_activate(event)
```

Now on your `AbilityContainer` node, click the **add element** button under the abilities parameter, choose `Resurrect` and then we are ready to configure it.

#### Configuring an ability

An ability surely has to be activated only when something allows it (if your character is alive there's no need to resurrect it again).

There's a simple but efficient way to handle these behaviors: tags.

A tag is a `String`, and you can add many you want based on your behaviors.

These are the tag families for an ability (all properties start with `tags_`):

- **tags_activation**: Tags added once ability has been activated.
- **tags_activation_required**: Tags required for activation. The ability cannot be activated if the `AbilityContainer` does not have all the tags provided here
- **tags_block**: Blocks execution if ore or more tags are contained by `AbilityContainer`
- **tags_cancellation_required**: Tags required for cancellation.
- **tags_cooldown_start**: Tags added when cooldown is started.
- **tags_cooldown_end**: Tags added when cooldown is ended.
- **tags_end_blocking**: Tags which will block the end of an `Ability`.
- **tags_to_remove_on_activation**: Tags which will be removed on activation.
- **tags_to_remove_on_block**: Tags which will be removed on block.
- **tags_to_remove_on_cancellation**: Tags which will be removed on cancellation.
- **tags_to_remove_on_cooldown_start**: Tags which will be removed when a cooldown start.
- **tags_to_remove_on_cooldown_end**: Tags which will be removed when a cooldown end.
- **tags_to_remove_on_end**: Tags which will be removed when an ability ends.

In order to proceed with our example, click the `AbilityContainer` node, then select the added ability and expand it. 

You will see all these tags under the `Tags` group.

For sake of gameplay, we want to add some tags in order to block the resurrection ability.

Let's start adding `resurrecting` to `tags_block` (It will mean that the ability is running, so we cannot run it twice or more).

Add `dead` and `resurrect.start` to `tags_activation_required`.

Add `resurrecting` to `tags_cooldown_start`.

Add `dead`, `resurrect.start` and `resurrecting` to `tags_to_remove_on_end`

This way we are telling that the ability requires both `dead` and `resurrect.start` to be activated, and cannot be activated anymore if the container is tagged with `resurrecting`. 

The removal of `resurrect.start` inside `tags_to_remove_on_activate` and `dead`, `resurrecting` inside `tags_to_remove_on_end` are necessary, otherwise the ability will be used only once (bug or feature? Depends on your needs).

Then, open the group `Cooldown` and set it to a value you like (use `3.0`, just for testing sake).

> Important: cooldown will not be taken in consideration if the proper tags are not set.

It's time to test it.

#### Activating your first ability

Inside your character, assign the `AbilityContainer` and `GameplayAttributeMap` to variables


```gdscript
@onready var ability_container: AbilityContainer = $AbilityContainer
@onready var gameplay_attribute_map: GameplayAttributeMap = $GameplayAttributeMap
```


and then where you handle input events add these lines of code

```gdscript
if Input.is_action_pressed("killme"):
  if not ability_container.has_tag("dead"):
    ability_container.add_tag("dead")
    gameplay_attribute_map.get_attribute_by_name("health").current_value = 0.0

if Input.is_action_pressed("resurrect"):
  # adds the tag, so if the ability container contains the "dead" tag too, the ability will be activated
  ability_container.add_tag("resurrect.start")
  ability_container.activate_many()
```

To see how it works, you can check the example in the example folder.

#### Searching and activating granted abilities

You can of course activate abilities programmatically. Let's make another (shorter example):

###### Searching for an ability by a predicate

```gdscript
var resurrect: Ability:
  get:
    if ability_container == null:
      return null

    return ability_container.find_by(func (x): return x is Resurrect)
```

###### Filtering all abilities by a predicate

```gdscript
var dead_tag_abilities: Array[Ability]:
  get:
    if ability_container == null:
      return null
    
    return ability_container.filter_abilities(func (x): return x.tags_required.has("dead"))
```

###### Activating a single ability

```gdscript
func activate_dead_abilities() -> void:
  for ability in dead_tag_abilities:
    # note, always check if an ability is granted or not. 
    # A character like in diablo2 could have dozen of abilities, 
    # but a player should be able to use them if they are not 
    # granted by purchasing them using skill points
    if ability_container.has_ability(ability):
      ability_container.activate_one(ability)
```

