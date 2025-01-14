#include "Framework/Framework.h"

int main()
{
    MainGame& Game = MainGame::Get(); 
    Game.Init();

    while (!Game.IsGameEnded())
    {
        Game.Tick();
    }
    
    return 0;
}
