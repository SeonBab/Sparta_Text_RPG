#include "BattleManager.h"
#include "Character/Player.h"
#include "Monster/Monster.h"
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

        // 30% 확률로 아이템 사용
        if (RandRange(1, 100) <= 30)
        {
            // UseItem(Player->GetInventory());
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

// Player쪽(지훈님)하고 Item쪽(선국님)에서 인벤토리 타입이 아직 통일되지 않음
// ItemList에서는 vector<std::shared_ptr<Item>으로 사용하는거 같은데 Player쪽에서는 unordered_map<string, int>로 되어있어서 구현 보류함
//void BattleManager::UseItem(std::vector<Item*>& Inventory)
//{
//    if (!Inventory.empty())
//    {
//
//
//    }
//}

bool BattleManager::IsPlayerMaxLevel(int PlayerLevel)
{
    return MaxPlayerLevel == PlayerLevel;
}