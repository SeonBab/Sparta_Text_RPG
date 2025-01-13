#pragma once
#include "Components/ActorComponent.h"
#include "Behavior.h"

class BehaviorComponent : public ActorComponent
{

    
public:
    BehaviorComponent(shared_ptr<Actor> InOwner)
        : ActorComponent(InOwner)
    {
        SetComponentType(EComponentType::Behavior);
    }

    void Beginplay(shared_ptr<Actor> NewActor) override;

    void Tick(float DeltaTime) override;

    void Behave();

    template<typename T>
    void AddBehavior()
    {
        BehaviorContainer.AddBehavior(make_shared<T>());
    }
    
    void RemoveBehavior(shared_ptr<Behavior> InBehavior)
    {
        BehaviorContainer.RemoveBehavior(InBehavior);
    }

    void AssignContainer(const FBehaviorContainer& InContainer)
    {
        BehaviorContainer = InContainer;
    }

    Getter(FBehaviorContainer, BehaviorContainer, BehaviorContainer);

private:
    
    FBehaviorContainer BehaviorContainer;
};
