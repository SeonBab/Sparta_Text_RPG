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

	std::vector<std::pair<std::string, int>> logVec;

public:
	static LogManager& Get() { return instance; }

	void ShowStatus();
	void ShowLog(); 
	void Append(const std::string& str, int delay = 0);
	void Draw(EDraw draw);

private:
	void MoveCursor(int x, int y);
	void ShowCursor(bool value);

	LogManager() = default;
};