#include "windows.h"
#include <chrono>
#include <iostream>
#include "Game.h"

using namespace std;

int main() 
{

	{
		shared_ptr<GameMain> Game = GameMain::GetInstance();
	
		Game->Init();
	
		while (!Game->IsGameEnded())
		{
			Game->Tick();
			Game->Render();
		}
	
		Game->Exit();
	}

	Sleep(4000);
	
	return 0;
}