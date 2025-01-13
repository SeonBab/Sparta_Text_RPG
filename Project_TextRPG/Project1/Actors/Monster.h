#pragma once
#include "Actor.h"

class Monster : public Actor
{
public:
    Monster()
    {
        Name  = "Monster";
    }

protected:
    virtual void BeginPlay(shared_ptr<Actor> NewActor) override;
    
};
