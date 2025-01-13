#include "Game.h"



shared_ptr<GameMain> GameMain::instance = nullptr;

void GameMain::Exit()
{
	DeleteManager<EventManager>();
	DeleteManager<StageManager>();
	DeleteManager<PlayerManager>();
	DeleteManager<WriteManager>();
	DeleteManager<KeyManager>();
	DeleteManager<ConsoleBufferManager>();
	instance = nullptr;
}

void GameMain::TickTime()
{
	CurTime = chrono::high_resolution_clock::now();
	DeltaTime = chrono::duration<float>(CurTime - PrevTime).count();
	PrevTime = CurTime;
}

void GameMain::Init()
{
	CurTime = chrono::high_resolution_clock::now();
	PrevTime = CurTime;
	GetManager<PlayerManager>()->Init();
	GetManager<StageManager>()->Init();
	GetManager<EventManager>()->Init();
	GetManager<ConsoleBufferManager>()->Init();
	GetManager<WriteManager>()->Init();
}

void GameMain::Tick()
{
	TickTime();
	GetManager<StageManager>()->Tick(DeltaTime);
	GetManager<EventManager>()->Tick();
}

void GameMain::Render()
{	
	GetManager<WriteManager>()->Render();
	GetManager<ConsoleBufferManager>()->ChangeBuffer();
}