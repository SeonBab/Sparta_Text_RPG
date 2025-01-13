#include "TimerComponent.h"

void TimerComponent::Tick(float DeltaTime)
{
    ActorComponent::Tick(DeltaTime);

    TimerMgr.Progress(DeltaTime);
}

void TimerComponent::Beginplay(shared_ptr<Actor> NewActor)
{
    ActorComponent::Beginplay(NewActor);
}
