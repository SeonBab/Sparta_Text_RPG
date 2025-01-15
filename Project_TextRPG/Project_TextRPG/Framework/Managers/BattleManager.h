#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Player/Player.h"
class Monster;

class BattleManager
{
public:
    static BattleManager& Get() { return Instance; }
private:

    static BattleManager Instance;

    friend class MainGame;

    const int RoomSize = 3;

    const int MaxPlayerLevel = 10;

    const int ItemUseProb = 30;

    const int ItemDropProb = 50; 
    
    const int RangeItemType = 1; // AttackBoost는 즉시 사용되도록

    bool Battle(Monster* Monster, Player* Player);

    int RandRange(int start, int end);


};