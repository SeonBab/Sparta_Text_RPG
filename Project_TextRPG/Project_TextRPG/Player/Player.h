#pragma once

#include "Framework/Framework.h"
#include "iostream"
#include "unordered_map"
#include <Framework/Managers/LogManager.h>

class Player : public Entity
{
private:

    static Player* Instance;
    int Level;
    int Exp;
    int Gold;
    unordered_map<string, int> Inventory;

    Player(string name);
    ~Player()
    {
		delete Instance;
		Instance = nullptr;
    }
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

public:

    static Player* GetInstance()
    {
        if (Instance == nullptr)
        {
            string name = "";
            Instance = new Player(name);
        }
		return Instance;
    }

    int GetGold() const { return Gold; }

    void SetGold(const int Gold) { this->Gold = Gold; }

    int GetLevel() const { return Level; }

    int GetExp() const { return Exp; }

    unordered_map<string, int> GetInventory() const { return Inventory; }

    void SetPlayerName();
    
    void TakeDamage(int Damage);

    void UpdateExp(int ExpAmount);

    void LevelUp();

    void BuyItem(string ItemName, int ItemPrice, int Count);

    void SellItem(string ItemName, int ItemPrice, int Count);

	void UseItem(string ItemName);

    void UseRandomItemOfInventory();

	void AddItem(string ItemName, int Count);

};


