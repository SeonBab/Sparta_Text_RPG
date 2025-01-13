#pragma once
#include "Actor.h"

class Character : public Actor
{
public:
    
    Character()
    {
        Name = "Player";
        
    }
    

protected:
    
    virtual void BeginPlay(shared_ptr<Actor> NewActor) override;
};


