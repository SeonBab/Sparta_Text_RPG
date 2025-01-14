// Monster.h
#pragma once

#include "Framework/Framework.h"

// 몬스터 정보를 담을 구조체
struct MonsterInfo {
    string name;
    int hp;
    int damage;
};

class Monster : public Entity {
public:
    // Entity의 생성자를 호출하는 Monster 생성자
    Monster(string name, int HP, int damage, int difficulty);

    // 몬스터 이름, HP, Damage 값을 생성하는 함수
    static MonsterInfo CreateMonsterInfo(int player_level, int difficulty);

    // 데미지 처리 함수 : 입력값 만큼 몬스터 체력 차감
    void TakeDamage(int Damage);

    // difficulty 값을 반환하는 Getter 함수
    int GetDifficulty() const { return difficulty; }

    int difficulty;  // 난이도 값을 저장하는 멤버 변수
};

