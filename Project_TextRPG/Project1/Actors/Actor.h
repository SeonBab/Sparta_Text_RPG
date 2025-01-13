#pragma once

#include <string>

#include "Components/ActorComponent.h"
#include "Components/Behavior/Behavior.h"
#include "define.h"
#include "Components/Timer/Timer.h"

class ActorComponent;
using namespace std;

enum class ETeamType
{
    Team_Player,
    Team_Monster,
};


struct FStat
{
    int MaxHP;
    int HP;
    int Def;
    int AttackPoint;
    float BehaveSpeed;
    ETeamType TeamType = ETeamType::Team_Monster;
};


#define StatGetterSetter(FuncPrefix, StatName )\
GetterSetter(FStat, ##FuncPrefix##Stat, ##StatName)\
GetterSetter(int, ##FuncPrefix##MaxHP, ##StatName##.MaxHP)\
GetterSetter(int, ##FuncPrefix##HP, ##StatName##.HP)\
GetterSetter(int, ##FuncPrefix##Def, ##StatName##.Def)\
GetterSetter(int, ##FuncPrefix##AttackPoint, ##StatName##.AttackPoint)\
GetterSetter(float, ##FuncPrefix##BehaveSpeed, ##StatName##.BehaveSpeed)\
GetterSetter(ETeamType, ##FuncPrefix##TeamType, ##StatName##.TeamType)

class Actor
{
public:
    
    StatGetterSetter(Cur, CurStat)
    StatGetterSetter(Default, DefaultStat)

    GetterSetter(string, Name, Name)

    virtual void Tick(float DeltaTime);

    virtual void Destory();

    bool IsValid()
    {
        return bIsValid;
    }

    void AddComponenet(EComponentType InComponentType, shared_ptr<Actor> InOwner);
    void RemoveComponent(EComponentType InComponentType, shared_ptr<Actor> InOwner);
    ActorComponent* FindComponent(EComponentType InComponentType);

    template<typename T>
    T* FindComponent(EComponentType InComponentType)
    {
        return dynamic_cast<T*>(FindComponent(InComponentType));
    }

    friend void AddComponent(shared_ptr<Actor> InActor, EComponentType InType);
    friend void RemoveComponent(shared_ptr<Actor> InActor, EComponentType InType);
    
    virtual ~Actor() = default;

protected:

    friend class Stage;

    virtual void BeginPlay(shared_ptr<Actor> NewActor);

    string Name;

private:

    vector<shared_ptr<ActorComponent>> Components;
   
    FStat CurStat;
    FStat DefaultStat;

    bool bIsValid = true;
    
};
