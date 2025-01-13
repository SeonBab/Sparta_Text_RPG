#include "LogManager.h"
#include <iostream>
#include <windows.h>
#include <mutex>
#include <fstream>
#include <vector>

using namespace std;

// 구조체 패딩 방지
// 이거 안하면 BMP 헤더 사이즈 안맞아서 해줘야함
#pragma pack(push, 1) 
struct BMPHeader
{
	USHORT fileType;    // 파일 타입 ("BM")
	UINT fileSize;      // 전체 파일 크기
	USHORT reserved1;   // 예약
	USHORT reserved2;   // 예약
	UINT offsetData;	// 픽셀 데이터의 시작 위치
};

struct BMPInfoHeader
{
	UINT size;			//헤더 크기
	int width;          // 이미지의 가로 픽셀 수
	int height;         // 이미지의 세로 픽셀 수
	USHORT planes;      // 컬러 플레인 수 (항상 1)
	USHORT bitCount;    // 비트 수 (24비트 BMP는 24)
};
#pragma pack(pop)


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
	CONSOLE_FONT_INFOEX cfi;
	auto handle = GetStdHandle(STD_OUTPUT_HANDLE);

	cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	GetCurrentConsoleFontEx(handle, FALSE, &cfi);

	COORD preFontSize = cfi.dwFontSize;

	cfi.dwFontSize.X *= 0.7f;
	cfi.dwFontSize.Y *= 0.7f;

	//폰트 사이즈 조정
	SetCurrentConsoleFontEx(handle, FALSE, &cfi);

	//그림
	{
		if (draw == EDraw::Player)
			ReadBMP("Character");
	}

	//이전 크기로 되돌림
	cfi.dwFontSize = preFontSize;
	SetCurrentConsoleFontEx(handle, FALSE, &cfi);
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

	// 콘솔 화면 버퍼 정보를 저장할 구조체
	CONSOLE_SCREEN_BUFFER_INFO preCsbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &preCsbi);

	int width = preCsbi.srWindow.Right - preCsbi.srWindow.Left + 1;
	string clearLine(width, ' ');

	while (true)
	{
		lock_guard<mutex> lock(m);

		// 콘솔 화면 버퍼 정보를 저장할 구조체
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

		if (csbi.srWindow.Bottom < statusShowLine)
		{
			Sleep(10);
			continue;
		}

		DisableInput();
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
			MoveCursor(0, statusShowLine);
			for (int i = 0; i < 2; i++)
				cout << clearLine << endl;

			statusShowLine = csbi.dwCursorPosition.Y + 3;
			MoveCursor(0, statusShowLine);
			cout << "------------------------" << endl;
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

void LogManager::ReadBMP(const std::string& filename)
{
	ifstream file(filename, ios::binary);
	if (!file)
	{
		cerr << "Failed to open file: " << filename << endl;
		return;
	}

	BMPHeader header;
	BMPInfoHeader infoHeader;

	// 헤더 읽기
	file.read(reinterpret_cast<char*>(&header), sizeof(header));
	file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

	if (header.fileType != 0x4D42)
	{
		std::cerr << "Not a BMP file." << std::endl;
		return;
	}

	int rowSize = (infoHeader.bitCount * infoHeader.width + 31) / 32 * 4;
	vector<UCHAR> row(rowSize);

	// 픽셀 데이터 출력 (단순화된 출력)
	file.seekg(header.offsetData, ios::beg);
	cout << infoHeader.width << " " << infoHeader.height << endl;

	bool** dot = new bool* [infoHeader.height];
	for (int y = infoHeader.height - 1; y >= 0; y--)
	{
		dot[y] = new bool[infoHeader.width];

		file.read(reinterpret_cast<char*>(row.data()), rowSize);
		for (int x = 0; x < infoHeader.width; ++x)
		{
			UCHAR blue = row[x * 3];
			//UCHAR green = row[x * 3 + 1];
			//UCHAR red = row[x * 3 + 2];

			//BMP는 그림이 아래부터 기록되있기 때문에 뒤집어 주기 위해서 배열에 넣어줌
			dot[y][x] = blue != 255;
		}
	}

	for (int y = 0; y < infoHeader.height; y++)
	{
		for (int x = 0; x < infoHeader.width; x++)
			if (dot[y][x])
				cout << "■";
			else
				cout << "□";

		cout << endl;
	}

	file.close();

}