#pragma once

#include "Framework/Framework.h"
#include "iostream"
#include "unordered_map"
#include "Item.h"
#include "mutex"

class Player : public Entity
{
private:

    static Player* instance;
    static std::mutex mtx;
    int Level;
    int Exp;
    int Gold;
    //unordered_map<string, int> Inventory;
    vector<Item*> Inventory; // Item 클래스 구현되었으니 사용하는게?

    Player(string name);
    ~Player()
    {
		delete instance;
		instance = nullptr;
    }
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;

public:

    static Player* GetInstance()
    {
        if(instance == nullptr)
        {
            std::lock_guard<std::mutex> lock(mtx);
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

	void UseItem(EItemType ItemType);

	void AddItem(EItemType ItemType);

    int GetGold();

    void SetGold(int Gold);

    int GetLevel();

    int GetExp();

};


