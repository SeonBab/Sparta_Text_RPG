#include "PlayerManager.h"

#include "Components/Behavior/BehaviorComponent.h"
#include "Actors/Character.h"
#include "Game.h"
#include "Components/Timer/TimerComponent.h"

shared_ptr<PlayerManager> PlayerManager::instance = nullptr;

FStat MainCharacterDefaultStat =
{
    100,
    100,
    1,
    4,
    2.f,
    ETeamType::Team_Player
};

void PlayerManager::Init()
{
    MainCharacter = make_shared<Character>();
    MainCharacter->SetDefaultStat(MainCharacterDefaultStat);
    MainCharacter->SetCurStat(MainCharacterDefaultStat);
    MainCharacter->AddComponenet(EComponentType::Behavior, MainCharacter);
    MainCharacter->AddComponenet(EComponentType::Timer, MainCharacter);
    auto BehaviorComp = MainCharacter->FindComponent<BehaviorComponent>(EComponentType::Behavior);
    
    BehaviorComp->AddBehavior<Behavior_Attack>();
    BehaviorComp->AddBehavior<Behavior_Powerup>();

    auto TimerComp = MainCharacter->FindComponent<TimerComponent>(EComponentType::Timer);

    TimerComp->SetTimer(bind(&BehaviorComponent::Behave, BehaviorComp), MainCharacter->GetCurBehaveSpeed(), true);
}

void PlayerManager::InitializeCharacter()
{
    MainCharacter->SetCurStat(MainCharacter->GetDefaultStat());
}

