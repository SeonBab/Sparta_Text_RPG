#pragma once

#include <string>
#include <vector>
#include <memory>
#include "Framework/Managers/LogManager.h"

enum class EItemUsageType
{
    Immediately,
    Battle,
    NONE,
};

class Item
{
public:
    Item() = delete;
    Item(std::string ItemName, int ItemGoldCost, EItemUsageType ItemUsageType, EDraw ItemDrawImage) : 
        Name(ItemName), GoldCost(ItemGoldCost), UsageType(ItemUsageType), DrawImage(ItemDrawImage) { }

    virtual void Use() = 0;

    const std::string& GetName() const { return Name; }

    const int GetGoldCost() const { return GoldCost; }

    const EItemUsageType GetUsageType() const { return UsageType; }

    const EDraw GetDrawImage() const { return DrawImage; }

private:
    std::string Name;
    int GoldCost;
    EItemUsageType UsageType;
    EDraw DrawImage;
};

class HealthPotion : public Item
{
public:
    HealthPotion() : Item("체력 포션", 10, EItemUsageType::Battle, EDraw::Potion) { }

    virtual void Use() override;
};

class HealthElixir : public Item
{
public:
    HealthElixir() : Item("체력 엘릭서", 30, EItemUsageType::Battle, EDraw::HelthElixir) {}

    virtual void Use() override;
};

class MoneyBag : public Item
{
public:
    MoneyBag() : Item("돈 가방", 10, EItemUsageType::Battle, EDraw::MoneyBag) {}

    virtual void Use() override;
};

class AttackBoost : public Item
{
public:
    AttackBoost() : Item("공격력 부스트", 15, EItemUsageType::Immediately, EDraw::AttackBoost) { }
    
    virtual void Use() override;
};

class HealthBoost : public Item
{
public:
    HealthBoost() : Item("체력 부스트", 20, EItemUsageType::Immediately, EDraw::HealthBoost) {}

    virtual void Use() override;
};

class ItemList
{
private:
    std::vector<std::shared_ptr<Item>> Items;

public:
    static const ItemList& GetInstance()
    {
        static ItemList Instance;
        return Instance;
    }

    const std::vector<std::shared_ptr<Item>>& GetItems() const { return Items; }

    const std::shared_ptr<Item>& GetItem(const std::string& Name)
    {
        for (int i = 0; i < Items.size(); ++i)
        {
            if (Items[i]->GetName() == Name)
            {
                return Items[i];
            }
        }

        return nullptr;
    }

private:
    ItemList()
    {
        Items.push_back(std::make_shared<HealthPotion>());
        Items.push_back(std::make_shared<HealthElixir>());
        Items.push_back(std::make_shared<MoneyBag>());
        Items.push_back(std::make_shared<AttackBoost>());
        Items.push_back(std::make_shared<HealthBoost>());
    }
};