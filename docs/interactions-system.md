Interactions system
===================

The interaction system is built upon three nodes: 

- the `InteractionManager`, which is a node that starts an `Interaction` on a focused `InteractableArea2D` or `InteractableArea3D` using an `InteractionRayCast2D` or `InteractionRayCast3D` to detect it
- the `InteractableArea2D` or `InteractableArea3D`, which is an area detectable by the `InteractionRayCast2D` or `InteractionRayCast3D`
- the `InteractionRayCast2D` or `InteractionRayCast3D`, which is the raycast responsible of detecting the first interactable area in line

An `Interaction` resource is required. This resource can add and/or remove several tags (`Array[String]`) when started or ended.

This resource can also handle while the interaction is performed 

- the `_input` overriding the method `handle_input`.
- the `_process` overriding the method `handle_process`.
- the `_physic_process` overriding the method `handle_physic_process`.

For a simple example of how it works, you can browse the `examples/sot_like` example.