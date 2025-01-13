#pragma once
#include <chrono>
#include <memory>
#include "Managers/Stage/StageManager.h"
#include "Managers/Event/EventManager.h"
#include "Managers/Player/PlayerManager.h"
#include "Managers/Console/LayoutManager.h"
#include "Managers/Console/ConsoleBufferManager.h"
#include "Managers/Key/KeyManager.h"


using namespace std;

class GameMain
{
private:

	GameMain() = default;
	~GameMain() = default;

	static void Deleter(GameMain* ptr)
	{
		delete ptr;
	}
	
	GameMain(const GameMain& other) = delete;

	GameMain& operator = (const GameMain& other) = delete;

	static shared_ptr<GameMain> instance;

public:
	
	static void Exit();
	
	static shared_ptr<GameMain> GetInstance()
	{
		if (nullptr == instance)
		{
			instance = shared_ptr<GameMain>(new GameMain(), Deleter);
		}
		return instance;
	}

	template<typename T>
	static void DeleteManager()
	{
		T::GetInstance() = nullptr;
	}

	template<typename T>
	static shared_ptr<T> GetManager()
	{
		if (GameMain::instance == nullptr)
		{
			return nullptr;
		}

		return T::GetInstance();
	}

private:

	bool bIsGameEnded;

	chrono::time_point<chrono::steady_clock> CurTime;
	chrono::time_point<chrono::steady_clock> PrevTime;
	float DeltaTime;

	void TickTime();

public:
	
	void Init();

	void Tick();

	void Render();

	bool IsGameEnded()			
	{
		return bIsGameEnded;
	}
	
	void EndGame()				
	{
		bIsGameEnded = true;
	}
};

