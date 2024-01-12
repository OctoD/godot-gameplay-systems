#ifndef GGS_ABILITY_QUEUE_H
#define GGS_ABILITY_QUEUE_H

#include <godot_cpp/classes/ref_counted.hpp>

#include "ability.h"

using namespace godot;

namespace ggs
{
	/// @brief An item in the ability queue.
	class AbilityQueueItem : public RefCounted
	{
		GDCLASS(AbilityQueueItem, RefCounted);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief How many times the ability has been called.
		float lifetime;
		/// @brief The ability.
		Ability *ability;

	public:
		/// @brief Default constructor.
		AbilityQueueItem();
		/// @brief Default destructor.
		~AbilityQueueItem();

		/// @brief Returns if the ability can be dequeued (it reached it's lifetime).
		/// @return True if the ability can be dequeued, false otherwise.
		bool can_be_dequeued() const;
		/// @brief Increments the lifetime of the ability.
		/// @param tick The amount to increment the lifetime by.
		void increment_lifetime(float tick);
		/// @brief Returns the ability.
		/// @return The ability.
		Ability *get_ability() const;
		/// @brief Sets the ability.
		/// @param p_ability The ability.
		void set_ability(Ability *p_ability);
	};

	/// @brief The ability queue.
	class AbilityQueue : public RefCounted
	{
		GDCLASS(AbilityQueue, RefCounted);

	protected:
		/// @brief Binds methods to Godot.
		static void _bind_methods();
		/// @brief The queue of abilities.
		TypedArray<AbilityQueueItem> queue;

	public:
		/// @brief Default constructor.
		AbilityQueue();
		/// @brief Default destructor.
		~AbilityQueue();

		/// @brief Returns if the ability can be enqueued.
		/// @param p_ability The ability to check.
		/// @return True if the ability can be enqueued, false otherwise.
		bool can_enqueue(Ability *p_ability);
		/// @brief Returns if the ability can be dequeued.
		/// @param p_ability The ability to check.
		/// @return True if the ability can be dequeued, false otherwise.
		bool can_dequeue(Ability *p_ability);
		/// @brief Dequeues an ability.
		/// @param p_ability The ability to dequeue.
		void dequeue(Ability *p_ability);
		/// @brief Enqueues an ability.
		/// @param p_ability The ability to enqueue.
		void enqueue(Ability *p_ability);
		/// @brief Returns if the ability is enqueued.
		/// @param p_ability The ability to check.
		/// @return True if the ability is enqueued, false otherwise.
		bool has_enqueued_ability(Ability *p_ability);
		/// @brief The process function.
		/// @param delta The time since the last frame.
		void process(float delta);
	};
}

#endif
