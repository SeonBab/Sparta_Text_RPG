#pragma once

#include "Framework/Framework.h"

enum class EMonsterType
{
    A,
    B,
    C,
    End
};

extern string Strings[(unsigned int)EMonsterType::End];

class MonsterDef : public Entity
{
    
public:

    MonsterDef();

    void GenerataeLevel();
    
    void Display();

private:

    int MaxLevel;
    int Level;
    
};

class Monster : public Entity
{
    
public:
    
    // Def로 생성 로직 추가
    Monster(const MonsterDef& Def)
    {
    }
};