#include "BattleManager.h"
#include "Player/Player.h"
#include "Monster/Monster.h"
#include "Item.h"
#include <random>
#include <string>
#include <vector>
#include <memory>
#include <iostream>

BattleManager BattleManager::Instance;

bool BattleManager::Battle(Monster* SelectedMonster, Player* Player)
{
    // true - 플레이어 승리, false - 몬스터 승리
    bool bIsPlayerWon = false;

    // 클리어 보상 //  
    int Gold = 10;
    int Exp = 50;

    auto Items = ItemList::GetInstance().GetItems();
    // 전투 시작전 30% 확률로 아이템 사용
    if (ItemUseProb >= RandRange(1, 100))
    {
        // 플레이어 클래스의 인벤토리에 직접 접근하는 것으로 변경됨
        // ItemList 클래스에 있는 종류중에 한가지 사용
        int ItemType = RandRange(0, Items.size() - 1);
        Player->UseItem(Items[ItemType].get()->GetName());
    }
    LogManager::Get() << "몬스터 " << SelectedMonster->GetName() << " 등장! 체력:" << SelectedMonster->GetHP() << ", 공격력: " << SelectedMonster->GetDamage() << '\n';

    while (true)
    {
        // 플레이어 선공
        SelectedMonster->TakeDamage(Player->GetDamage());
        LogManager::Get() << "플레이어가 몬스터를 공격합니다! ";
        if (SelectedMonster->GetHP() > 0)
        {
            LogManager::Get() << SelectedMonster->GetName() << " 몬스터의 남은 체력: " << SelectedMonster->GetHP() << '\n';
        }
        else
        {
            LogManager::Get() << SelectedMonster->GetName() << "가 죽었습니다!\n";
            // 몬스터에서 부스트 드랍되면 바로 사용되도록
            Gold = 10 * SelectedMonster->GetDifficulty();
            Exp = Exp * SelectedMonster->GetDifficulty() * 0.5;

            // 몬스터 난이도에 따라 다른 획득 보상
            Player->SetGold(Player->GetGold() + Gold);

            Player->UpdateExp(Exp);
            if (ItemDropProb >= RandRange(0, 100)) // Drop Item
            {
                const int RandItemIdx = RandRange(0, Items.size() - 1);
                LogManager::Get() << Items[RandItemIdx].get()->GetName() << " 아이템 획득!\n";
                Player->AddItem(Items[RandItemIdx].get()->GetName(), 1);
            }
            LogManager::Get() << "플레이어가 " << Exp << " Exp와 " << Gold << " 골드를 획득했습니다. EXP : " << Player->GetExp() << " / 100" << ", 골드: " << Player->GetGold() << '\n';
            bIsPlayerWon = true;
            break;
        }
        Player->TakeDamage(SelectedMonster->GetDamage());
        LogManager::Get() << "몬스터가 플레이어를 공격합니다. ";
        if (Player->GetHP() > 0)
        {
            LogManager::Get() << "플레이어의 남은 체력 : " << Player->GetHP() << '\n';
        }
        else
        {
            LogManager::Get() << "플레이어가 사망했습니다. \n";
            bIsPlayerWon = false;
            break;
        }
    }
    return bIsPlayerWon;
}

int BattleManager::RandRange(int start, int end)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(start, end);
    return dis(gen);
}