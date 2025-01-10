#pragma once
#include <memory>
#include <vector>
#include <string>

#include "Framework/Managers/BattleManager.h"
#include "Framework/Managers/ShopManager.h"

using namespace std;

enum class EEndType
{
    Win,
    Lose,
    None,
};

class Entity
{
    
public:
    
    const string& GetName() const { return Name; }
    void SetName(const string& name) { Name = name; }
    
private:
    
    string Name;
    
};


class MainGame
{
    
public:

    void Init();

    void Tick();

    static MainGame& Get();

    void GenerateMonster();

    void SetGameEnded(bool InIsGameEnded){bIsGameEnded = InIsGameEnded;}
    
    bool IsGameEnded(){return bIsGameEnded;}
    
    void OnGameEnded();

    vector<unique_ptr<Entity>> Monsters;

    EEndType EndType = EEndType::None;
    
private:
    BattleManager m_BattleManager;
    ShopManager m_ShopManager;

    unsigned int MonsterNum = 4;

    bool bIsGameEnded = false;

    MainGame() = default;
};
