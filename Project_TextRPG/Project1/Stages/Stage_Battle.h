#pragma once
#include <functional>

#include "Managers/Stage/Stage.h"
class Actor;
using namespace std;

class Stage_Battle : public Stage
{
public:
    virtual void Init() override;

    virtual void Tick(float DeltaTime) override;
    
    virtual void Render() override;

protected:

    unsigned int MaxMonsterNum = 6;
    unsigned int MinMonsterNum = 1;
    
};
