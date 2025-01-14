#include "LogManager.h"
#include <iostream>
#include <windows.h>
#include <mutex>
#include <fstream>

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

void LogManager::Append(const std::string& str, float delay)
{
	DeleteStatusLog();
	cout << str << endl;
	UpdateStatusLog();

	if (delay > .0f)
		Sleep(delay);
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
	if (draw == EDraw::Player)
		ReadBMP("Character.bmp");
}

void LogManager::DeleteStatusLog()
{
	// 콘솔 화면 버퍼 정보를 저장할 구조체
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	COORD preCursorPos = csbi.dwCursorPosition;
	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	string clearLine(width, ' ');

	MoveCursor(0, statusShowLine);
	cout << clearLine << endl;
	cout << clearLine << endl;
	MoveCursor(preCursorPos.X, preCursorPos.Y);
}

void LogManager::UpdateStatusLog()
{
	// 콘솔 화면 버퍼 정보를 저장할 구조체
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	COORD preCursorPos = csbi.dwCursorPosition;

	//Status가 출력될 줄
	statusShowLine = csbi.dwCursorPosition.Y + 3;

	MoveCursor(0, statusShowLine);
	cout << "------------------------" << endl;
	cout << "플레이어 정보";

	//원래 있던 커서 위치
	MoveCursor(preCursorPos.X, preCursorPos.Y);
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