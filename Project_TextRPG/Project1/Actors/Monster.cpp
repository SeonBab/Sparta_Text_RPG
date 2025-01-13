#include "Monster.h"

#include "Components/Behavior/BehaviorComponent.h"
#include "Components/Timer/TimerComponent.h"

FStat MonsterDefaultStat = FStat
{
    20,
    20,
    1,
    4,
    1.4f,
    ETeamType::Team_Monster,
};

void Monster::BeginPlay(shared_ptr<Actor> NewActor)
{
    Actor::BeginPlay(NewActor);

    SetDefaultStat(MonsterDefaultStat);
    SetCurStat(MonsterDefaultStat);
    
    AddComponenet(EComponentType::Behavior, NewActor);
    AddComponenet(EComponentType::Timer, NewActor);
    
    auto BehaviorComp = FindComponent<BehaviorComponent>(EComponentType::Behavior);
    BehaviorComp->AddBehavior<Behavior_Attack>();
    
    auto TimerComp = FindComponent<TimerComponent>(EComponentType::Timer);
    TimerComp->SetTimer(bind(&BehaviorComponent::Behave, BehaviorComp), GetCurBehaveSpeed(), true);
}