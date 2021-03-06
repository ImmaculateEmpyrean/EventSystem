#pragma once

#include <iostream>
#include<memory>
#include<vector>

#include "EventBroadcastStation.h"

#include "EnumEventType.h"
#include "Event.h"
#include "EventTypes/TestConcreteEvent.h"

namespace ErmineEventSystem
{
	class BroadcastComponent
	{
	public:
		//There Is Absolutely No Reason To Create An Object Of A BroadcastComponent Just Broadcast What Is Needed Using The Api..
		BroadcastComponent() = delete;
		
		static void BroadcastEvent(std::unique_ptr<Event> EventToBeBroadcasted);
	};
}
