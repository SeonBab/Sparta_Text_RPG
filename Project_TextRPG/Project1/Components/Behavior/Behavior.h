#pragma once
#include <memory>
#include <vector>

#include "Actors/Actor.h"
#include "define.h"

using namespace std;

class Actor;

struct FBehaviorContext
{
    shared_ptr<Actor> Self;
    vector<shared_ptr<Actor>> Targets;
};

class Behavior
{
    
public:
    virtual ~Behavior() = default;

    virtual void Behave(FBehaviorContext& BehaveContext) = 0;
    

    GetterSetter(int, Priority, Priority)

protected:

    // 각 Behavior에 대한 고정된 Priority를 위해서
    // 1. 잘 정한다
    // 2. Enum으로 관리한다.
    int Priority = -1;
};

struct FBehaviorContainer
{
    void AddBehavior(shared_ptr<Behavior> InBehavior);
    void RemoveBehavior(shared_ptr<Behavior> InBehavior);
    void Behave(FBehaviorContext& Context);
    
 private:
    vector<shared_ptr<Behavior>> Behaviors;

    void Sort();
};


class Behavior_Powerup : public Behavior
{
public:
    Behavior_Powerup()
    {
       Priority = 1; 
    }

    void Behave(FBehaviorContext& BehaveContext) override;
};


class Behavior_Attack : public Behavior
{
public:
    Behavior_Attack()
    {
        Priority = 2;
    }

    int AttackCount = 2;

    void Behave(FBehaviorContext& BehaveContext) override;

private:
    void Attack(Actor* Self, Actor* Target);
};


class Behavior_UseItem : public Behavior
{
    Behavior_UseItem()
    {
        Priority = 3;
    }

    void Behave(FBehaviorContext& BehaveContext) override
    {
        
    }
};
