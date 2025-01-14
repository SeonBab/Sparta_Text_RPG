#pragma once

#include <string>
#include <vector>
#include <memory>

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
    Item(std::string ItemName, int ItemGoldCost, EItemUsageType ItemUsageType) : Name(ItemName), GoldCost(ItemGoldCost), UsageType(ItemUsageType) {}

    virtual void Use() = 0;

    const std::string& GetName() const { return Name; }

    const int GetGoldCost() const { return GoldCost; }

    const EItemUsageType GetUsageType() const { return UsageType; }

private:
    std::string Name;
    int GoldCost;
    EItemUsageType UsageType;
};

class HealthPotion : public Item
{
public:
    HealthPotion() : Item("체력 포션", 10, EItemUsageType::Battle) { }

    virtual void Use() override;
};

class AttackBoost : public Item
{
public:
    AttackBoost() : Item("공격력 부스트", 15, EItemUsageType::Immediately) {}
    
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
        Items.push_back(std::make_shared<AttackBoost>());
    }
};