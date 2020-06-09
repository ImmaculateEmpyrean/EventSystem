#include "RecieverComponent.h"

ErmineEventSystem::RecieverComponent::RecieverComponent(std::function<void(Event*)> Callable, std::atomic<bool>& SwitchTOControlIfAnEventCanBeExecuted, EventType SubscriptionType)
	:
	Callable(Callable),
	Switch(SwitchTOControlIfAnEventCanBeExecuted),
	RefToEventType(SubscriptionType)
{
	auto station = ErmineEventSystem::EventBroadcastStation::GetStation(); //Gets a Line To The Station
	switch (SubscriptionType)
	{
	case EventType::ConcreteEvent: std::unique_ptr<ErmineEventSystem::ConcreteEventSubscription> Obj = std::make_unique<ErmineEventSystem::ConcreteEventSubscription>(Callable,Switch);
								   station->QueueSubscription(std::move(Obj));
								   break;
	}
}

void ErmineEventSystem::RecieverComponent::Bind(std::function<void(Event*)> Callable, std::atomic<bool>& SwitchTOControlIfAnEventCanBeExecuted, EventType SubscriptionType)
{
	auto station = ErmineEventSystem::EventBroadcastStation::GetStation(); //Gets a Line To The Station
		
	/*switch(SubscriptionType)
	{
	case EventType::ConcreteEvent: Obj = std::dynamic_pointer_cast<Ermine::EventSubscription*>(std::make_unique<Ermine::ConcreteEventSubscription>(Callable, SwitchTOControlIfAnEventCanBeExecuted));
		station->QueueSubscription(std::move(Obj));
		break;
	case EventType::KeyCallbackEvent: Obj = std::make_unique<Ermine::KeyCallbackEventSubscription>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
		break;
	case EventType::CharacterCallbackEvent: std::unique_ptr<Ermine::CharacterCallbackEventSubscription> Obj = std::make_unique<Ermine::CharacterCallbackEventSubscription>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
		break;
	case EventType::CursorPositionCallbackEvent: std::unique_ptr<Ermine::CursorPositionCallbackEvent> Obj = std::make_unique<Ermine::CursorPositionCallbackEvent>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
		break;
	case EventType::MouseButtonCallbackEvent: std::unique_ptr<Ermine::MouseButtonCallbackEvent> Obj = std::make_unique<Ermine::MouseButtonCallbackEvent>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
		break;
	case EventType::ScrollCallbackEvent: std::unique_ptr<Ermine::ScrollCallbackEvent> Obj = std::make_unique<Ermine::ScrollCallbackEvent>(Callable, SwitchTOControlIfAnEventCanBeExecuted);
		station->QueueSubscription(std::move(Obj));
		break;
	default: STDOUTDefaultLog_Error("Error This Line Must Never Be Reached.. Got From Reciever::Bind Function");
	}*/

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
