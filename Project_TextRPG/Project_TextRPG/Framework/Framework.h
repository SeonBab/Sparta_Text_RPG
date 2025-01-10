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
    const int GetHP() const { return HP; }
    void SetHP(const int hp) { HP = hp; }
    const int GetMaxHP() const { return MaxHP; }
    void SetMaxHP(const int maxHP) { MaxHP = maxHP; }
    const int GetDamage() const { return Damage; }
    void SetDamage(const int damage) { Damage = damage; }
    Entity::Entity(string name, int maxHP, int damage)
    {
        Name = name;
        MaxHP = maxHP;
        HP = MaxHP; // 태어날 땐 최대 체력이 현재 체력과 같음
        Damage = damage;
    }
    
protected:
    
    string Name;
    int MaxHP;
    int HP;
    int Damage;
    
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
    
    void ClearBuffer();
    
    void AddStringToBuffer(const string& InString);
    
    void DisplayBuffer(bool bClear = false);

    void DisplayChoices();

    void Select();
    
private:

    // Buffer System 쓰려면 여기다 추가 삭제만
    vector<string> Buffer;

    unsigned int MaxMonsterNum = 5;
    unsigned int MinMonsterNum = 2;

    bool bIsGameEnded = false;

    MainGame() = default;
};