#include "Framework.h"
#include <iostream>
#include <windows.h>

#include "Monster/Monster.h"

void MainGame::Init()
{
    srand((unsigned int)time(NULL));
}

void MainGame::Tick()
{
    // Console Clear
    system("cls");
    
    GenerateMonster();
    cout << Monsters.size() + 1 << ". " << "Shop";
    cout << "\n";
    // cout << 선택지 - 몬스터 여러 개, 상점
    
    
    // cin >> 내 선택지 ( valid할 때 까지)
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

    //
    DisplayBuffer();
    
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

void MainGame::GenerateMonster()
{
    Monsters.clear();
    
    Monsters.resize(rand() % MonsterNum);
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

void MainGame::DisplayBuffer()
{
    for(auto& String : Buffer)
    {
        cout << String << "\n";
    }
}
