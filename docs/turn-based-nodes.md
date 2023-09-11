Turn based nodes
================

Turn based nodes are nodes that can be used to create turn based games. 

To start adding functionalities to your game, you can add a `TurnBasedGame` node to your scene. This node should be at the highest level of your hierarchy. It will be used to manage the turns properly.

Then you should add a `TurnSubscriber` to each node which should be notified when a turn starts or ends.

This node has a priority property. The nodes with the highest priority will start their turns first. If two nodes have the same priority, the one that was added first will start its turn first.

To get the `TurnBasedGame` node, you have to use the singleton `TurnManager`.

This has a method which returns the `TurnBasedGame` node. You can use it like this:

```gdscript
# To start a turn sequence
var turn_based_game = TurnManager.get_turn_based_game()
turn_based_game.start_turn_sequence();

# To end a turn sequence
turn_based_game.end_turn_sequence();
```

Each `TurnSubscriber` can terminate it's own turn by calling their `end_turn` method.

```gdscript
# To end a turn
self.end_turn();
```
