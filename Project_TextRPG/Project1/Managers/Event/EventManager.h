#pragma once
#include <memory>
#include <queue>

#include "define.h"

using namespace std;

enum class EEventType
{
	ChangeStage,
	DestroyActor,
	End
};

struct FEvent
{
	FEvent(EEventType InEventType, shared_ptr<void> InEventData1 = nullptr, shared_ptr<void> InEventData2 = nullptr)
		: EventType(InEventType)
		, EventData1(InEventData1)
		, EventData2(InEventData2)
	{

	}

	EEventType EventType;
	
	shared_ptr<void> EventData1;
	shared_ptr<void> EventData2;
};

class EventManager
{
GameMainSingleton(EventManager)

private:

	bool IsLevelChanged;

	queue<FEvent> EventQueue;

	void ManageEvent();

public:

	void AddEvent(const FEvent& Event)
	{
		EventQueue.push(Event);
	}
		

	void Init();

	void Tick();

};

