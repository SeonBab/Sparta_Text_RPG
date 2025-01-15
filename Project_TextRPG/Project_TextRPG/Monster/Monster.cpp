// Monster.cpp
#include "Monster.h"
#include <iostream>

// Entity의 생성자를 호출하는 Monster 생성자
Monster::Monster(string Name, int Hp, int Damage, int Difficulty)
    : Entity(Name, Hp, Damage), Difficulty(Difficulty) {
}

// 몬스터 이름, 체력, 공격력 값을 생성하는 함수
FMonsterInfo Monster::CreateMonsterInfo(int PlayerLevel, int Difficulty) {
    FMonsterInfo MonsterInfo;

    if (Difficulty == 4) { // 보스 몬스터
        MonsterInfo.MonsterName = "Boss";
        MonsterInfo.MonsterHp = (rand() % 16 + 30) * PlayerLevel;  // (30~45) * 플레이어 레벨
        MonsterInfo.MonsterDamage = (rand() % 6 + 8) * PlayerLevel;    // (8~13) * 플레이어 레벨
    }
    else { // 일반 몬스터
        if (Difficulty == 1) { // 쉬움 난이도 몬스터
            MonsterInfo.MonsterName = "Slime";
            MonsterInfo.MonsterHp = (rand() % 11 + 20) * PlayerLevel;  // (20~30) * 플레이어 레벨
            MonsterInfo.MonsterDamage = (rand() % 6 + 5) * PlayerLevel;    // (5~10) * 플레이어 레벨
        }
        else if (Difficulty == 2) { // 보통 난이도 몬스터
            MonsterInfo.MonsterName = "Goblin";
            MonsterInfo.MonsterHp = (rand() % 11 + 22) * PlayerLevel;  // (22~32) * 플레이어 레벨
            MonsterInfo.MonsterDamage = (rand() % 6 + 6) * PlayerLevel;    // (6~11) * 플레이어 레벨
        }
        else if (Difficulty == 3) { // 어려움 난이도 몬스터
            MonsterInfo.MonsterName = "Oak";
            MonsterInfo.MonsterHp = (rand() % 11 + 25) * PlayerLevel;  // (25~35) * 플레이어 레벨
            MonsterInfo.MonsterDamage = (rand() % 6 + 7) * PlayerLevel;    // (7~12) * 플레이어 레벨
        }
    }

    return MonsterInfo; // 계산된 몬스터 정보 반환
}

// 몬스터 데미지 처리 함수
void Monster::TakeDamage(int Damage) {
    HP -= Damage;  // 입력값 만큼 체력 차감
}
