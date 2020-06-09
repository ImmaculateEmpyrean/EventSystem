#include "EventBroadcastStation.h"

ErmineEventSystem::EventBroadcastStation* ErmineEventSystem::EventBroadcastStation::EventBroadcastStationPointer = nullptr; //Note The Broadcast Station is not initialized
std::once_flag ErmineEventSystem::EventBroadcastStation::LazyInitializationFlag;
std::atomic<bool> ErmineEventSystem::EventBroadcastStation::StationDestructionOrdered = false;
std::thread* ErmineEventSystem::EventBroadcastStation::StationThreadObject;
std::mutex ErmineEventSystem::EventBroadcastStation::MainMutex;

void EventBroadcastStationMainRoutine()
{
	while (ErmineEventSystem::EventBroadcastStation::StationDestructionOrdered == false)
	{
		_sleep(100);
		auto Station = ErmineEventSystem::EventBroadcastStation::GetStation();
		Station->DispatchMessages();
	}
}


ErmineEventSystem::EventBroadcastStation::~EventBroadcastStation()
{}

ErmineEventSystem::EventBroadcastStation* ErmineEventSystem::EventBroadcastStation::GetStation()
{
	//std::lock_guard<std::mutex> GetStationLockGaurd(GetStationLock); //This Ensures Only One Thread Can Access The Retuen At a Given Time
	
	std::call_once(LazyInitializationFlag, []() {
		EventBroadcastStationPointer = DBG_NEW EventBroadcastStation(); //Create A New event Broadcast Station..
		StationThreadObject = new std::thread(EventBroadcastStationMainRoutine);
	});

	std::unique_lock<std::mutex> Loc(MainMutex);//,std::adopt_lock);
	return EventBroadcastStationPointer;
}

void ErmineEventSystem::EventBroadcastStation::DestroyStation()
{
	StationDestructionOrdered = true;
	StationThreadObject->join();

	delete StationThreadObject;
	delete EventBroadcastStationPointer;
}

void ErmineEventSystem::EventBroadcastStation::QueueBroadcast(std::unique_ptr<Event> BroadcastPackage)
{
	std::unique_lock<std::mutex> Loc(MainMutex);//, std::adopt_lock);//std::lock_guard<std::mutex> Loc(MainMutex,std::adopt_lock);
	
	ErmineEventSystem::EventType BroadcastType = BroadcastPackage->GetEventType();
	Event* EvePtr = BroadcastPackage.release();

	switch(BroadcastType)
	{
	case EventType::ConcreteEvent:ConcreteEventsQueue.push_back(*((ConcreteEvent*)(EvePtr)));
		break;
	case EventType::KeyCallbackEvent:KeyCallbackEventsQueue.push_back(*((KeyCallbackEvent*)(EvePtr)));
		break;
	case EventType::CharacterCallbackEvent:CharacterCallbackEventsQueue.push_back(*((CharacterCallbackEvent*)(EvePtr)));
		break;
	case EventType::CursorPositionCallbackEvent:CursorPositionCallbackEventsQueue.push_back(*((CursorPositionCallbackEvent*)(EvePtr)));
		break;
	case EventType::MouseButtonCallbackEvent:MouseButtonCallbackEventsQueue.push_back(*((MouseButtonCallbackEvent*)(EvePtr)));
		break;
	case EventType::ScrollCallbackEvent:ScrollCallbackEventsQueue.push_back(*((ScrollCallbackEvent*)(EvePtr)));
		break;
	default: LogBuffer("Unknown Event Type Recieved For QUeing Check Api Maybe... Dunno I should never trigger");
	}
	delete EvePtr;
}

void ErmineEventSystem::EventBroadcastStation::QueueSubscription(std::unique_ptr<EventSubscription> Subscription)
{
	std::unique_lock<std::mutex> Loc(MainMutex);//, std::adopt_lock);//std::lock_guard<std::mutex> Loc(MainMutex, std::adopt_lock);
	
	auto SubscriptionType = Subscription->GetEventSubscriptionType();
	EventSubscription* EvePtr = Subscription.release();

	switch (SubscriptionType)
	{
	case EventType::ConcreteEvent : ConcreteEventSubscriptions.push_back(*((ConcreteEventSubscription*)(EvePtr)));
		break;
	case EventType::KeyCallbackEvent : KeyCallbackEventsSubscriptions.push_back(*((KeyCallbackEventSubscription*)(EvePtr)));
		break;
	case EventType::CharacterCallbackEvent: CharacterCallbackEventSubscriptions.push_back(*((CharacterCallbackEventSubscription*)(EvePtr)));
		break;
	case EventType::CursorPositionCallbackEvent: CursorPositionCallbackEventSubscriptions.push_back(*((CursorPositionCallbackEventSubscription*)(EvePtr)));
		break;
	case EventType::MouseButtonCallbackEvent: MouseButtonCallbackEventSubscriptions.push_back(*((MouseButtonCallbackEventSubscription*)(EvePtr)));
		break;
	case EventType::ScrollCallbackEvent: ScrollCallbackEventSubscriptions.push_back(*((ScrollCallbackEventSubscription*)(EvePtr)));
		break;
	default: LogBuffer("Unknown Subscription Type Recieved For Queing Check Api Maybe... Dunno I should never trigger");
	}

	delete EvePtr;
}



void ErmineEventSystem::EventBroadcastStation::DispatchMessages()
{
	std::unique_lock<std::mutex> Loc(MainMutex);//std::lock_guard<std::mutex> Loc(MainMutex, std::adopt_lock);
	
	//Just Iterate Over All Buffers And Try To Dispatch The Messages...
	DispatchConcreteMessages();
	DispatchKeyCallbackMessages();
	DispatchCharacterCallbackMessages();
	DispatchCursorPositionCallbackMessages();
	DispatchMouseButtonCallbackMessages();
	DispatchScrollCallbackMessages();
}

void ErmineEventSystem::EventBroadcastStation::DispatchConcreteMessages()
{
	for (int i = 0; i < ConcreteEventsQueue.size(); i++)
	{
		for (auto j : ConcreteEventSubscriptions)
		{
			if (j.CanIRecieveEventFlag == true)
			{
				j.CallableObject(&ConcreteEventsQueue[i]);
			}
			//If The Event Is Already handled No Point In Handling it Further Right..
			if (ConcreteEventsQueue[i].IsEventHandled() == true)
			{
				break;
			}
		}
		ConcreteEventsQueue.erase(ConcreteEventsQueue.begin() + i);
	}
}

void ErmineEventSystem::EventBroadcastStation::DispatchKeyCallbackMessages()
{
	for (int i = 0; i < KeyCallbackEventsQueue.size(); i++)
	{
		for (auto j : KeyCallbackEventsSubscriptions)
		{
			if (j.CanIRecieveEventFlag == true)
			{
				j.CallableObject(&KeyCallbackEventsQueue[i]);
			}
			//If The Event Is Already handled No Point In Handling it Further Right..
			if (KeyCallbackEventsQueue[i].IsEventHandled() == true)
			{
				break;
			}
		}
		KeyCallbackEventsQueue.erase(KeyCallbackEventsQueue.begin() + i);
	}
}

void ErmineEventSystem::EventBroadcastStation::DispatchCharacterCallbackMessages()
{
	for (int i = 0; i < CharacterCallbackEventsQueue.size(); i++)
	{
		for (auto j : CharacterCallbackEventSubscriptions)
		{
			if (j.CanIRecieveEventFlag == true)
			{
				j.CallableObject(&CharacterCallbackEventsQueue[i]);
			}
			//If The Event Is Already handled No Point In Handling it Further Right..
			if (CharacterCallbackEventsQueue[i].IsEventHandled() == true)
			{
				break;
			}
		}
		CharacterCallbackEventsQueue.erase(CharacterCallbackEventsQueue.begin() + i);
	}
}

void ErmineEventSystem::EventBroadcastStation::DispatchCursorPositionCallbackMessages()
{
	for (int i = 0; i < CursorPositionCallbackEventsQueue.size(); i++)
	{
		for (auto j : CursorPositionCallbackEventSubscriptions)
		{
			if (j.CanIRecieveEventFlag == true)
			{
				j.CallableObject(&CursorPositionCallbackEventsQueue[i]);
			}
			//If The Event Is Already handled No Point In Handling it Further Right..
			if (CursorPositionCallbackEventsQueue[i].IsEventHandled() == true)
			{
				break;
			}
		}
		CursorPositionCallbackEventsQueue.erase(CursorPositionCallbackEventsQueue.begin() + i);
	}
}

void ErmineEventSystem::EventBroadcastStation::DispatchMouseButtonCallbackMessages()
{
	for (int i = 0; i < MouseButtonCallbackEventsQueue.size(); i++)
	{
		for (auto j : MouseButtonCallbackEventSubscriptions)
		{
			if (j.CanIRecieveEventFlag == true)
			{
				j.CallableObject(&MouseButtonCallbackEventsQueue[i]);
			}
			//If The Event Is Already handled No Point In Handling it Further Right..
			if (MouseButtonCallbackEventsQueue[i].IsEventHandled() == true)
			{
				break;
			}
		}
		MouseButtonCallbackEventsQueue.erase(MouseButtonCallbackEventsQueue.begin() + i);
	}
}

void ErmineEventSystem::EventBroadcastStation::DispatchScrollCallbackMessages()
{
	for (int i = 0; i < ScrollCallbackEventsQueue.size(); i++)
	{
		for (auto j : ScrollCallbackEventSubscriptions)
		{
			if (j.CanIRecieveEventFlag == true)
			{
				j.CallableObject(&ScrollCallbackEventsQueue[i]);
			}
			//If The Event Is Already handled No Point In Handling it Further Right..
			if (ScrollCallbackEventsQueue[i].IsEventHandled() == true)
			{
				break;
			}
		}
		ScrollCallbackEventsQueue.erase(ScrollCallbackEventsQueue.begin() + i);
	}
}
