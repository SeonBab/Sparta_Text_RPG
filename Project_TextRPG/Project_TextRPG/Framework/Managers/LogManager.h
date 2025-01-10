#pragma once
#include <string>
#include <vector>
#include <utility>

class LogManager
{
public:
	enum EDraw
	{
		Player,
		Shop,
		Fight,
	};

private:
	static LogManager instance;

public:
	static LogManager& Get() { return instance; }

	void ShowStatus();
	void Pause(); 
	void Append(const std::string& str, float delay = .0f);
	void Draw(EDraw draw);

private:
	void MoveCursor(int x, int y);
	void ShowCursor(bool value);

	LogManager() = default;
};