#include "Stage.h"



void Stage::Tick(float DeltaTime)
{
	for(shared_ptr<Actor> Actor : Actors)
	{
		if(Actor->IsValid())
		{
			Actor->Tick(DeltaTime);
		}
	}
}