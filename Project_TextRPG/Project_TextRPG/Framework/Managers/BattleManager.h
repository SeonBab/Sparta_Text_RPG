#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Character/Player.h"
class Monster;
class Item;
class Entity;

class BattleManager
{
public:
    static BattleManager& Get() { return Instance; }
private:

    static BattleManager Instance;
    friend class MainGame;

    const int RoomSize = 3;
    const int MaxPlayerLevel = 10;
    unsigned int MonsterSuffleIndex[4];

    bool Battle(Monster* Monster, Player* Character);

    int RandRange(int start, int end);

    //void UseItem(vector<Item*>& Inventory);

};