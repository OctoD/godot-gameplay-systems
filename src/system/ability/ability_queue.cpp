#include "ability_queue.h"

using namespace ggs;

void AbilityQueueItem::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("can_be_dequeued"), &AbilityQueueItem::can_be_dequeued);
	ClassDB::bind_method(D_METHOD("increment_lifetime", "tick"), &AbilityQueueItem::increment_lifetime);
	ClassDB::bind_method(D_METHOD("get_ability"), &AbilityQueueItem::get_ability);
	ClassDB::bind_method(D_METHOD("set_ability", "ability"), &AbilityQueueItem::set_ability);
}

AbilityQueueItem::AbilityQueueItem()
{
}

AbilityQueueItem::~AbilityQueueItem()
{
}

bool AbilityQueueItem::can_be_dequeued() const
{
	return lifetime >= ability->get_cooldown();
}

void AbilityQueueItem::increment_lifetime(float tick)
{
	lifetime += tick;
}

Ability *AbilityQueueItem::get_ability() const
{
	return ability;
}

void AbilityQueueItem::set_ability(Ability *p_ability)
{
	ability = p_ability;
	lifetime = p_ability->get_cooldown();
}

void AbilityQueue::_bind_methods()
{
	/// binds methods
	ClassDB::bind_method(D_METHOD("can_enqueue", "ability"), &AbilityQueue::can_enqueue);
	ClassDB::bind_method(D_METHOD("can_dequeue", "ability"), &AbilityQueue::can_dequeue);
	ClassDB::bind_method(D_METHOD("dequeue", "ability"), &AbilityQueue::dequeue);
	ClassDB::bind_method(D_METHOD("enqueue", "ability"), &AbilityQueue::enqueue);
	ClassDB::bind_method(D_METHOD("process", "delta"), &AbilityQueue::process);

	/// signals bindings
	ADD_SIGNAL(MethodInfo("ability_enqueued", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
	ADD_SIGNAL(MethodInfo("ability_dequeued", PropertyInfo(Variant::OBJECT, "ability", PROPERTY_HINT_RESOURCE_TYPE, "Ability")));
}

AbilityQueue::AbilityQueue()
{
	queue = TypedArray<AbilityQueueItem>();
}

AbilityQueue::~AbilityQueue()
{
}

bool AbilityQueue::can_enqueue(Ability *p_ability)
{
	return p_ability != nullptr && p_ability->get_cooldown() - 1.0f > 0.05f;
}

bool AbilityQueue::can_dequeue(Ability *p_ability)
{
	for (int i = queue.size() - 1; i >= 0; i--)
	{
		AbilityQueueItem *item = cast_to<AbilityQueueItem>(queue[i]);

		if (item != nullptr && item->get_ability()->get_ability_name() == p_ability->get_ability_name())
		{
			return true;
		}
	}
	
    return false;
}

void AbilityQueue::dequeue(Ability *p_ability)
{
	for (int i = queue.size() - 1; i >= 0; i--)
	{
		AbilityQueueItem *item = cast_to<AbilityQueueItem>(queue[i]);

		if (item != nullptr && item->get_ability()->get_ability_name() == p_ability->get_ability_name())
		{
			queue.remove_at(i);
			emit_signal("ability_dequeued", p_ability);
		}
	}
}

void AbilityQueue::enqueue(Ability *p_ability)
{
	if (can_enqueue(p_ability))
	{
		AbilityQueueItem *item = memnew(AbilityQueueItem);
		item->set_ability(p_ability);
		queue.push_back(item);
		emit_signal("ability_enqueued", p_ability);
	}
}

bool AbilityQueue::has_enqueued_ability(Ability *p_ability)
{
	for (int i = queue.size() - 1; i >= 0; i--)
	{
		AbilityQueueItem *item = cast_to<AbilityQueueItem>(queue[i]);

		if (item != nullptr && item->get_ability()->get_ability_name() == p_ability->get_ability_name())
		{
			return true;
		}
	}
	
    return false;
}

void AbilityQueue::process(float delta)
{
	for (int i = queue.size() - 1; i >= 0; i--)
	{
		AbilityQueueItem *item = cast_to<AbilityQueueItem>(queue[i]);

		if (item != nullptr)
		{
			item->increment_lifetime(delta);

			if (item->can_be_dequeued())
			{
				queue.remove_at(i);
			}
		}
	}
}