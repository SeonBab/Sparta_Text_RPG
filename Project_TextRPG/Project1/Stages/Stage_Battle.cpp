#include "Stage_Battle.h"

#include "Game.h"
#include "Actors/Monster.h"
#include "Actors/Character.h"


unsigned int Timer::GID = 0;


void Stage_Battle::Init()
{
    shared_ptr<Actor> MainCharacter = GameMain::GetManager<PlayerManager>()->GetMainCharacter();
    GameMain::GetManager<StageManager>()->GetCurrentStage()->SpawnActor(MainCharacter);
    
    unsigned int MonsterNum = max(MinMonsterNum, rand() % (MaxMonsterNum + 1)); 

    for(int i = 0; i < MonsterNum; ++i)
    {
        SpawnActor<Monster>();
    }
}

void Stage_Battle::Tick(float DeltaTime)
{
    Stage::Tick(DeltaTime);

    auto& Actors = GameMain::GetManager<StageManager>()->GetCurrentStage()->GetActors();

    bool bHasPlayerTeam = false;
    bool bHasMonsterTeam = false;
    for(auto& CurActor : Actors)
    {
        if(!CurActor->IsValid())
        {
            continue;
        }
        
        if(CurActor->GetCurTeamType() == ETeamType::Team_Monster )
        {
            bHasMonsterTeam = true;
        }
        else if(CurActor->GetCurTeamType() == ETeamType::Team_Player)
        {
            bHasPlayerTeam = true;
        }
    }

    if(!bHasMonsterTeam)
    {
        GameMain::GetInstance()->EndGame();
        GameMain::GetManager<WriteManager>()->AddLine(ELayoutType::LOG, FLayoutString(string("너는 이겼따."), EWriteOption_MoveDown));
        
    }

    if(!bHasPlayerTeam)
    {
        GameMain::GetInstance()->EndGame();
        GameMain::GetManager<WriteManager>()->AddLine(ELayoutType::LOG, FLayoutString(string("너는 졌따."), EWriteOption_MoveDown));
    }
}

void Stage_Battle::Render()
{
    
}
