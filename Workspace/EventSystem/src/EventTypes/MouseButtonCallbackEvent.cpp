#include "MouseButtonCallbackEvent.h"

namespace ErmineEventSystem
{
	////////////////////////////////////////////////////////
	//MouseButtonCallback Event Class///////////////////////
	////////////////////////////////////////////////////////
	MouseButtonCallbackEvent::MouseButtonCallbackEvent(int button, int action, int mods)
		:
		button(button),
		action(action),
		mods(mods)
	{}

	std::unique_ptr<MouseButtonCallbackEvent> MouseButtonCallbackEvent::GenerateEvent(int button, int action, int mods)
	{
		std::unique_ptr<MouseButtonCallbackEvent> ptr = std::make_unique<MouseButtonCallbackEvent>(button, action, mods);
		return std::move(ptr);
	}

	////////////////////////////////////////////////////////
	//MouseButtonCallback Event Subscription Class//////////
	////////////////////////////////////////////////////////

	MouseButtonCallbackEventSubscription::MouseButtonCallbackEventSubscription(std::function<void(MouseButtonCallbackEvent*)> CallableObject)
		:
		CallableObject(CallableObject)
	{}

	MouseButtonCallbackEventSubscription::MouseButtonCallbackEventSubscription(std::function<void(MouseButtonCallbackEvent*)> CallableObject, std::atomic<bool>& Flag)
		:
		EventSubscription(Flag),
		CallableObject(CallableObject)
	{}

	EventType MouseButtonCallbackEventSubscription::GetEventSubscriptionType()
	{
		return EventType::MouseButtonCallbackEvent;
	}
}
