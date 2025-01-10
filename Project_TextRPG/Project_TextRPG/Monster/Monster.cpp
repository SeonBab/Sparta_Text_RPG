// Monster.cpp
#include "Monster.h"
#include <iostream>

// Entity 생성자 필요시 작성 필

Monster::Monster(int player_level, int difficulty) {

    this->difficulty = difficulty;  // 전달받은 난이도 값을 멤버 변수에 저장

    if (difficulty == 4) // 보스 몬스터
    {
        Name = "Boss Monster";
        HP = (rand() % 16 + 30) * player_level;  // (30~45) * 플레이어 레벨
        Damage = (rand() % 6 + 8) * player_level;    // (8~13) * 플레이어 레벨
    }
    else // 일반 몬스터
    {
        // 난이도에 따른 몬스터 체력과 공격력 설정
        if (difficulty == 1) { // 쉬움
            Name = "Slime";
            HP = (rand() % 11 + 20) * player_level;  // (20~30) * 플레이어 레벨
            Damage = (rand() % 6 + 5) * player_level;    // (5~10) * 플레이어 레벨
        }
        else if (difficulty == 2) { // 보통
            Name = "Goblin";
            HP = (rand() % 11 + 22) * player_level;  // (22~32) * 플레이어 레벨
            Damage = (rand() % 6 + 6) * player_level;    // (6~11) * 플레이어 레벨
        }
        else if (difficulty == 3) { // 어려움
            Name = "Oak";
            HP = (rand() % 11 + 25) * player_level;  // (25~35) * 플레이어 레벨
            Damage = (rand() % 6 + 7) * player_level;    // (7~12) * 플레이어 레벨
        }
    }

    cout << "몬스터 이름: " << Name << ", 체력: " << HP << ", 공격력: " << Damage << endl;
}

// 몬스터 데미지 처리 함수
void Monster::TakeDamage(int Damage) {
    HP -= Damage;  // 입력값 만큼 체력 차감

    // 체력이 0 이하로 떨어지면 "죽음" 처리
    if (HP <= 0) {
        HP = 0;  // 체력은 음수가 될 수 없으므로 0으로 고정
        std::cout << Name << "가 죽었습니다!" << std::endl;
    }
    else {
        std::cout << Name << "의 남은 체력: " << HP << std::endl;
    }
}