#include "Player.h"

Player* Player::instance;


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
    if (Gold > totalPrice)
    {
        Gold -= totalPrice;
        Inventory[itemName] += count;
    }
    else
    {

    }
}

void Player::SellItem(string itemName, int itemPrice, int count)
{
    if (Inventory[itemName] >= count)
    {
        int totalPrice = itemPrice * count;
        Inventory[itemName] -= count;
        Gold += totalPrice;
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
