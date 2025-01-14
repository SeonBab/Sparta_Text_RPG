#include "Player.h"

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

//void Player::BuyItem(string itemName, int itemPrice, int count)
//{
//    int totalPrice = itemPrice * count;
//    if (Gold > totalPrice)
//    {
//        Gold -= totalPrice;
//        Inventory[itemName] += count;
//		cout << itemName << "을(를) " << count << "개 구매했습니다." << endl;
//    }
//    else
//    {
//		cout << "골드가 부족합니다." << endl;
//    }
//}
//
//void Player::SellItem(string itemName, int itemPrice, int count)
//{
//    if (Inventory[itemName] >= count)
//    {
//        int totalPrice = itemPrice * count;
//        Inventory[itemName] -= count;
//        Gold += totalPrice;
//		cout << itemName << "을(를) " << count << "개 판매했습니다." << endl;
//    }
//    else {
//		cout << "아이템이 부족합니다." << endl;
//    }
//}

void Player::UseItem(EItemType ItemType)
{
    //if (Inventory[itemName] > 0)
    //{
    //    Inventory[itemName]--;
    //}

    int ItemIdx = static_cast<int>(ItemType);
    if (EItemType::HealthPotion == ItemType)
    {
        if (Inventory[ItemIdx])
        {
            std::cout << "아이템 " << Inventory[ItemIdx]->GetName() << "을 사용합니다. 체력을 회복합니다.\n";

            // Item 클래스에서 구현중으로 보임. Player 클래스 체력은 Player 클래스에서 올리는게 맞지 않나 싶음
            Inventory[ItemIdx]->Use();
            //if (MaxHP + PortionAmount > 100)
            //{
            //    HP = MaxHP;
            //}
            //else
            //{
            //    HP += PortionAmount;
            //}
        }
    }
}

void Player::AddItem(EItemType ItemType)
{
    int ItemIdx = static_cast<int>(ItemType);
    switch (ItemType)
    {
    case EItemType::HealthPotion:
        ++Inventory[ItemIdx];
        break;
        // 아이템 종류 추가 되면 삽입
    default:
        break;
    }
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
