#pragma once

#include <string>
#include <vector>
#include <memory>

class Item
{
public:
    Item() = delete;
    Item(std::string Name, int GoldCost) : Name(Name), GoldCost(GoldCost) {}

    virtual void Use() = 0;

    const std::string& GetName() const { return Name; }

    const int GetGoldCost() const { return GoldCost; }

private:
    std::string Name;
    int GoldCost;
};

class HealthPotion : public Item
{
public:
    HealthPotion() : Item("ü�� ����", 10) { }

    virtual void Use() override
    {
        // TODO
        // �÷��̾� ü�� ȸ���ǰ�
        // ��¿� ��ȣ
    }
};

class AttackBoost : public Item
{
public:
    AttackBoost() : Item("���ݷ� �ν�Ʈ", 15) {}
    
    virtual void Use() override
    {
        // TODO
        // �÷��̾� ���ݷ��� ������
        // ��¿� ��ȣ
    }
};

class ItemList
{
private:
    std::vector<std::shared_ptr<Item>> Items;

public:
    static const ItemList& GetInatance()
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
        Items.push_back(std::make_unique<HealthPotion>());
        Items.push_back(std::make_unique<AttackBoost>());
    }
};