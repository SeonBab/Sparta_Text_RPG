// Monster.h
#pragma once

#include "Framework/Framework.h"

// 몬스터 정보를 담을 구조체
struct FMonsterInfo {
    string MonsterName;
    int MonsterHp;
    int MonsterDamage;
};

class Monster : public Entity {
public:
    // Entity의 생성자를 호출하는 Monster 생성자
    Monster(string Name, int Hp, int Damage, int Difficulty);

    // 몬스터 이름, HP, Damage 값을 생성하는 함수
    static FMonsterInfo CreateMonsterInfo(int PlayerLevel, int Difficulty);

    // 데미지 처리 함수 : 입력값 만큼 몬스터 체력 차감
    void TakeDamage(int Damage);

    // Difficulty 값을 반환하는 Getter 함수
    int GetDifficulty() const { return Difficulty; }

    // 난이도 값을 저장하는 멤버 변수
    int Difficulty;  
};

