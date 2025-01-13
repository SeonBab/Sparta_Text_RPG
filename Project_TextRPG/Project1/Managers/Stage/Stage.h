#pragma once
#include <memory>
#include <vector>
#include <iostream>

#include "Actors/Actor.h"

struct FStat;

using namespace std;

enum class EStageType
{
	// StageStart,
	End
};


class Stage
{
protected:
	vector<shared_ptr<Actor>> Actors;

private:


public:
	virtual ~Stage() = default;
	

	virtual void Init() = 0;

	virtual void Tick(float DeltaTime);

	virtual void Render() = 0;

	template<typename T>
	shared_ptr<Actor> SpawnActor()
	{
		shared_ptr<Actor> NewActor = make_shared<T>();
		Actors.push_back(NewActor);
		NewActor->BeginPlay(NewActor);
		return NewActor;
	}

	// PlayerManger를 위한 함수.
	void SpawnActor(shared_ptr<Actor> NewActor)
	{
		Actors.push_back(NewActor);
		NewActor->BeginPlay(NewActor);
	}
	
	
	void DestroyActor(Actor* InActor)
	{
		for(auto& Actor : Actors)
		{
			if(Actor.get() == InActor)
			{
				swap(Actor, Actors.back());
				Actors.pop_back();
				return;
			}
		}
	}

	const vector<shared_ptr<Actor>>& GetActors()
	{
		return Actors;
	}
};

