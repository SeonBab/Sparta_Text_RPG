#include "BehaviorComponent.h"

#include "Game.h"

void BehaviorComponent::Beginplay(shared_ptr<Actor> NewActor)
{
    ActorComponent::Beginplay(NewActor);
}

void BehaviorComponent::Tick(float DeltaTime)
{
    ActorComponent::Tick( DeltaTime);
}

void BehaviorComponent::Behave()
{
    auto& Actors = GameMain::GetManager<StageManager>()->GetCurrentStage()->GetActors();
    FBehaviorContext Context;
    for(auto& CurActor : Actors)
    {
        if(!CurActor->IsValid())
        {
            continue;
        }
        
        if(!Owner.expired() && CurActor->GetCurTeamType() != Owner.lock()->GetCurTeamType())
        {
            Context.Targets.push_back(CurActor);    
        }
        else if(CurActor.get() == Owner.lock().get())
        {
            Context.Self = CurActor;
        }
    }
    BehaviorContainer.Behave(Context);
}
