#include "KeyCallbackEvent.h"

namespace ErmineEventSystem
{
	////////////////////////////////////////////////////////
	//KeyCallback Event Class///////////////////////////////
	////////////////////////////////////////////////////////

	KeyCallbackEvent::KeyCallbackEvent(int key, int scancode, int action, int mods)
		:
		key(key),
		scancode(scancode),
		action(action),
		mods(mods)
	{}

	std::unique_ptr<KeyCallbackEvent> KeyCallbackEvent::GenerateEvent(int key, int scancode, int action, int mods)
	{
		std::unique_ptr<KeyCallbackEvent> ptr = std::make_unique<KeyCallbackEvent>(key,scancode,action,mods);
		return std::move(ptr);
	}

	////////////////////////////////////////////////////////
	//KeyCallback Event Subscription Class//////////////////
	////////////////////////////////////////////////////////


	KeyCallbackEventSubscription::KeyCallbackEventSubscription(std::function<void(KeyCallbackEvent*)> CallableObject)
		:
		CallableObject(CallableObject)
	{}

	KeyCallbackEventSubscription::KeyCallbackEventSubscription(std::function<void(KeyCallbackEvent*)> CallableObject, 
															   std::atomic<bool> & Flag)
		:
		EventSubscription(Flag),
		CallableObject(CallableObject)
	{}

	EventType KeyCallbackEventSubscription::GetEventSubscriptionType()
	{
		return EventType::KeyCallbackEvent;
	}
}
