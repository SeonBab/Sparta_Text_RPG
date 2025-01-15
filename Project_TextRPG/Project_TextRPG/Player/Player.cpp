#include "Player.h"
#include "Item.h"
#include "Framework/Managers/LogManager.h"

Player* Player::instance;

Player::Player(string name) : Entity(name, 200, 30)
{
	instance = nullptr;

	Level = 1;
	Exp = 0;
	Gold = 0;
}

void Player::SetPlayerName()
{
	string name;
	LogManager::Get().Append("이름을 입력하세요: ");
	cin >> name;
	Name = name;
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

	MaxHP += Level * 10;
    HP = MaxHP;
	Damage += Level * 5;
	LogManager::Get().Append("플레이어 레벨업! 현재 레벨: " + std::to_string(Level) + "\n");
    Exp -= 100;
}

void Player::BuyItem(string itemName, int itemPrice, int count)
{
	int totalPrice = itemPrice * count;
	if (Gold >= totalPrice)
	{
		Gold -= totalPrice;
		LogManager::Get().Append(itemName + "을(를) " + std::to_string(count) + "개 구매했습니다.\n");
		Player::AddItem(itemName, count);
	}
	else
	{
		LogManager::Get().Append("골드가 부족합니다.\n");
	}
}

void Player::SellItem(string itemName, int itemPrice, int count)
{
	if (Inventory[itemName] >= count)
	{
		int totalPrice = itemPrice * count;
		Inventory[itemName] -= count;
		Gold += totalPrice;
		LogManager::Get().Append(itemName + "을(를) " + std::to_string(count) + "개 판매했습니다.\n");
	}
	else {
		LogManager::Get().Append("아이템이 부족합니다.\n");
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
			LogManager::Get().Append("잘못된 아이템 접근입니다\n");
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
		LogManager::Get().Append("잘못된 아이템 접근입니다\n");
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
