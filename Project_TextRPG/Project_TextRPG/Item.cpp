#include "Item.h"
#include "Player/Player.h"

void HealthPotion::Use()
{
    // 체력 회복 물약이 회복시킬 값
    int HPRecovery = 50;

    // 플레이어 가져오기
    Player* CurPlayer = Player::GetInstance();
    if (nullptr == CurPlayer)
    {
        return;
    }

    int CurHP = CurPlayer->GetHP();

    // HP를 회복시키려 할 때 최대 체력보다 높아지지 않도록 설정
    CurHP = (CurHP + HPRecovery > CurPlayer->GetMaxHP()) ? CurPlayer->GetMaxHP() : CurHP + HPRecovery;

    CurPlayer->SetHP(CurHP);

    LogManager::Get() << GetName() << "을(를) 사용하여 " << "체력이 " << CurHP << "이(가) 됐습니다." << "\n";

    LogManager::Get().Draw(GetDrawImage(), 5);
}

void HealthElixir::Use()
{
    // 플레이어 가져오기
    Player* CurPlayer = Player::GetInstance();
    if (nullptr == CurPlayer)
    {
        return;
    }

    // 체력 엘릭서가 회복시킬 값
    // 최대 체력으로 회복
    int HPRecovery = CurPlayer->GetMaxHP();

    CurPlayer->SetHP(HPRecovery);

    LogManager::Get() << GetName() << "을(를) 사용하여 " << "체력이 " << HPRecovery << "이(가) 됐습니다." << "\n";

    LogManager::Get().Draw(GetDrawImage(), 5);
}

void MoneyBag::Use()
{
    // 돈가방이 증가시킬 골드 값
    int GoldUp = 20;

    // 플레이어 가져오기
    Player* CurPlayer = Player::GetInstance();
    if (nullptr == CurPlayer)
    {
        return;
    }

    GoldUp = CurPlayer->GetGold() + GoldUp;

    CurPlayer->SetGold(GoldUp);

    LogManager::Get() << GetName() << "을(를) 사용하여 " << "골드가 " << GoldUp << "이(가) 됐습니다." << "\n";

    LogManager::Get().Draw(GetDrawImage(), 5);
}

void AttackBoost::Use()
{
    // 공격력 부스트가 증가시킬 공격력 값
    int DamageUp = 10;

    // 플레이어 가져오기
    Player* CurPlayer = Player::GetInstance();
    if (nullptr == CurPlayer)
    {
        return;
    }

    DamageUp = CurPlayer->GetDamage() + DamageUp;

    CurPlayer->SetDamage(DamageUp);

    LogManager::Get() << GetName() << "을(를) 사용하여 " << "공격력이 " << DamageUp << "이(가) 됐습니다." << "\n";

    LogManager::Get().Draw(GetDrawImage(), 5);
}

void HealthBoost::Use()
{
    // 체력 부스트가 증가시킬 체력 값
    int HPUp = 10;

    // 플레이어 가져오기
    Player* CurPlayer = Player::GetInstance();
    if (nullptr == CurPlayer)
    {
        return;
    }

    HPUp = CurPlayer->GetMaxHP() + HPUp;

    CurPlayer->SetDamage(HPUp);

    LogManager::Get() << GetName() << "을(를) 사용하여 " << "최대 체력이 " << HPUp << "이(가) 됐습니다." << "\n";

    LogManager::Get().Draw(GetDrawImage(), 5);
}