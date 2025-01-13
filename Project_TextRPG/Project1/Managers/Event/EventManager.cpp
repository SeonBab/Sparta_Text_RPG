#include "EventManager.h"

#include "Game.h"
#include "Managers/Stage/Stage.h"

shared_ptr<EventManager> EventManager::instance = nullptr;

void EventManager::ManageEvent()
{
	while (!EventQueue.empty()) 
	{
		const FEvent& CurrentEvent = EventQueue.front();

		switch (CurrentEvent.EventType)
		{
		case EEventType::ChangeStage:
			{
				IsLevelChanged = true;
				EStageType NextStageType = *static_cast<EStageType*> (CurrentEvent.EventData1.get());
				GameMain::GetManager<StageManager>()->ChangeCurrentStage(NextStageType);
				break;
			}

		case EEventType::DestroyActor :
			{
				if(!IsLevelChanged)
				{
					Actor* TargetActor = *static_cast<Actor**> (CurrentEvent.EventData1.get());
					GameMain::GetManager<StageManager>()->DestroyActor(TargetActor);
				}
				break;
			}
		}

		EventQueue.pop();
	}

	IsLevelChanged = false;
}

void EventManager::Init()
{

}

void EventManager::Tick()
{

	ManageEvent();

}
