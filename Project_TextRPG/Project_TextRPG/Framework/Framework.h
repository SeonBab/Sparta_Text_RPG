#pragma once
#include <memory>
#include <vector>
#include <string>

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

    void GenerateMonsterDefs();

    void SetGameEnded(bool InIsGameEnded){bIsGameEnded = InIsGameEnded;}
    
    bool IsGameEnded(){return bIsGameEnded;}
    
    void OnGameEnded();

    vector<unique_ptr<Entity>> Monsters;

    EEndType EndType = EEndType::None;
    
    void DisplayChoices();

    void Select();
    
private:
    unsigned int MaxMonsterNum = 5;
    unsigned int MinMonsterNum = 2;

    bool bIsGameEnded = false;

    MainGame() = default;
};