#include "Framework.h"
#include <iostream>
#include <random>
#include "Framework/Managers/LogManager.h"
#include "Monster/Monster.h"
#include "Framework/Managers/ShopManager.h"
#include "Framework/Managers/BattleManager.h"

#include "Player/Player.h"

void MainGame::Init()
{
	srand((unsigned int)time(NULL));

	LogManager::Get().Initialize();
	LogManager::Get().DrawOutline();

	Player::GetInstance()->SetPlayerName();
}

void MainGame::Select()
{
	while (true)
	{
		cin >> PlayerChoice;
		// Idx 1부터 시작 + Shop뒤에 붙음.
		if (1 <= PlayerChoice && PlayerChoice < Monsters.size() + 2)
		{
			if (Monsters.size() + 1 == PlayerChoice)
			{
				bBlockRegenerateMonster = true;
				ShopManager::PrintShopMenu();
			}
			break;
		}
		else
		{
			LogManager::Get() << "Not Valid" << "\n";
		}
	}
}


void MainGame::Tick()
{
	// Console Clear
	LogManager::Get().Clear();
	LogManager::Get().DrawOutline();

	LogManager::Get().Draw(EDraw::Stage);

	// 10레벨 달성시 보스 몬스터와 강제 전투이므로 DisplayChoices() 함수 앞에 와야함
	if (MaxPlayerLevel == Player::GetInstance()->GetLevel())
	{
		FMonsterInfo BossMonsterInfo = Monster::CreateMonsterInfo(Player::GetInstance()->GetLevel(), 4);

		unique_ptr<Monster> BossMonster = make_unique<Monster>(BossMonsterInfo.MonsterName, BossMonsterInfo.MonsterHP, BossMonsterInfo.MonsterDamage, 4);
		// 보스 몬스터에게 이기거나 플레이어가 죽은 경우 이후 게임 로직을 더이상 처리하지 않고 게임을 종료
		if (BattleManager::Get().Battle(BossMonster.get(), Player::GetInstance()))
		{
			LogManager::Get() << "축하합니다! 보스를 처치하고 게임 엔딩을 보셨습니다!" << "\n";
			
			//EndType = EEndType::Win;
			//OnGameEnded();
		}
		else
		{
			LogManager::Get() << "아쉽게도 보스한테 패배하셨습니다." << "\n";

			//EndType = EEndType::Lose;
			//OnGameEnded();
		}

		// 밑에 로직 실행하지 않고 프로그램 강제 종료
		exit(0);
	}

    if (!bBlockRegenerateMonster) // 꼼수 방지. 상점 갔다 나온다고 몬스터가 다시 생성되면 안됨
    {
        CreateMonster();
        bBlockRegenerateMonster = false;
    }
    DisplayChoices();
    Select();
    
    // 상점을 선택한 경우를 제외
    if (Monsters.size() >= PlayerChoice)
    {
        if (!BattleManager::Get().Battle(Monsters[PlayerChoice - 1].get(), Player::GetInstance()))
        {
            EndType = EEndType::Lose;
            OnGameEnded();
        }
        else // 정상 전투
        {
            bBlockRegenerateMonster = false;
        }
    }

	LogManager::Get().Pause();

	// system.pause(), delay()
	// Item 사용 - 알아서 하자.
	// 보상 - Item, Gold, Exp
	// 분기 1-1. Level 10 : 선택지를 바꿈.

	// ShopManager->DoSomething
	// 분기 2. Shop()
	// 선택지
	// while(bExit)

	// Status 출력
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

	// 2~5마리의 몬스터 배열 생성
	const int RandMonstersArrSize = RandRange(MinMonsterNum, MaxMonsterNum);
	Monsters.resize(RandMonstersArrSize);

	for (int i = 0; i < Monsters.size(); ++i)
	{
		// 슬라임 고블린 오크중 무작위 생성
		const int RandMonsterType = RandRange(1, MaxMonsterTypeRange);

		// 몬스터 정보 계산
		FMonsterInfo MonsterInfo = Monster::CreateMonsterInfo(Player::GetInstance()->GetLevel(), RandMonsterType);

		Monsters[i] = make_unique<Monster>(MonsterInfo.MonsterName, MonsterInfo.MonsterHP, MonsterInfo.MonsterDamage, RandMonsterType);
	}
}

// 현재 일반 몬스터에게 죽었을때만 실행됨
void MainGame::OnGameEnded()
{
    if(EndType == EEndType::Lose)
    {
		LogManager::Get() << "You Lose..." << "\n";
    }
    else if(EndType == EEndType::Win)
    {
		LogManager::Get() << "You Win!!!" << "\n";
    }

	// 승패에 관계없이 무조건 게임 종료
	bIsGameEnded = true;
}

void MainGame::DisplayChoices()
{
	LogManager::Get().GetLayout(ELayout::Log).Clear(true);
	LogManager::Get() << "눈 앞에 " << Monsters.size() << "개의 갈림길이 있습니다.\n각 갈림길마다 적 몬스터의 기운이 느껴집니다. \n";

	for (int i = 0; i < Monsters.size(); ++i)
	{
		LogManager::Get() << i + 1 << "번째 길: " << Monsters[i].get()->GetName() << '(';
		for (int j = 0; j < Monsters[i].get()->GetDifficulty(); ++j) // 몬스터 난이도에 따라 별 출력
		{
			LogManager::Get() << '*';
		}
		LogManager::Get() << ")\n";
	}

	LogManager::Get() << Monsters.size() + 1 << ". Shop\n";
}

int MainGame::RandRange(int Start, int End)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(Start, End);
	return dis(gen);
}