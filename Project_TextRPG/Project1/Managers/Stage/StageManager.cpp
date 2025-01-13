#include "StageManager.h"


#include "Stage.h"
#include "Stages/Stage_Battle.h"

shared_ptr<StageManager> StageManager::instance = nullptr;


void StageManager::Init()
{
	
	CurrentStage = make_shared<Stage_Battle>();

	CurrentStage->Init();


}

void StageManager::Tick(float DeltaTime)
{
	CurrentStage->Tick(DeltaTime);
}


void StageManager::ChangeCurrentStage(EStageType NextStageType)
{
	switch (NextStageType)
	{
	// case EStageType::StageStart:
	// {
	// 	CurrentStage = make_shared<Stage_Start>();
	// 	break;
	// }
	}
	
	CurrentStage->Init();
}
