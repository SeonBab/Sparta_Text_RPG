#include "Actor.h"

#include "Components/ActorComponent.h"
#include "Game.h"


void Actor::Tick(float DeltaTime)
{
    for(auto Component : Components)
    {
        Component->Tick(DeltaTime);
    }
}

void Actor::Destory()
{
    bIsValid = false;
    FEvent Event({EEventType::DestroyActor, shared_ptr<void>(new uintptr_t(reinterpret_cast<uintptr_t>(this)), [](void* ptr)
    {
        delete static_cast<uintptr_t*>(ptr);
    })});
    GameMain::GetManager<EventManager>()->AddEvent(Event);
}

void Actor::BeginPlay(shared_ptr<Actor> NewActor)
{
    for(auto Component : Components)
    {
        Component->Beginplay(NewActor);
    }
}

void Actor::AddComponenet(EComponentType InComponentType, shared_ptr<Actor> InOwner)
{
   ::AddComponent(InOwner, InComponentType);
}

void Actor::RemoveComponent(EComponentType InComponentType, shared_ptr<Actor> InOwner)
{
    ::RemoveComponent(InOwner, InComponentType);
}

ActorComponent* Actor::FindComponent(EComponentType InComponentType)
{
    for(auto Component : Components)
    {
        if(Component->GetComponentType() == InComponentType)
        {
            return Component.get();
        }
    }
    
    return nullptr;
}

