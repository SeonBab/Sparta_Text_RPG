#include "Framework.h"
#include <iostream>

#include "Monster/Monster.h"

void MainGame::Init()
{
    srand((unsigned int)time(NULL));
}

void MainGame::Select()
{
    int Idx = 0;
    while(true)
    {
        cin >> Idx;
        // Idx 1부터 시작 + Shop뒤에 붙음.
        if(Idx < Monsters.size() + 2 || Idx <= 0)
        {
            break;
        }
        else
        {
            cout << "Not Valid" << "\n";
        }
    }
}

void MainGame::Tick()
{
    // Console Clear
    system("cls");
    
    GenerateMonsterDefs();
    DisplayChoices();
    Select();
    
    // BattleManager->CreateMonsterFromDef
    // BattleManager->Battle
    // 분기 1. Battle()
    // Battle System : while()
    // system.pause(), delay()
    // Item 사용 - 알아서 하자.
    // 보상 - Item, Gold, Exp
    // 분기 1-1. Level 10 : 선택지를 바꿈.

    // ShopManager->DoSomething
    // 분기 2. Shop()
    // 선택지
    // while(bExit)
    
    // DisplayBuffer();
    
    // Status 출력

    // Game 출력
    if(bIsGameEnded)
    {
        OnGameEnded();
    }
}

MainGame& MainGame::Get()
{
    static MainGame Game;
    return Game;
}


void MainGame::GenerateMonsterDefs()
{
    Monsters.clear();

    int ClampedNum = min(MaxMonsterNum, max(rand() % (MaxMonsterNum + 1), MinMonsterNum));
    Monsters.resize(ClampedNum);
    for(int i = 0 ; i < Monsters.size(); ++i)
    {
        Monsters[i] = make_unique<MonsterDef>();
        cout << i + 1 << "." << Monsters[i].get()->GetName() << "  ";
    }
}

void MainGame::OnGameEnded()
{
    if(EndType == EEndType::Lose)
    {
        cout << "You Lose..." << "\n";
    }
    else if(EndType == EEndType::Win)
    {
        cout << "You Win!!!" << "\n";
    }
}

void MainGame::ClearBuffer()
{
    Buffer.clear();
}

void MainGame::AddStringToBuffer(const string& InString)
{
    Buffer.push_back(InString);
}

void MainGame::DisplayBuffer(bool bClear)
{
    system("cls");
    
    for(auto& String : Buffer)
    {
        cout << String << "\n";
    }
}

void MainGame::DisplayChoices()
{
    for(int i = 0 ; i < Monsters.size(); ++i)
    {
        cout << i + 1 << "." << Monsters[i].get()->GetName() << "  ";
    }

    cout << Monsters.size() + 1 << ". " << "Shop";
    cout << "\n";
}
