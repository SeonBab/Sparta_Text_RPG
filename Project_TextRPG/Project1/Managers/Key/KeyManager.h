#pragma once
#include "memory"
#include "define.h"

using namespace std;

class KeyManager
{
    GameMainSingleton(KeyManager)

public:

    bool IsKeyPressed(char Key);
    
};
