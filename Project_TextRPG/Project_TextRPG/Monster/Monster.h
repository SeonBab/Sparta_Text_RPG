// Monster.h
#pragma once

#include "Framework/Framework.h"
#include "Framework/Managers/LogManager.h"
#include <unordered_map>

// 몬스터 정보를 담을 구조체
struct FMonsterInfo {
    string MonsterName;
    EDraw MonsterDraw;
    int MonsterHp;
    int MonsterDamage;
};

class Monster : public Entity {
private:
    EDraw Draw;

    // 몬스터 이름별로 죽은 횟수 저장
    static unordered_map<string, int> DeathCountMap;

public:
    // Entity의 생성자를 호출하는 Monster 생성자
    Monster(string Name, int Hp, int Damage, int Difficulty, EDraw Draw);

    // 몬스터 이름, HP, Damage 값을 생성하는 함수 (static을 이용하여 몬스터 객체를 생성하지 않고 사용)
    static FMonsterInfo CreateMonsterInfo(int PlayerLevel, int Difficulty);

    // 데미지 처리 함수 : 입력값 만큼 몬스터 체력 차감
    void TakeDamage(int Damage);

    // 모든 몬스터의 죽은 횟수를 출력
    static void PrintAllDeathCounts();

    // Difficulty 값을 반환하는 Getter 함수
    int GetDifficulty() const { return Difficulty; }
    EDraw GetDraw() const { return Draw; }

    // 난이도 값을 저장하는 멤버 변수
    int Difficulty;
};

