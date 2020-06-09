#include "BroadcastComponent.h"

ErmineEventSystem::EventBroadcastStation* ErmineEventSystem::BroadcastComponent::ConnectionToStation = nullptr;
std::once_flag ErmineEventSystem::BroadcastComponent::BroadcastComponentInitializationFlag;

ErmineEventSystem::BroadcastComponent::BroadcastComponent()
{
	ConnectionToStation = EventBroadcastStation::GetStation();
}

unsigned int ErmineEventSystem::BroadcastComponent::AddEventForBroadcasting(std::unique_ptr<Event> EventToQueueForSending)
{
	EventsThatCanBeBroadcasted.emplace_back(std::move(EventToQueueForSending));
	return EventsThatCanBeBroadcasted.size() - 1;
}

void ErmineEventSystem::BroadcastComponent::BroadcastEventFromQueue(unsigned int& RecievedToken)
{
	if (RecievedToken < 0)
	{
		std::cout << "Invalid Token Recieved By BroadcastComponent::BroadcastEventFromQueue returning" << std::endl;
		return;
	}

	BroadcastEvent(std::move(EventsThatCanBeBroadcasted[RecievedToken]));
	EventsThatCanBeBroadcasted.erase(EventsThatCanBeBroadcasted.begin() + RecievedToken);
	RecievedToken = -1;
}

void ErmineEventSystem::BroadcastComponent::BroadcastEvent(std::unique_ptr<Event> EventToBeBroadcasted)
{
	std::call_once(BroadcastComponentInitializationFlag, []() {
		ConnectionToStation = ErmineEventSystem::EventBroadcastStation::GetStation();
	});
	
	ConnectionToStation->QueueBroadcast(std::move(EventToBeBroadcasted));
}
