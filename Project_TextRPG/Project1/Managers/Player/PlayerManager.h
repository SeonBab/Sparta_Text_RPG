#pragma once
#include <memory>

#include "Actors/Actor.h"
#include "define.h"

class Character;

using namespace std;



class PlayerManager
{
    GameMainSingleton(PlayerManager)

private:

    void Init();
    
    shared_ptr<Actor> MainCharacter;

public:

    shared_ptr<Actor> GetMainCharacter(){return MainCharacter;}
    
    void InitializeCharacter();
    

    // OnLevelChanged
};
