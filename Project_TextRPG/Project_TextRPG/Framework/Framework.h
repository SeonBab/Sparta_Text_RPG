﻿#pragma once
#include <memory>
#include <vector>
#include <string>

using namespace std;
class Monster;
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

    void SetName(const string& Name) { this->Name = Name; }

    const int GetHP() const { return HP; }

    void SetHP(const int HP) { this->HP = HP; }

    const int GetMaxHP() const { return MaxHP; }

    void SetMaxHP(const int MaxHP) { this->MaxHP = MaxHP; }

    const int GetDamage() const { return Damage; }

    void SetDamage(const int Damage) { this->Damage = Damage; }

    Entity(string Name, int MaxHP, int Damage)
    {
        this->Name = Name;
        this->MaxHP = MaxHP;
        this->HP = MaxHP; // 태어날 땐 최대 체력이 현재 체력과 같음
        this->Damage = Damage;
    }

	virtual void TakeDamage(int Damage) = 0;
    
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

    void CreateMonster();

    void SetGameEnded(bool InIsGameEnded){bIsGameEnded = InIsGameEnded;}
    
    bool IsGameEnded(){return bIsGameEnded;}
    
    void OnGameEnded();

    vector<unique_ptr<Monster>> Monsters;

    EEndType EndType = EEndType::None;
    
    void DisplayChoices();

    void Select();
    
    int RandRange(int Start, int End);
private:

    // Monster //
    const unsigned int MaxMonsterNum = 5;

    const unsigned int MinMonsterNum = 2;

    const unsigned int MaxMonsterTypeRange = 3; // Monster 클래스에 보스를 제외하고 슬라임 고블린 오크 3가지 존재

    const unsigned int MaxPlayerLevel = 10; // 10 레벨 달성시 Boss 몬스터와 전투

    bool bIsGameEnded = false;

    bool bBlockRegenerateMonster = false; // 상점 이동 후 몬스터 재생성 방지

    int PlayerChoice = 0;
    
    

    MainGame() = default;
};