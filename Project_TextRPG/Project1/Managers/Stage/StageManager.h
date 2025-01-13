#pragma once

#include <memory>
#include "Stage.h"

class Actor;
using namespace std;


class Stage;

enum class EStageType;



class StageManager
{
private:
	GameMainSingleton(StageManager)


private:

	shared_ptr<Stage> CurrentStage = nullptr;

public:

	shared_ptr<Stage> GetCurrentStage(){ return CurrentStage; }

	void Init();

	void Tick(float DeltaTime);
	
	void ChangeCurrentStage(EStageType NextStageType);

	template<typename T>
	shared_ptr<Actor> CreateActor()
	{
		return CurrentStage->SpawnActor<T>(); 
	}

	void DestroyActor(Actor* InActor)
	{
		CurrentStage->DestroyActor(InActor);
	}
	
};

