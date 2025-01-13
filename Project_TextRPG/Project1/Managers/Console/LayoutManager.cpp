#include "LayoutManager.h"

#include <cassert>
#include <iostream>

#include "ConsoleBufferManager.h"
#include "Game.h"

using namespace std;

shared_ptr<WriteManager> WriteManager::instance = nullptr;

void WriteManager::AddLine(ELayoutType TargetLayout, const FLayoutString& InLayoutString, int LineIndex)
{
    ConsoleLayoutContainer.AddLine(TargetLayout, InLayoutString, LineIndex);
}

void WriteManager::Render()
{
    ConsoleLayoutContainer.Render();
}

void WriteManager::Init()
{
    CreateAllLayouts();
}

void WriteManager::CreateAllLayouts()
{
    CreateLayOut(ELayoutType::TITLE, 0, 0, 120, 2);
    AddLine(ELayoutType::TITLE,
        FLayoutString(
            "스파르타의 모험",
            EWriteOption_Clear,
            FDecorator{"[",'=',"]"},
            FStyleOption(ETextColorType::WHITE, EBackgroundColorType::GRAY)));
    CreateLayOut(ELayoutType::LOG, 0, 2, 120, 4);
    
        
    CreateLayOut(ELayoutType::STORY, 30, 2, 80, 4);
    
    CreateLayOut(ELayoutType::SELECT, 0, 15, 30, 5);
    AddLine(ELayoutType::SELECT,
        FLayoutString(
            "Selection3",
            EWriteOption_Clear,
            FDecorator{"[",'=',"]"},
            FStyleOption(ETextColorType::RED_INENSITY, EBackgroundColorType::GRAY)));
    AddLine(ELayoutType::SELECT,
        FLayoutString(
            "Selection2",
            EWriteOption_MoveDown,
            FDecorator{"[",'=',"]"},
            FStyleOption(ETextColorType::RED_INENSITY, EBackgroundColorType::GRAY)));
    AddLine(ELayoutType::SELECT,
        FLayoutString(
            "Selection1",
            EWriteOption_MoveDown,
            FDecorator{"[",'=',"]"},
            FStyleOption(ETextColorType::RED_INENSITY, EBackgroundColorType::GRAY)));
    
    
}

void WriteManager::CreateLayOut(ELayoutType LayoutType, short Left, short Top, int Width, int Height)
{
    ConsoleLayoutContainer.AddLayout(LayoutType, FConsoleLayout(Left, Top, Width, Height));
}

short FConsoleLayout::CalcCharLength(char ch)
{
    return ch & 0x80 ? 2 : 1;
}

void FConsoleLayout::Render()
{
    HANDLE& BackBuffer = GameMain::GetManager<ConsoleBufferManager>()->GetBackBuffer();
    const COORD& BufferSize = GameMain::GetManager<ConsoleBufferManager>()->GetBufferSize();

    int Idx = 0;

    
    for (const auto& [Line, WriteOption, Decorator, Style] : LayoutString)
    {
        short CurTop = Top + Idx;
        short ExpectedWidth = 0;
        for(auto ch : Line)
        {
            ExpectedWidth += CalcCharLength(ch);   
        }

        for(auto ch : Decorator.PreFix)
        {
            ExpectedWidth += CalcCharLength(ch);   
        }

        for(auto ch : Decorator.PostFix)
        {
            ExpectedWidth += CalcCharLength(ch);   
        }
                
        if(CurTop >= BufferSize.Y || ExpectedWidth >= Width || Left + ExpectedWidth >= BufferSize.X)
        {
            assert(!"CheckLayout");
            return;
        }
        
        SetConsoleCursorPosition(BackBuffer, COORD{Left, CurTop});
        SetConsoleTextAttribute(BackBuffer, (WORD)Style.TextColor | (WORD)Style.BackGroundColor);
        
        DWORD charsWritten;

        if(!Decorator.PreFix.empty())
        {
            WriteFile(BackBuffer, Decorator.PreFix.c_str(), Decorator.PreFix.size(), &charsWritten, NULL);
            
        }

        string Fill;
        if(Decorator.Fill != '\0')
        {
            for(int i = 1; i <= (Width - ExpectedWidth) / 2; i++)
            {
                Fill += Decorator.Fill;
            }
            if(!Fill.empty())
            {
                WriteFile(BackBuffer, Fill.c_str(), Fill.size(), &charsWritten, NULL);
            }    
        }

        // 특수문자 -> 3BYTE + 문자 끝
        // const char some[4] ="★";
        // string c = "★ ";
        // WriteFile(BackBuffer, c.c_str(), c.size(), &charsWritten, NULL);
        
        WriteFile(BackBuffer, Line.c_str(), Line.size(), &charsWritten, NULL);
        
        if(Decorator.Fill != '\0')
        {
            if((Width - ExpectedWidth) % 2)
            {
                Fill += Decorator.Fill;
            }
            
            if(!Fill.empty())
            {
                WriteFile(BackBuffer, Fill.c_str(), Fill.size(), &charsWritten, NULL);
            }    
        }
        
        if(!Decorator.PostFix.empty())
        {
            WriteFile(BackBuffer, Decorator.PostFix.c_str(), Decorator.PostFix.size(), &charsWritten, NULL);
        }
        
        
        Idx++;
    }
}

void FConsoleLayoutContainer::Render()
{
    for (auto it = LayoutMap.begin(); it != LayoutMap.end(); ++it)
    {
        FConsoleLayout& Layout = it->second;
        Layout.Render();
    }
}

void FConsoleLayoutContainer::AddLine(ELayoutType TargetType, const FLayoutString& InLayoutString, int LineIndex)
{
    FConsoleLayout& ConsoleLayout = LayoutMap.find(TargetType)->second;
    ConsoleLayout.LayoutString[LineIndex].EWriteOption = InLayoutString.EWriteOption;
    FLayoutString& LayoutString = ConsoleLayout.LayoutString[LineIndex];
    
    if (InLayoutString.EWriteOption & EWriteOption_Clear)
    {
        LayoutString = InLayoutString;
    }
    else if (InLayoutString.EWriteOption & EWriteOption_Overwrite)
    {
        LayoutString.Line.assign(InLayoutString.Line + LayoutString.Line.substr(InLayoutString.Line.size()));
    }

    if (InLayoutString.EWriteOption & EWriteOption_MoveUp)
    {
        for (int i = 0; i < LineIndex; ++i)
        {
            swap(ConsoleLayout.LayoutString[i], ConsoleLayout.LayoutString[i + 1]);
        }
        ConsoleLayout.LayoutString[LineIndex] = InLayoutString;
    }
    else if (InLayoutString.EWriteOption & EWriteOption_MoveDown)
    {
        for (int i = ConsoleLayout.Height - 1; i > LineIndex; --i)
        {
            swap(ConsoleLayout.LayoutString[i], ConsoleLayout.LayoutString[i - 1]);
        }
        ConsoleLayout.LayoutString[LineIndex] = InLayoutString;
    }
}

void FConsoleLayoutContainer::AddLayout(ELayoutType LayoutType, FConsoleLayout&& InLayout)
{
    LayoutMap.insert({LayoutType, InLayout});
}