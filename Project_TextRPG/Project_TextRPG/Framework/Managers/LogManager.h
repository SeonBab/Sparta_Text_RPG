#pragma once
#include <string>
#include <vector>


enum class EDraw
{
	Player,
	Shop,
	Fight,
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
	struct Rect
	{
		int left, up;
		int width, height;

	public:
		Rect(int left, int up, int width, int height) 
			: left(left), up(up), width(width), height(height) {}
	};

public:
	Rect rect;
	std::string text;
	std::vector<std::string> outputTextVec;

public:
	Layout(Rect rect) : rect(rect) {}

	void Clear(bool clearBuffer = false);

protected:
	void Output();

private:
	void SetOutputText();
};


class DrawLayout : public Layout
{
public:
	DrawLayout(Layout::Rect rect) : Layout(rect) {};
	void Draw(EDraw draw);

private:
	void DrawBMP(const std::string& filename);
};


class PlayerStatLayout : public Layout
{
public:
	PlayerStatLayout(Layout::Rect rect) : Layout(rect) {};
	void Update();
};


class LogLayout : public Layout
{
public:
	LogLayout(Layout::Rect rect) : Layout(rect) {}
	void Append(const std::string& str, float delay = .0f);
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
	void Append(char ch);
	void Append(const std::string& str, float delay = .0f);
	void Draw(EDraw draw);
	void Pause();
	//전체 레이아웃의 buffer까지 전부 삭제함
	void Clear();

	std::pair<int, int> GetCursorPosition();
	void MoveCursor(int x, int y);

	Layout& GetLayout(ELayout layout) { return layouts[(int)layout]; }

	LogManager& operator<<(const std::string& message);
	LogManager& operator<<(char value);
	LogManager& operator<<(int value);
	LogManager& operator<<(float value);
	LogManager& operator<<(size_t value);

private:
	LogManager() = default;
};