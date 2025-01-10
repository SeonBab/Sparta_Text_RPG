#include "LogManager.h"
#include <iostream>
#include <windows.h>

using namespace std;

LogManager LogManager::instance;

void LogManager::ShowStatus()
{
	// �ܼ� ȭ�� ���� ������ ������ ����ü
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	MoveCursor(0, csbi.srWindow.Top + 20);
	cout << "�÷��̾� ����" << endl;

	//���� �ִ� Ŀ�� ��ġ
	MoveCursor(csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y);
}

void LogManager::ShowLog()
{
	for (pair<string, int> log : logVec)
	{
		cout << log.first << endl;
		if (log.second > 0) Sleep(log.second);
	}

	//system("pause");
	cin.ignore();
	cin.ignore();
}

void LogManager::Append(const string& str, int delay)
{
	logVec.push_back({ str, delay });
}

void LogManager::Draw(EDraw draw)
{

}

void LogManager::Clear()
{
	logVec.clear();
}


void LogManager::MoveCursor(int x, int y)
{
	//Ŀ���̵��Լ�
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