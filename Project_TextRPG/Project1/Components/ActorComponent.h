#pragma once
#include <memory>

class Actor;
using namespace std;

#include "define.h"

enum class EComponentType
{
    Timer,
    Behavior,
    
};

void AddComponent(shared_ptr<Actor> InActor, EComponentType InType);
void RemoveComponent(shared_ptr<Actor> InActor, EComponentType InType);

class ActorComponent
{
public:
    ActorComponent(shared_ptr<Actor> InOwner)
        : Owner(InOwner)
    {
    }
    
    virtual ~ActorComponent() = default;
    virtual void Tick(float DeltaTime){}
    Getter(EComponentType, ComponentType, ComponentType)

protected:

    friend class Actor;

    weak_ptr<Actor> Owner;
    virtual void Beginplay(shared_ptr<Actor> NewActor){}
    Setter(EComponentType, ComponentType, ComponentType)

    EComponentType ComponentType;
    
};


