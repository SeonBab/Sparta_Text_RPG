#pragma once

#include "Framework/Framework.h"
#include "iostream"
#include "unordered_map"

class Player : public Entity
{
private:

    static Player* instance;
    int Level;
    int Exp;
    int Gold;
    unordered_map<string, int> Inventory;

    Player(string name);
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

public:

    // 해당 함수 Framework init에서 최초 실행 필요
    static Player* GetInstance()
    {
        if(instance == nullptr)
        {
            string name;
            cout << "이름을 입력하세요: ";
            cin >> name;
            instance = new Player(name);
        }
        return instance;
    }

    void TakeDamage(int damage);

    void UpdateExp(int expAmount);

    void LevelUp();

    void BuyItem(string itemName, int itemPrice, int count);

    void SellItem(string itemName, int itemPrice, int count);

    int GetGold();

    void SetGold(int Gold);

    int GetLevel();

    int GetExp();

};


