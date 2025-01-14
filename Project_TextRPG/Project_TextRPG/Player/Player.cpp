#include "Player.h"
#include "Item.h"

Player* Player::instance;
std::mutex Player::mtx;

Player::Player(string name) : Entity(name, 200, 30)
{
    Level = 1;
    Exp = 0;
    Gold = 0;
}


void Player::TakeDamage(int damage)
{
    HP -= damage;
}

void Player::UpdateExp(int expAmount)
{
    Exp += expAmount;
    if (Exp >= 100)
        LevelUp();
}

void Player::LevelUp()
{
    Level++;
    Exp -= 100;
}

void Player::BuyItem(string itemName, int itemPrice, int count)
{
    int totalPrice = itemPrice * count;
    if (Gold >= totalPrice)
    {
        Gold -= totalPrice;
		cout << itemName << "을(를) " << count << "개 구매했습니다." << endl;
        Player::AddItem(itemName, count);
    }
    else
    {
		cout << "골드가 부족합니다." << endl;
    }
}

void Player::SellItem(string itemName, int itemPrice, int count)
{
    if (Inventory[itemName] >= count)
    {
        int totalPrice = itemPrice * count;
        Inventory[itemName] -= count;
        Gold += totalPrice;
		cout << itemName << "을(를) " << count << "개 판매했습니다." << endl;
    }
    else {
		cout << "아이템이 부족합니다." << endl;
    }
}

void Player::UseItem(string itemName)
{
    if (Inventory[itemName] > 0)
    {
        // 배틀 아이템 사용
        ItemList itemList = ItemList::GetInstance();
        std::shared_ptr<Item> item = itemList.GetItem(itemName);

        if (item != nullptr)
        {
            item->Use();
            Inventory[itemName]--;
        }
        else
            cout << "잘못된 아이템 접근입니다" << endl;
    }
}

void Player::AddItem(string itemName, int count)
{
    ItemList itemList = ItemList::GetInstance();
    std::shared_ptr<Item> item = itemList.GetItem(itemName);

    if (item != nullptr) 
    {
		if (item->GetUsageType() == EItemUsageType::Immediately)
		{
            // Count 만큼 아이템 즉시 사용
			for (int i = 0; i < count; i++)
                item->Use();
		}
		else if (item->GetUsageType() == EItemUsageType::Battle)
		{
			Inventory[itemName] += count;
		}
    }
    else
        cout << "잘못된 아이템 접근입니다" << endl;
}

int Player::GetGold()
{
    return Gold;
}

void Player::SetGold(int Gold)
{
    this->Gold = Gold;
}

int Player::GetLevel()
{
    return Level;
}

int Player::GetExp()
{
    return Exp;
}

unordered_map<string, int> Player::GetInventory()
{
	return Inventory;
}
