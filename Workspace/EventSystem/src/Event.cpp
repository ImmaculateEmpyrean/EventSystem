#include "Event.h"

ErmineEventSystem::EventSubscription::EventSubscription()
	:
	CanIRecieveEventFlag(std::atomic<bool>(true)) //Not Recommended To Use This .. Intended For Legacy Purposes...
{}

ErmineEventSystem::EventSubscription::EventSubscription(std::atomic<bool>& CanIRecieveEventNowFlag)
	:
	CanIRecieveEventFlag(CanIRecieveEventNowFlag) //If Possible Use This Constructor It Surely Is Recommended
{}