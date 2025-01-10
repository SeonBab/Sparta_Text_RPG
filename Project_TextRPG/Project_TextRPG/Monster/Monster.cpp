#include "Monster.h"


string Strings[(unsigned int)EMonsterType::End]
{
    "A",
    "B",
    "C",
};

MonsterDef::MonsterDef()
{
    Level = rand() % 10;
    SetName(Strings[rand() % (unsigned int)EMonsterType::End]);
}