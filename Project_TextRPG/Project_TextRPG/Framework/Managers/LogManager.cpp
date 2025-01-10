#include "LogManager.h"
#include <iostream>
#include <windows.h>

using namespace std;

LogManager LogManager::instance;

void LogManager::ShowStatus()
{
	// 콘솔 화면 버퍼 정보를 저장할 구조체
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	MoveCursor(0, csbi.srWindow.Top + 20);
	cout << "플레이어 정보" << endl;

	//원래 있던 커서 위치
	MoveCursor(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
}

void LogManager::Pause()
{
	system("pause");
}

void LogManager::Append(const string& str, float delaySecond)
{
	cout << str << endl;
	ShowStatus();

	if (delaySecond > 0)
		Sleep(delaySecond * 1000);
}

void LogManager::Draw(EDraw draw)
{

}

void LogManager::MoveCursor(int x, int y)
{
	//커서이동함수
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void LogManager::ShowCursor(bool value)
{
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO ConsoleCursor;

	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ConsoleCursor.bVisible = value;
	ConsoleCursor.dwSize = 1;

	SetConsoleCursorInfo(hConsole, &ConsoleCursor);
}