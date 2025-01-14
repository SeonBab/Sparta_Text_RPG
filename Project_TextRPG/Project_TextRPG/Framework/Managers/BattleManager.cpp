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
    if (ItemUseProb >= RandRange(1, 100))
    {
        // 플레이어 클래스의 인벤토리에 직접 접근하는 것으로 변경됨
        auto Items = ItemList::GetInstance().GetItems();
        // ItemList 클래스에 있는 종류중에 한가지 사용
        int ItemType = RandRange(0, Items.size() - 1);
        Player->UseItem(Items[ItemType].get()->GetName());
    }
    while (true)
    {
        std::cout << "몬스터 " << MonsterName << " 등장! 체력:" << MonsterHP << ", 공격력: " << MonsterDamage << '\n';

        // 플레이어 선공
        std::cout << "플레이어가 몬스터를 공격합니다! " << MonsterName << " 체력: " << MonsterHP << '\n';
        SelectedMonster->TakeDamage(PlayerDamage);
        MonsterHP = SelectedMonster->GetHP();
        if (MonsterHP <= 0)
        {
            // 몬스터에서 부스트 드랍되면 바로 사용되도록
            Gold = 10 * MonsterDifficulty; // 필수 구현 조건에서 골드 10~20으로 되어있음 -> 난이도에 따른 골드 비례 보상
            //Exp = Exp * MonsterDifficultLevel; // 필수 구현조건에서 경험치는 고정되어있음

            // 몬스터 난이도에 따라 다른 획득 보상
            Player->SetGold(Gold);

            Player->UpdateExp(Exp);

            if (ItemDropProb >= RandRange(0, 100)) // Drop Item
            {
                const int RandItemIdx = RandRange(0, 1); // 지금은 아이템 2개. 아이템 타입 종류가 총 몇개인지 Item클래스에서 건네받는게 좋아보임
                switch (RandItemIdx)
                {
                case 0: // HealthPortion
                    std::cout << "HealthPotion 아이템 획득! \n";
                    Player->AddItem("HealthPotion", 1);
                    break;

                case 1: // AttackBoost
                    // AttackBoost는 바로 사용되게끔 설정 -> AddItem하면 그쪽에서 바로 사용되게끔 변경됨
                    std::cout << "AttackBoost 아이템 획득! \n";
                    Player->AddItem("AttackBoost", 1);
                    break;

                default:
                    break;
                }
            }

            std::cout << "플레이어가 " << Exp << " Exp와 " << Gold << " 골드를 획득했습니다. 현재 EXP:" << Player->GetExp() << "/100" <<
                ", 골드: " << Player->GetGold() << '\n';
            bIsPlayerWon = true;
            break;
        }

        std::cout << "몬스터가 플레이어를 공격합니다. 몬스터가 입힌 데미지: " << MonsterDamage << '\n';
        Player->TakeDamage(MonsterDamage);
        PlayerHP = Player->GetHP();
        if (PlayerHP <= 0)
        {
            std::cout << "플레이어가 사망했습니다. \n";
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