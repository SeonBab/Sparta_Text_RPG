#include "Player.h"
#include "Item.h"
#include "Framework/Managers/LogManager.h"

Player* Player::Instance;

Player::Player(string name) : Entity(name, 200, 30)
{
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

void Player::TakeDamage(int Damage)
{
	HP -= Damage;
}

void Player::UpdateExp(int ExpAmount)
{
	Exp += ExpAmount;
	if (Exp >= 100)
		LevelUp();
}

void Player::LevelUp()
{ 
    Level++;

	MaxHP += Level * 10;
    HP = MaxHP;
	Damage += Level * 5;
	LogManager::Get().Draw(EDraw::LevelUp, 3, 3);
	LogManager::Get().Append("플레이어 레벨업! 현재 레벨: " + std::to_string(Level) + "\n");
    Exp -= 100;
}

void Player::BuyItem(string ItemName, int ItemPrice, int Count)
{
	int TotalPrice = ItemPrice * Count;
	if (Gold >= TotalPrice)
	{
		Gold -= TotalPrice;
		LogManager::Get().Append(ItemName + "을(를) " + std::to_string(Count) + "개 구매했습니다.\n");
		Player::AddItem(ItemName, Count);
	}
	else
	{
		LogManager::Get().Append("골드가 부족합니다.\n");
	}
}

void Player::SellItem(string ItemName, int ItemPrice, int Count)
{
	if (Inventory[ItemName] >= Count)
	{
		int TotalPrice = ItemPrice * Count;
		Inventory[ItemName] -= Count;
		Gold += TotalPrice;
		LogManager::Get().Append(ItemName + "을(를) " + std::to_string(Count) + "개 판매했습니다.\n");
	}
	else 
	{
		LogManager::Get().Append("아이템이 부족합니다.\n");
	}
}

void Player::UseItem(string ItemName)
{
	if (Inventory[ItemName] > 0)
	{
		// 배틀 아이템 사용
		ItemList itemList = ItemList::GetInstance();
		std::shared_ptr<Item> item = itemList.GetItem(ItemName);

		if (item != nullptr)
		{
			item->Use();
			Inventory[ItemName]--;
		}
		else 
		{
			LogManager::Get().Append("잘못된 아이템 접근입니다\n");
		}
	}
}

void Player::UseRandomItemOfInventory() {
	vector<string> ValidItems;
	for (auto& Item : Inventory)
	{
		if (Item.second > 0) {
			ValidItems.push_back(Item.first);
		}
	}
	if (ValidItems.size() != 0)
	{
		int RandomIndex = rand() % ValidItems.size();
		string RandomItem = ValidItems[RandomIndex];
		UseItem(RandomItem);
	}
}

void Player::AddItem(string ItemName, int Count)
{
	ItemList itemList = ItemList::GetInstance();
	std::shared_ptr<Item> Item = itemList.GetItem(ItemName);

	if (Item != nullptr)
	{
		if (Item->GetUsageType() == EItemUsageType::Immediately)
		{
			// Count 만큼 아이템 즉시 사용
			for (int i = 0; i < Count; i++)
				Item->Use();
		}
		else if (Item->GetUsageType() == EItemUsageType::Battle)
		{
			Inventory[ItemName] += Count;
		}
	}
	else {
		LogManager::Get().Append("잘못된 아이템 접근입니다\n");
	}
}

