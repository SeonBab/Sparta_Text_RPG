#include "Item.h"
#include "Player/Player.h"

void HealthPotion::Use()
{
    // 체력 회복 물약이 회복시킬 값
    int HPRecovery = 5;

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

    std::cout << GetName() << "을(를) 사용하여" << "체력이 " << CurHP << "이(가) 됐습니다." << std::endl;
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

    std::cout << GetName() << "을(를) 사용하여" << "공격력이 " << DamageUp << "이(가) 됐습니다." << std::endl;
}
