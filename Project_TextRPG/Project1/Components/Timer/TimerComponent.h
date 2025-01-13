#pragma once
#include "Components/ActorComponent.h"
#include "Timer.h"

class TimerComponent : public ActorComponent
{
public:
    
    TimerComponent(shared_ptr<Actor> InOwner)
        : ActorComponent(InOwner)
    {
        SetComponentType(EComponentType::Timer);    
    }
    
public:
    
    void Tick(float DeltaTime) override;
    
    void SetTimer(std::function<void()> InOnTriggered, float InTriggerTime, bool InbRepeat)
    {
        TimerMgr.AddTimer( InOnTriggered,  InTriggerTime,  InbRepeat);
    };

protected:
    
    void Beginplay(shared_ptr<Actor> NewActor) override;

private:
    
    TimerManager TimerMgr;
};
