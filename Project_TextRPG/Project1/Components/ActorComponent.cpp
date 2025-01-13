#include "ActorComponent.h"

#include "Actors/Actor.h"
#include "Components/Behavior/BehaviorComponent.h"
#include "Components/Timer/TimerComponent.h"

void AddComponent(shared_ptr<Actor> InActor, EComponentType InType)
{
    for(auto Component : InActor->Components)
    {
        if(Component->GetComponentType() == InType)
        {
            return;
        }
    }
    
    switch (InType)
    {
    case EComponentType::Timer:
        {
            InActor->Components.push_back(make_shared<TimerComponent>(InActor));
            break;
        }
    case EComponentType::Behavior:
        {
            InActor->Components.push_back(make_shared<BehaviorComponent>(InActor));
            break;
        }
    }
}

void RemoveComponent(shared_ptr<Actor> InActor, EComponentType InType)
{
    for(auto& Component : InActor->Components)
    {
        if(Component->GetComponentType() == InType)
        {
            swap(Component, InActor->Components.back());
            InActor->Components.pop_back();
            return;
        }
    }
}
