#include "RecieverComponent.h"

#include "../EventTypes/TestConcreteEvent.h"
#include "../EventTypes/KeyCallbackEvent.h"
#include "../EventTypes/CharacterCallbackEvent.h"
#include "../EventTypes/CursorPositionCallbackEvent.h"
#include "../EventTypes/MouseButtonCallbackEvent.h"
#include "../EventTypes/ScrollCallbackEvent.h"

void ErmineEventSystem::RecieverComponent::Bind(std::function<void(Event*)> Callable, std::atomic<bool>& SwitchTOControlIfAnEventCanBeExecuted, EventType SubscriptionType)
{
	auto station = ErmineEventSystem::EventBroadcastStation::GetStation(); //Gets a Line To The Station

	if (SubscriptionType == EventType::ConcreteEvent)
	{
		std::unique_ptr<ErmineEventSystem::ConcreteEventSubscription> Obj = std::make_unique<ErmineEventSystem::ConcreteEventSubscription>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
	}
	else if (SubscriptionType == EventType::KeyCallbackEvent)
	{
		std::unique_ptr<ErmineEventSystem::KeyCallbackEventSubscription> Obj = std::make_unique<ErmineEventSystem::KeyCallbackEventSubscription>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
	}
	else if (SubscriptionType == EventType::CharacterCallbackEvent)
	{
		std::unique_ptr<ErmineEventSystem::CharacterCallbackEventSubscription> Obj = std::make_unique<ErmineEventSystem::CharacterCallbackEventSubscription>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
	}
	else if (SubscriptionType == EventType::CursorPositionCallbackEvent)
	{
		std::unique_ptr<ErmineEventSystem::CursorPositionCallbackEventSubscription> Obj = std::make_unique<ErmineEventSystem::CursorPositionCallbackEventSubscription>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
	}
	else if (SubscriptionType == EventType::MouseButtonCallbackEvent)
	{
		std::unique_ptr<ErmineEventSystem::MouseButtonCallbackEventSubscription> Obj = std::make_unique<ErmineEventSystem::MouseButtonCallbackEventSubscription>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
	}
	else if (SubscriptionType == EventType::ScrollCallbackEvent)
	{
		std::unique_ptr<ErmineEventSystem::ScrollCallbackEventSubscription> Obj = std::make_unique < ErmineEventSystem::ScrollCallbackEventSubscription > (Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
	}
	else
	{
		LogBuffer("Error This Line Must Never Be Reached.. Got From Reciever::Bind Function");
	}
	
	
}
