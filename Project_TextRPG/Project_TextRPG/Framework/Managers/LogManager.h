#pragma once
#include <string>
#include <vector>


enum class EDraw
{
	Player,
	Shop,
	Stage,
	Potion,
	AttackBoost
};

enum class ELayout
{
	Draw,
	PlayerStat,
	Log
};


//============================================================================
// Layout
//============================================================================

class Layout
{
public:
	struct FRect
	{
		int left, up;
		int width, height;

	public:
		FRect(int Left, int Up, int Width, int Height) 
			: left(Left), up(Up), width(Width), height(Height) {}
	};

public:
	FRect rect;
	std::string text;
	std::vector<std::string> outputTextVec;

public:
	Layout(FRect Rect) : rect(Rect) {}

	void Clear(bool ClearBuffer = false);

protected:
	void Output();

private:
	void SetOutputText();
};


class DrawLayout : public Layout
{
public:
	DrawLayout(Layout::FRect Rect) : Layout(Rect) {};
	void Draw(EDraw Draw, int x = 0, int y = 0);

private:
	void DrawBMP(const std::string& Filename);
};


class PlayerStatLayout : public Layout
{
public:
	PlayerStatLayout(Layout::FRect Rect) : Layout(Rect) {};
	void Update();
};


class LogLayout : public Layout
{
public:
	LogLayout(Layout::FRect Rect) : Layout(Rect) {}
	void Append(const std::string& Str, float Delay = .0f);
};

//============================================================================
// LogManager
//============================================================================


class LogManager
{
private:
	Layout* layouts;
	int width, height;
	std::string* outline;

public:
	static LogManager& Get();

	void Initialize();
	void DrawOutline();
	void Append(char Ch);
	void Append(const std::string& Str, float Delay = .0f);
	void Delay(float Delay);
	void Draw(EDraw Draw, int x = 0, int y = 0);
	void Pause();
	//전체 레이아웃의 buffer까지 전부 삭제함
	void Clear();

	std::pair<int, int> GetCursorPosition();
	void MoveCursor(int X, int Y);

	Layout& GetLayout(ELayout Layout) { return layouts[(int)Layout]; }

	LogManager& operator<<(const std::string& Message);
	LogManager& operator<<(char Value);
	LogManager& operator<<(int Value);
	LogManager& operator<<(float Value);
	LogManager& operator<<(size_t Value);

private:
	LogManager() = default;
};