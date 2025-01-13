#pragma once
#include <stdexcept>

#include "LayoutManager.h"

class ConsoleBufferManager
{
private:
    ConsoleBufferManager() = default;
    ~ConsoleBufferManager()
    {
        CloseHandle(ScreenBuffer[0]);
        CloseHandle(ScreenBuffer[1]);
    }
    ConsoleBufferManager(ConsoleBufferManager& other) = delete;
    ConsoleBufferManager& operator =(const ConsoleBufferManager& other) = delete;
    static void Deleter(ConsoleBufferManager* ptr)
    {
        delete ptr;
    }
    static shared_ptr<ConsoleBufferManager> instance;

    static shared_ptr<ConsoleBufferManager>& GetInstance()
    {
        if (nullptr == instance)
        {
            instance = shared_ptr<ConsoleBufferManager>(new ConsoleBufferManager(), Deleter);
        }
        return instance;
    }

    friend class GameMain;

    void Init();

public:

    void Clear();
    void ChangeBuffer();

    Getter(COORD, BufferSize, BufferSize)

    HANDLE& GetFrontBuffer()
    {
        return ScreenBuffer[ActiveBufferIndex];
    }
    
    
    HANDLE& GetBackBuffer()
    {
        return ScreenBuffer[GetInactiveBufferIndex()];
    }

private:

    friend class ConsoleLayoutManager;
    
    HANDLE ScreenBuffer[2]; // 두 개의 화면 버퍼
    int ActiveBufferIndex; // 현재 활성화된 버퍼 인덱스

    int GetInactiveBufferIndex() const
    {
        return !ActiveBufferIndex; // 활성화되지 않은 버퍼의 인덱스를 반환
    }

    COORD BufferSize = {120, 30};
};
