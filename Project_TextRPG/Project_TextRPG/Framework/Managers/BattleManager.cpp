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
    // true - 플레이어 승리, false - 몬스터 승리
    bool bIsPlayerWon = false;

    // 몬스터 //
    string MonsterName = SelectedMonster->GetName();
    int MonsterHP = SelectedMonster->GetHP();
    int MonsterDamage = SelectedMonster->GetDamage();
    int MonsterDifficulty = SelectedMonster->GetDifficulty();

    // 캐릭터 //
    string PlayerName = Player->GetName();
    int PlayerHP = Player->GetHP();
    int PlayerDamage = Player->GetDamage();
    int PlayerLevel = Player->GetLevel();

    // 클리어 보상 //  
    int Gold = 10;
    int Exp = 50;
    // 전투 시작전 30% 확률로 아이템 사용
    if (RandRange(1, 100) <= ItemProb)
    {
        // AttackBoost는 구입 즉시 스테이터스가 증가하도록 설정했으므로 현재는 HealthPortion만 사용가능
        // 다른 아이템 추가할꺼면 아이템 타입도 랜덤 값으로 받아와야함
        const int MaxItemType = 1;
        EItemType ItemType = static_cast<EItemType>(RandRange(0, MaxItemType));
        switch (ItemType)
        {
        case EItemType::HealthPotion:
            Player->UseItem(ItemType);
            break;
            // 아이템 종류 늘어나면 추가
        default:
            break;
        }
    }
    while (true)
    {
        if (PlayerHP)
        {
            std::cout << "플레이어가 사망했습니다. \n";
            bIsPlayerWon = false;
            break;
        }
        if (MonsterHP)
        {
            std::cout << "몬스터가 처치되었습니다. \n";
            // 몬스터에서 부스트 드랍되면 바로 사용되도록
            Gold = 10 * MonsterDifficulty; // 필수 구현 조건에서 골드 10~20으로 되어있음 -> 난이도에 따른 골드 비례 보상
            //Exp = Exp * MonsterDifficultLevel; // 필수 구현조건에서 경험치는 고정되어있음

            // 몬스터 난이도에 따라 다른 획득 보상
            Player->SetGold(Gold);

            Player->UpdateExp(Exp);

            std::cout << "플레이어가 " << Exp << " Exp와 " << Gold << " 골드를 획득했습니다. 현재 EXP:" << Player->GetExp() << '/100' <<
                ", 골드: " << Player->GetGold() << '\n';
            bIsPlayerWon = true;
            break;
        }

        std::cout << "몬스터 " << MonsterName << " 등장! 체력:" << MonsterHP << ", 공격력: " << MonsterDamage << '\n';

        // 플레이어 선공
        std::cout << "플레이어가 몬스터를 공격합니다!" << MonsterName << " 체력: " << MonsterHP << '\n';
        SelectedMonster->TakeDamage(PlayerDamage);

        std::cout << "몬스터가 플레이어를 공격합니다. 몬스터가 입힌 데미지: " << MonsterDamage << '\n';
        Player->TakeDamage(MonsterDamage);

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