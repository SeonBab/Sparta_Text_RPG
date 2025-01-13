#include "LogManager.h"
#include <iostream>
#include <windows.h>
#include <mutex>

using namespace std;

LogManager& LogManager::Get()
{
	static LogManager instance;
	return instance;
}

void LogManager::Pause()
{
	system("pause");
}

void LogManager::Clear()
{
	system("cls");
}

void LogManager::Draw(EDraw draw)
{

}

void LogManager::RunStatusThread()
{
	statusThread = thread(&LogManager::ShowStatus, this);
}

void LogManager::StopStatusThread()
{
	statusThread.join();
}


void LogManager::EnableInput() {
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = ENABLE_PROCESSED_INPUT | ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT;
	SetConsoleMode(hInput, mode);  // 기본 입력 모드로 복원
}

void LogManager::DisableInput() {
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hInput, 0);  // 모든 입력을 비활성화
}


void LogManager::ShowStatus()
{
	static mutex m;

	while (true)
	{
		lock_guard<mutex> lock(m);
		DisableInput();

		// 콘솔 화면 버퍼 정보를 저장할 구조체
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		COORD preCursorPos = csbi.dwCursorPosition;

		//콘솔창 아랫쪽에 Log를 남기는 방식.
		/*
		{
			//기존 위치에 있던 로그 삭제
			if (statusShowLine >= 0)
			{
				MoveCursor(0, statusShowLine);
				cout << "                     " << endl;
			}

			//기본적으로 스탯창이 위치할 목표 위치
			statusShowLine = csbi.srWindow.Bottom - 1;

			//화면 내에 로그가 원래 뜨는 위치보다 길어지면 밑에 추가
			if (statusShowLine <= csbi.dwCursorPosition.Y)
				statusShowLine = csbi.dwCursorPosition.Y + 3;

			MoveCursor(0, statusShowLine);
			cout << "  플레이어 정보" << endl;
		}
		*/

		//아래쪽에 추가로 Log를 붙여주는 방식
		{
			if (statusShowLine >= 0)
			{
				MoveCursor(0, statusShowLine);
				cout << "                     " << endl;
			}

			statusShowLine = csbi.dwCursorPosition.Y + 3;
			MoveCursor(0, statusShowLine);
			cout << "플레이어 정보";
		}

		//원래 있던 커서 위치
		MoveCursor(preCursorPos.X, preCursorPos.Y);
		EnableInput();

		Sleep(10);
	}
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