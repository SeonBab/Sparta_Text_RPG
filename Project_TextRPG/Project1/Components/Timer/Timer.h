#pragma once
#include <functional>
#include <algorithm>
#include <vector>

class Timer
{

public:
    
    Timer(std::function<void()> InOnTriggered, std::function<void(int)> InOnExpired, float InTriggerTime, bool InbRepeat)
    {
        ID = GID++;
        OnTriggered = InOnTriggered;
        OnExpired = InOnExpired;
        TriggerTime = InTriggerTime;
        bIsRepeat = InbRepeat;
    }
    
private:
    
    static unsigned int GID;

    unsigned int ID;
    
    float AccTime = 0.f;
    float TriggerTime = 0.f;
    bool bIsRepeat = false;
    bool IsActive = true;

    void TikTok(float DeltaTime)
    {
        if(!IsActive)
        {
            return;
        }
        
        AccTime += DeltaTime;
        if(AccTime >= TriggerTime)
        {
            
            OnTrigger();

            if(bIsRepeat)
            {
                AccTime -= TriggerTime;
            }
            else
            {
                IsActive = false;
                if(OnExpired)
                {
                    OnExpired(ID);
                }
            }
        }
    };

    std::function<void()> OnTriggered;
    std::function<void(int)> OnExpired;
    
    void OnTrigger()
    {
        if(OnTriggered)
        {
            OnTriggered();
        }
    }

    friend class TimerManager;
};

 
class TimerManager
{

public:
    void AddTimer(std::function<void()> InOnTriggered, float InTriggerTime, bool InbRepeat)
    {
        Timers.emplace_back(Timer(InOnTriggered, bind(&TimerManager::OnTimerExpired, this, std::placeholders::_1), InTriggerTime, InbRepeat));
    }

    void Progress(float DeltaTime)
    {
        for(auto& Timer : Timers)
        {
            Timer.TikTok(DeltaTime);
        }
    }
    
    
private:

    void OnTimerExpired(int TimerID)
    {
        for(auto& Timer : Timers)
        {
            if(TimerID == Timer.ID)
            {
                std::swap(Timer, Timers.back());
                Timers.pop_back();
                return;
            }
        }
    }

    std::vector<Timer> Timers;
    
};