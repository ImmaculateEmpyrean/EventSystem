#pragma once
#include<iostream>
#include<vector>
#include<string>

#include "Symbols.h"
#include "Components/BroadcastComponent.h"
#include "Components/RecieverComponent.h"

class E1A
{
public:
	//Constructor
	E1A()
	{
		std::unique_ptr<ErmineEventSystem::ConcreteEvent> EventObj = ErmineEventSystem::ConcreteEvent::GenerateEvent("This Message Is Being BroadCasted In The System");
		ErmineEventSystem::BroadcastComponent::BroadcastEvent(std::move(EventObj));
	}

};

class E1B
{
public:
	E1B()
	{
		ErmineEventSystem::RecieverComponent::Bind(GenCallableFromMethod(&E1B::TestFunction), Flag, ErmineEventSystem::EventType::ConcreteEvent);
	}

private:
	std::atomic<bool> Flag = true;

	void TestFunction(ErmineEventSystem::Event* EveObj)
	{
		auto ptr = (ErmineEventSystem::ConcreteEvent*)EveObj;
		LogBuffer(ptr->GetMessageBuffer().c_str());
	}
};

void Example1Main()
{
	E1B RecieverObject;
	E1A SenderObject;

	std::cin.get();
}