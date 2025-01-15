// Monster.cpp
#include "Monster.h"
#include <iostream>

// Entity의 생성자를 호출하는 Monster 생성자
Monster::Monster(std::string name, int HP, int damage, int difficulty)
    : Entity(name, HP, damage), difficulty(difficulty) {
}

// 몬스터 이름, HP, Damage 값을 생성하는 함수
MonsterInfo Monster::CreateMonsterInfo(int player_level, int difficulty) {
    MonsterInfo info;

    if (difficulty == 4) { // 보스 몬스터
        info.name = "Boss";
        info.hp = (rand() % 16 + 30) * player_level;  // (30~45) * 플레이어 레벨
        info.damage = (rand() % 6 + 8) * player_level;    // (8~13) * 플레이어 레벨
    }
    else { // 일반 몬스터
        if (difficulty == 1) { // 쉬움
            info.name = "Slime";
            info.hp = (rand() % 11 + 20) * player_level;  // (20~30) * 플레이어 레벨
            info.damage = (rand() % 6 + 5) * player_level;    // (5~10) * 플레이어 레벨
        }
        else if (difficulty == 2) { // 보통
            info.name = "Goblin";
            info.hp = (rand() % 11 + 22) * player_level;  // (22~32) * 플레이어 레벨
            info.damage = (rand() % 6 + 6) * player_level;    // (6~11) * 플레이어 레벨
        }
        else if (difficulty == 3) { // 어려움
            info.name = "Oak";
            info.hp = (rand() % 11 + 25) * player_level;  // (25~35) * 플레이어 레벨
            info.damage = (rand() % 6 + 7) * player_level;    // (7~12) * 플레이어 레벨
        }
    }

    return info; // 계산된 몬스터 정보 반환
}

// 몬스터 데미지 처리 함수
void Monster::TakeDamage(int Damage) {
    HP -= Damage;  // 입력값 만큼 체력 차감
}
