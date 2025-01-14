#pragma once
#include <string>
#include <vector>

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

	int statusShowLine = -1;		//갱신될 라인의 넘버

public:
	static LogManager& Get();
	
	void Append(const std::string& str, float delay = .0f);
	void Pause(); 
	void Clear();
	void Draw(EDraw draw);

private:
	void DeleteStatusLog();
	//스테이터스 화면 갱신
	void UpdateStatusLog();
	void MoveCursor(int x, int y);
	void ShowCursor(bool value);
	void ReadBMP(const std::string& filename);

	LogManager() = default;
};