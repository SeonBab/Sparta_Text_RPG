#include "Monster.h"


string Strings[(unsigned int)EMonsterType::End]
{
    "A",
    "B",
    "C",
};

MonsterDef::MonsterDef()
{
    Level = min(1, rand() % (MaxLevel + 1));
    SetName(Strings[rand() % (unsigned int)EMonsterType::End]);
}

