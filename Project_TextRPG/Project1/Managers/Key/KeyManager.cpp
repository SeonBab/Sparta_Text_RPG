#include "KeyManager.h"

#include <conio.h>

shared_ptr<KeyManager> KeyManager::instance = nullptr;

bool KeyManager::IsKeyPressed(char Key)
{
    if( _kbhit())
    {
        if (_getch() == Key)
        {
            return true;
        }
    }

    return false;
}
