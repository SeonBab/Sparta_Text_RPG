#pragma once
#include <windows.h>

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "define.h"

class ConsoleBufferManager;
using namespace std;



enum class ETextColorType
{
	BLACK = 0,
	GRAY = FOREGROUND_INTENSITY,
	RED = FOREGROUND_RED,
	RED_INENSITY = FOREGROUND_RED | FOREGROUND_INTENSITY,
	ORANGE = FOREGROUND_RED | FOREGROUND_GREEN,
	ORANGE_INENSITY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	GREEN = FOREGROUND_GREEN,
	GREEN_INENSITY = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	SKY = FOREGROUND_GREEN | FOREGROUND_BLUE,
	SKY_INENSITY = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	BLUE = FOREGROUND_BLUE,
	BLUE_INENSITY = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	PURPLE = FOREGROUND_BLUE | FOREGROUND_RED,
	PURPLE_INENSITY = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY,

	WHITE = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,

	END
};

enum class EBackgroundColorType
{
	BLACK = 0,
	GRAY = BACKGROUND_INTENSITY,
	RED = BACKGROUND_RED,
	RED_INENSITY = BACKGROUND_RED | BACKGROUND_INTENSITY,
	ORANGE = BACKGROUND_RED | BACKGROUND_GREEN,
	ORANGE_INENSITY = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	GREEN = BACKGROUND_GREEN,
	GREEN_INENSITY = BACKGROUND_GREEN | BACKGROUND_INTENSITY,
	SKY = BACKGROUND_GREEN | BACKGROUND_BLUE,
	SKY_INENSITY = BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	BLUE = BACKGROUND_BLUE,
	BLUE_INENSITY = BACKGROUND_BLUE | BACKGROUND_INTENSITY,
	PURPLE = BACKGROUND_BLUE | BACKGROUND_RED,
	PURPLE_INENSITY = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY,

	WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE,

	END
};

enum class ELayoutType
{
	TITLE,
	STAT,
	MAP,
	STORY,
	SELECT,
	LOG,

	END
};

enum EWriteOption
{
	EWriteOption_Clear = 1,
	EWriteOption_Overwrite = 2,
	EWriteOption_MoveUp = 4,
	EWriteOption_MoveDown = 8,
};

struct FStyleOption
{
	ETextColorType			TextColor = ETextColorType::WHITE;
	EBackgroundColorType	BackGroundColor = EBackgroundColorType::BLACK;
};

struct FDecorator
{
	string PreFix;
	char Fill;
	string PostFix;
};

struct FLayoutString
{
	string					Line;
	int						EWriteOption;
	FDecorator				Decorator;
	FStyleOption			StyleOptions;
};

struct FConsoleLayout
{
	vector<FLayoutString>	LayoutString;
	short					Left;
	short					Top;
	int						Width;
	int						Height;
	

	FConsoleLayout(short InLeft, short InTop, int InWidth, int InHeight)
		: Left(InLeft)
		, Top(InTop)
		, Width(InWidth)
		, Height(InHeight)
	{
		LayoutString.resize(InHeight);
	}

	short CalcCharLength(char ch);
	
	void Render();
};



struct FConsoleLayoutContainer
{
private:
	map<ELayoutType, FConsoleLayout> LayoutMap;

public:
	void Render();
	void AddLine(ELayoutType TargetType, const FLayoutString& InLayoutString, int LineIndex);
	void AddLayout(ELayoutType LayoutType, FConsoleLayout&& InLayout);
};






class WriteManager
{
private:
	GameMainSingleton(WriteManager)

	weak_ptr<ConsoleBufferManager> BufferManager;
	
	FConsoleLayoutContainer ConsoleLayoutContainer;

public:

	void AddLine(ELayoutType TargetLayout, const FLayoutString& InLayoutString, int LineIndex = 0);

	void Render();

	void Init();

	void CreateAllLayouts();

private:

	void CreateLayOut(ELayoutType LayoutType, short Left, short Top, int Width, int Height);
};