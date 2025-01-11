#include "Framework.h"
#include <iostream>
#include <random>
#include "Framework/Managers/LogManager.h"
#include "Monster/Monster.h"
#include "Framework/Managers/ShopManager.h"
#include "Framework/Managers/BattleManager.h"

void MainGame::Init()
{
    srand((unsigned int)time(NULL));
}

void MainGame::Select()
{
    while(true)
    {
        cin >> PlayerChoice;
        // Idx 1부터 시작 + Shop뒤에 붙음.
        if(1 <= PlayerChoice && PlayerChoice < Monsters.size() + 2)
        {
            if (Monsters.size() + 1 == PlayerChoice)
            {
                ShopManager::PrintShopMenu();
            }
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
    LogManager::Get().Clear();
    
    // 유저 입력 이전에 떠야함
    LogManager::Get().ShowStatus();

    // 10레벨 달성시 보스 몬스터와 강제 전투이므로 DisplayChoices() 함수 앞에 와야함
    if (MaxPlayerLevel == Player::GetInstance()->GetLevel())
    {
        unique_ptr<Monster> BossMonster = make_unique<Monster>(10, 4);
        BattleManager::Get().Battle(BossMonster.get(), Player::GetInstance());
    }

    CreateMonster();
    DisplayChoices();
    Select();
    
    LogManager::Get().ShowLog();

    BattleManager::Get().Battle(Monsters[PlayerChoice].get(), Player::GetInstance());
    

    // system.pause(), delay()
    // Item 사용 - 알아서 하자.
    // 보상 - Item, Gold, Exp
    // 분기 1-1. Level 10 : 선택지를 바꿈.

    // ShopManager->DoSomething
    // 분기 2. Shop()
    // 선택지
    // while(bExit)
    
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


void MainGame::CreateMonster()
{
    Monsters.clear();
    //int ClampedNum = min(MaxMonsterNum, max(rand() % (MaxMonsterNum + 1), MinMonsterNum));

    const int RandMonstersArrSize = RandRange(MinMonsterNum, MaxMonsterNum);
    Monsters.resize(RandMonstersArrSize);

    for(int i = 0 ; i < Monsters.size(); ++i)
    {
        // 슬라임 고블린 오크중 무작위 생성
        const int RandMonsterType = RandRange(0, MaxMonsterTypeRange);
        Monsters[i] = make_unique<Monster>(Player::GetInstance()->GetLevel(), RandMonsterType);
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

void MainGame::DisplayChoices()
{
    std::cout << "눈 앞에 " << Monsters.size() << "개의 갈림길이 있습니다. 각 갈림길마다 적 몬스터의 기운이 느껴집니다. \n";
    
    for(int i = 0 ; i < Monsters.size(); ++i)
    {
        std::cout << i + 1 << "번째 길: " << Monsters[i].get()->GetName() << '(';
        for (int j = 0; j < Monsters[i].get()->GetDifficulty(); ++j) // 몬스터 난이도에 따라 별 출력
        {
            std::cout << '*';
        }
        std::cout << ")\n";
    }

    cout << Monsters.size() + 1 << ". " << "Shop";
    cout << "\n";
}

int MainGame::RandRange(int Start, int End)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(Start, End);
    return dis(gen);
}