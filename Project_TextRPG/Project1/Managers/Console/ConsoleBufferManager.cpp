#include "ConsoleBufferManager.h"

#include <iostream>

shared_ptr<ConsoleBufferManager> ConsoleBufferManager::instance = nullptr;

void ConsoleBufferManager::Init()
{
    ScreenBuffer[0]  = CreateConsoleScreenBuffer(
       GENERIC_WRITE, // 읽기/쓰기 권한
       0,                            
       NULL,                         
       CONSOLE_TEXTMODE_BUFFER,                            
       NULL                          
   );
    
    ScreenBuffer[1]  = CreateConsoleScreenBuffer(
        GENERIC_WRITE, // 읽기/쓰기 권한
        0,                            
        NULL,                         
        CONSOLE_TEXTMODE_BUFFER,                            
        NULL                          
    );
    
    // 초기 활성 버퍼 설정
    SetConsoleActiveScreenBuffer(ScreenBuffer[0]);
    ActiveBufferIndex = 0;
    
    
    SetConsoleScreenBufferSize(ScreenBuffer[0], BufferSize);
    SetConsoleScreenBufferSize(ScreenBuffer[1], BufferSize);


    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(ScreenBuffer[0], &cci);
    SetConsoleCursorInfo(ScreenBuffer[1], &cci);

    
}

void ConsoleBufferManager::Clear()
{
    // system("cls");
    DWORD charsWritten;
    FillConsoleOutputCharacter(ScreenBuffer[GetInactiveBufferIndex()], ' ', BufferSize.X * BufferSize.Y , {0, 0},
                               &charsWritten);
    
}

void ConsoleBufferManager::ChangeBuffer()
{
    SetConsoleActiveScreenBuffer(ScreenBuffer[GetInactiveBufferIndex()]);
    ActiveBufferIndex = GetInactiveBufferIndex();
    Clear();
}


