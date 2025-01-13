#include "Character.h"

#include "Components/Behavior/BehaviorComponent.h"
#include "Game.h"
#include "Components/Timer/TimerComponent.h"


class TimerComponent;

void Character::BeginPlay(shared_ptr<Actor> NewActor)
{
    Actor::BeginPlay(NewActor);

    GameMain::GetManager<PlayerManager>()->InitializeCharacter();
}

