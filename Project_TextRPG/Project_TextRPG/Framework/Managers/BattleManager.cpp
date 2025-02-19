﻿#include "BattleManager.h"
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
    LogManager::Get().Clear();
    LogManager::Get().Draw(EDraw::Fight);

    //근데 이럴꺼면 걍 이름 검사하지 그랬냐?
    pair<int, int> pos;
    switch (SelectedMonster->GetDraw())
    {
    case EDraw::Slime: pos = { 31, 23 }; break;
    case EDraw::Oak: pos = { 14, 8 }; break;
    case EDraw::Goblin: pos = { 29, 13 }; break;
    case EDraw::Boss: pos = { 2, 1 }; break;
    default:
        break;
    }

    LogManager::Get().Draw(SelectedMonster->GetDraw(), pos.first, pos.second);
    LogManager::Get().Draw(EDraw::Player, 0, 16);

    LogManager::Get() << "\n";

    // true - 플레이어 승리, false - 몬스터 승리
    bool bIsPlayerWon = false;

    // 클리어 보상 //  
    int Gold = 10;
    int Exp = 50;

    auto Items = ItemList::GetInstance().GetItems();

    LogManager::Get() << "몬스터 " << SelectedMonster->GetName() << " 등장! 체력:" << SelectedMonster->GetHP() << ", 공격력: " << SelectedMonster->GetDamage() << '\n';
    LogManager::Get().Delay(DelayTime);

    while (true)
    {
        // 플레이어 선공
        SelectedMonster->TakeDamage(Player->GetDamage());
        LogManager::Get() << "플레이어가 몬스터를 공격합니다! ";
        LogManager::Get().Delay(DelayTime);

        if (SelectedMonster->GetHP() > 0)
        {
            LogManager::Get() << '\n' << SelectedMonster->GetName() << "의 남은 체력: " << SelectedMonster->GetHP() << '\n';
            LogManager::Get().Delay(DelayTime);

            // 전투 턴이 끝날 때마다 아이템 사용(플레이어 턴 끝)
            if (ItemUseProb >= RandRange(1, 100))
            {
                Player->UseRandomItemOfInventory();
            }
        }
        else
        {
            LogManager::Get() << '\n' << SelectedMonster->GetName() << "가 죽었습니다!\n";
            LogManager::Get().Delay(DelayTime);
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
                LogManager::Get().Delay(DelayTime);
                Player->AddItem(Items[RandItemIdx].get()->GetName(), 1);
            }
            LogManager::Get() << "플레이어가 " << Exp << " Exp와 " << Gold << " 골드를 획득했습니다. \nEXP : " << Player->GetExp() << " / 100" << ", 골드: " << Player->GetGold() << '\n';
            LogManager::Get().Delay(DelayTime);
            bIsPlayerWon = true;
            break;
        }

        Player->TakeDamage(SelectedMonster->GetDamage());
        LogManager::Get() << "몬스터가 플레이어를 공격합니다. ";

        if (Player->GetHP() > 0)
        {
            LogManager::Get() << "\n플레이어의 남은 체력 : " << Player->GetHP() << '\n';
            LogManager::Get().Delay(DelayTime);


            // 전투 턴이 끝날 때마다 아이템 사용(몬스터 턴 끝)
            if (ItemUseProb >= RandRange(1, 100))
            {
                Player->UseRandomItemOfInventory();
            }
        }
        else
        {
            LogManager::Get() << "\n플레이어가 사망했습니다. \n";
            LogManager::Get().Delay(DelayTime);
            bIsPlayerWon = false;
            break;
        }
    }

    // 배틀 종료 이후 죽은 몬스터의 전체 횟수 출력
    Monster::PrintAllDeathCounts();
    LogManager::Get().Delay(DelayTime);

    return bIsPlayerWon;
}

int BattleManager::RandRange(int Start, int End)
{
    std::random_device Rd;
    std::mt19937 Gen(Rd());
    std::uniform_int_distribution<int> Dis(Start, End);
    return Dis(Gen);
}