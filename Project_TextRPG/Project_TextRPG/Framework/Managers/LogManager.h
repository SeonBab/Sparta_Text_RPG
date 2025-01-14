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

	int statusShowLine = -1;		//���ŵ� ������ �ѹ�

public:
	static LogManager& Get();
	
	void Append(const std::string& str, float delay = .0f);
	void Pause(); 
	void Clear();
	void Draw(EDraw draw);

private:
	void DeleteStatusLog();
	//�������ͽ� ȭ�� ����
	void UpdateStatusLog();
	void MoveCursor(int x, int y);
	void ShowCursor(bool value);
	void ReadBMP(const std::string& filename);

	LogManager() = default;
};