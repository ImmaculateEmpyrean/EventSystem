#include "BroadcastComponent.h"

void ErmineEventSystem::BroadcastComponent::BroadcastEvent(std::unique_ptr<Event> EventToBeBroadcasted)
{
	ErmineEventSystem::EventBroadcastStation::GetStation()->QueueBroadcast(std::move(EventToBeBroadcasted));
}
