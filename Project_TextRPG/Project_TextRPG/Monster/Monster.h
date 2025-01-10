// Monster.h
#pragma once

#include "../Framework/Framework.h"

class Monster : public Entity {
public:
    // Entity 생성자 (구현 필요?)
    Monster(string name, int maxHP, int damage);

    // 생성자 : 플레이어 및 난이도에 따른 몬스터 생성
    Monster(int player_level, int difficulty);

    // 데미지 처리 함수 : 입력값 만큼 몬스터 체력 차감
    void TakeDamage(int Damage);

    // difficulty 값을 반환하는 Getter 함수
    int GetDifficulty() const { return difficulty; }

private:
    int difficulty;  // 난이도 값을 저장하는 멤버 변수
};