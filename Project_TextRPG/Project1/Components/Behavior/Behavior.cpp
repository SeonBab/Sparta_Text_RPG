#include "Behavior.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "Game.h"
#include "Actors/Actor.h"

void FBehaviorContainer::AddBehavior(shared_ptr<Behavior> InBehavior)
{
    Behaviors.push_back(InBehavior);
    Sort();
}

void FBehaviorContainer::RemoveBehavior(shared_ptr<Behavior> InBehavior)
{
    for(auto& CurBehavior : Behaviors)
    {
        if(CurBehavior == InBehavior)
        {
            swap(CurBehavior, Behaviors.back());
            Behaviors.pop_back();
            Sort();
        }
    }
}

void FBehaviorContainer::Behave(FBehaviorContext& Context)
{
    for(auto& Behavior : Behaviors)
    {
        Behavior->Behave(Context);
    }
}

void FBehaviorContainer::Sort()
{
    sort(Behaviors.begin(), Behaviors.end(), [this](const shared_ptr<Behavior>& A, const shared_ptr<Behavior>& B)
        {
            return A->GetPriority() < B->GetPriority();
        });
}

void Behavior_Powerup::Behave(FBehaviorContext& BehaveContext)
{
    BehaveContext.Self->SetCurAttackPoint(BehaveContext.Self->GetCurAttackPoint() + 1);
}

void Behavior_Attack::Behave(FBehaviorContext& BehaveContext)
{
    int Loc_AttackCount = AttackCount;
    while(Loc_AttackCount && !BehaveContext.Targets.empty())
    {
        int TargetIdx = rand() % BehaveContext.Targets.size();
        shared_ptr<Actor> Target = BehaveContext.Targets[TargetIdx];
        
        if(Target->IsValid())
        {
            Attack(BehaveContext.Self.get(), Target.get());
            --Loc_AttackCount;
        }
        else
        {
            // Swap
            BehaveContext.Targets.erase(BehaveContext.Targets.begin() + TargetIdx);
        }
    }
}

void Behavior_Attack::Attack(Actor* Self, Actor* Target)
{
    Target->SetCurHP(Target->GetCurHP() - max(1, Self->GetCurAttackPoint() - Target->GetCurDef()));
    ostringstream oss;
    oss << Self->GetName() << " Attack : " << Target->GetName() <<" ->  Damage(" << max(1, Self->GetCurAttackPoint() - Target->GetCurDef()) << ")\n";
    
    GameMain::GetManager<WriteManager>()->AddLine(ELayoutType::LOG, FLayoutString(oss.str(), EWriteOption_MoveDown));

    
    if(Target->GetCurHP() <= 0)
    {
        // Gold Exp
        Target->SetCurHP(0);
        oss.clear();
        oss << Target->GetName() << " : Dead \n";
        GameMain::GetManager<WriteManager>()->AddLine(ELayoutType::LOG, FLayoutString(oss.str(), EWriteOption_MoveDown));
        Target->Destory();
    }
}
