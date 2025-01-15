#include "LogManager.h"
#include <iostream>
#include <windows.h>
#include <fstream>

#include "Player/Player.h"

using namespace std;


//==========================================================
// BMP struct
//==========================================================

// 구조체 패딩 방지
// 이거 안하면 BMP 헤더 사이즈 안맞아서 해줘야함
#pragma pack(push, 1) 
struct FBMPHeader
{
	USHORT fileType;    // 파일 타입 ("BM")
	UINT fileSize;      // 전체 파일 크기
	USHORT reserved1;   // 예약
	USHORT reserved2;   // 예약
	UINT offsetData;	// 픽셀 데이터의 시작 위치
};

struct FBMPInfoHeader
{
	UINT size;			//헤더 크기
	int width;          // 이미지의 가로 픽셀 수
	int height;         // 이미지의 세로 픽셀 수
	USHORT planes;      // 컬러 플레인 수 (항상 1)
	USHORT bitCount;    // 비트 수 (24비트 BMP는 24)
};
#pragma pack(pop)

struct FRgb
{
	BYTE red;
	BYTE green;
	BYTE blue;
};

//==========================================================
//Layout
//==========================================================


void Layout::Clear(bool ClearBuffer)
{
	if (ClearBuffer)
	{
		text.clear();
		outputTextVec.clear();
	}

	string clearLine(rect.width, ' ');
	for (int i = 0; i < rect.height; i++)
	{
		LogManager::Get().MoveCursor(rect.left, rect.up + i);
		cout << clearLine;
	}
}

void Layout::Output()
{
	SetOutputText();

	int start = max(0, (int)outputTextVec.size() - rect.height);
	for (int i = start; i < outputTextVec.size(); i++)
	{
		LogManager::Get().MoveCursor(rect.left, rect.up + i - start);
		cout << outputTextVec[i];
	}
}

void Layout::SetOutputText()
{
	//메모리 아끼게 수정
	outputTextVec.clear();
	if (outputTextVec.size() == 0)
		outputTextVec.push_back(string());

	int lineNumber = 0;
	int charNum = 0;

	for (int i = 0; i < text.size(); i++)
	{
		outputTextVec[lineNumber].push_back(text[i]);

		if (text[i] == '\n' || charNum >= rect.width - 1)
		{
			lineNumber++;
			charNum = 0;

			if (outputTextVec.size() <= lineNumber)
				outputTextVec.push_back(string());
		}
		else
			charNum++;
	}
}



//자체적으로 그림
void DrawLayout::Draw(EDraw Draw, int x, int y)
{
	//지움
	for (int i = 0; i < rect.height; i++)
	{
		LogManager::Get().MoveCursor(rect.left, rect.up + i);
		for (int j = 0; j < rect.width / 2; j++)
			cout << "■";
	}

	LogManager::Get().MoveCursor(rect.left + x, rect.up + y);

	switch (Draw)
	{
	case EDraw::Player:
		DrawBMP("Character.bmp");
		break;

	case EDraw::Shop:
		DrawBMP("Shop.bmp");
		break;

	case EDraw::Stage:
		DrawBMP("Stage.bmp");
		break; 

	case EDraw::Potion:
		DrawBMP("health_potion_pixel.bmp");
		break;

	case EDraw::AttackBoost:
		DrawBMP("attack_boost_pixel.bmp");
		break;

	default:
			break;
	}
}

void DrawLayout::DrawBMP(const std::string& Filename)
{
	//BMP 읽어오기

	ifstream file(Filename, ios::binary);
	if (!file)
	{
		LogManager::Get() << "파일을 열지 못했습니다.\n경로 : " << Filename << "\n";
		return;
	}

	FBMPHeader header;
	FBMPInfoHeader infoHeader;

	// 헤더 읽기
	file.read(reinterpret_cast<char*>(&header), sizeof(header));
	file.read(reinterpret_cast<char*>(&infoHeader), sizeof(infoHeader));

	if (header.fileType != 0x4D42)
	{
		LogManager::Get() << "BMP 파일이 아닙니다.\n";
		return;
	}

	int rowSize = (infoHeader.bitCount * infoHeader.width + 31) / 32 * 4;
	vector<UCHAR> row(rowSize);

	// 픽셀 데이터 출력 (단순화된 출력)
	file.seekg(header.offsetData, ios::beg);

	vector<FRgb> pixelVec(infoHeader.width * infoHeader.height);
	for (int y = infoHeader.height - 1; y >= 0; y--)
	{
		file.read(reinterpret_cast<char*>(row.data()), rowSize);
		for (int x = 0; x < infoHeader.width; ++x)
		{
			UCHAR blue = row[x * 3];
			UCHAR green = row[x * 3 + 1];
			UCHAR red = row[x * 3 + 2];

			//BMP는 그림이 아래부터 기록되있기 때문에 뒤집어 주기 위해서 배열에 넣어줌
			pixelVec[x + y * infoHeader.width] = { red, green, blue };
		}
	}

	//출력
	auto prePos = LogManager::Get().GetCursorPosition();

	for (int y = 0; y < infoHeader.height; y++)
	{
		for (int x = 0; x < infoHeader.width; x++)
		{
			LogManager::Get().MoveCursor(prePos.first + x * 2, prePos.second + y);

			auto& pixel = pixelVec[x + y * infoHeader.width];
			if (!(pixel.red == 255 && pixel.green == 255 && pixel.blue == 255))
				//색 입혀서 출력, 하얀색(=투명)은 무시
				cout << "\033[38;2;" << (int)pixel.red << ";" << (int)pixel.green << ";" << (int)pixel.blue << "m" << "■" << "\033[0m";
		}
	}

	file.close();
}



void PlayerStatLayout::Update()
{
	if (Player::GetInstance() == nullptr)
		return;

	string result;
	result += " Name  : " + Player::GetInstance()->GetName();
	result += "\n Level : " + to_string(Player::GetInstance()->GetLevel());
	result += "\n Damage: " + to_string(Player::GetInstance()->GetDamage());
	result += "\n Gold  : " + to_string(Player::GetInstance()->GetGold());

	int maxBar = 20;
	result += "\n HP    : ";
	for (int i = 0; i < maxBar; i++)
		if (i < (float)Player::GetInstance()->GetHP() / Player::GetInstance()->GetMaxHP() * maxBar)
			result += "■";
		else
			result += "□";

	result += "\n Exp   : ";
	for (int i = 0; i < maxBar; i++)
		if (i < (float)Player::GetInstance()->GetExp() / 100 * maxBar)
			result += "■";
		else
			result += "□";

	text = result;

	//출력 장소 비웠다가 다시 채우기
	Clear();
	Output();
}



void LogLayout::Append(const std::string& Str, float Delay)
{
	text += Str;

	Clear();
	Output();

	LogManager::Get().Delay(Delay);
}



//==========================================================
// LogManager
//==========================================================


LogManager& LogManager::Get()
{
	static LogManager instance;
	return instance;
}

void LogManager::Initialize()
{
	layouts = new Layout[3]
	{
		//그림
		DrawLayout({ 1, 1, 101, 39 }),
		//스텟
		PlayerStatLayout({ 105, 2, 50, 6 }),
		//로그
		LogLayout(Layout::FRect(105, 9, 50, 30)),
	};

	width = 158;
	height = 42;

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	DWORD dwMode = 0;
	GetConsoleMode(handle, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(handle, dwMode);

	// 버퍼 크기 설정
	COORD bufferSize;
	bufferSize.X = width;
	bufferSize.Y = height;
	SetConsoleScreenBufferSize(handle, bufferSize);

	//화면 사이즈 설정
	SMALL_RECT windowSize;
	windowSize.Left = 0;
	windowSize.Top = 0;
	windowSize.Right = width - 1;
	windowSize.Bottom = height - 1;
	SetConsoleWindowInfo(handle, TRUE, &windowSize);

	//외곽선 세팅
	{
		//외곽선
		outline = new string[height - 1];
		string spaceLine(width, ' ');
		for (int i = 0; i < height - 1; i++)
			outline[i] = spaceLine;

		//왼쪽 오른쪽
		for (int i = 0; i < height - 1; i++)
		{
			outline[i][0] = 'l';
			outline[i][width - 1] = 'l';
		}

		//위 아래
		string straightLine(width, '-');
		outline[0] = straightLine;
		outline[height - 2] = straightLine;

		//가로선
		for (int i = 0; i <= (int)ELayout::Log; i++)
			for (int x = 0; x <= layouts[i].rect.width; x++)
			{
				outline[layouts[i].rect.up - 1][layouts[i].rect.left + x] = '-';
				outline[layouts[i].rect.up + layouts[i].rect.height][layouts[i].rect.left + x] = '-';
			}

		//세로선
		for (int i = 0; i <= (int)ELayout::Log; i++)
			for (int y = 0; y < layouts[i].rect.height; y++)
			{
				outline[layouts[i].rect.up + y][layouts[i].rect.left - 1] = 'l';
				outline[layouts[i].rect.up + y][layouts[i].rect.left + layouts[i].rect.width + 1] = 'l';
			}
	}

}

void LogManager::DrawOutline()
{
	MoveCursor(0, 0);

	//맨 아랫줄 - 2까지만 그려지나 봄
	for (int i = 0; i < height - 1; i++)
		cout << outline[i] << endl;
}

void LogManager::Append(char Ch)
{
	Append(string(1, Ch));
}

void LogManager::Append(const string& Str, float Delay)
{
	static_cast<LogLayout*>(&layouts[2])->Append(Str, Delay);
	auto prePos = GetCursorPosition();

	static_cast<PlayerStatLayout*>(&layouts[1])->Update();
	MoveCursor(prePos.first, prePos.second);
}

void LogManager::Delay(float Delay)
{
	if (Delay > .0f)
		Sleep(Delay * 1000);
}

void LogManager::Draw(EDraw Draw, int x, int y)
{
	static_cast<DrawLayout*>(&layouts[0])->Draw(Draw, x, y);
}

void LogManager::Pause()
{
	Sleep(2000);
}

void LogManager::Clear()
{
	for (int i = 0; i < (int)ELayout::Log; i++)
		layouts[i].Clear(true);
}

pair<int, int> LogManager::GetCursorPosition()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	return { csbi.dwCursorPosition.X, csbi.dwCursorPosition.Y };
}

void LogManager::MoveCursor(int X, int Y)
{
	//커서이동함수
	COORD Cur;
	Cur.X = X;
	Cur.Y = Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

LogManager& LogManager::operator<<(const std::string& Message)
{
	Append(Message);
	return *this;
}

LogManager& LogManager::operator<<(char Value)
{
	Append(Value);
	return *this;
}

LogManager& LogManager::operator<<(int Value)
{
	*this << to_string(Value);
	return *this;
}

LogManager& LogManager::operator<<(float Value)
{
	*this << to_string(Value);
	return *this;
}

LogManager& LogManager::operator<<(size_t Value)
{
	*this << to_string(Value);
	return *this;
}

//void LogManager::DeleteStatusLog()
//{
//	// 콘솔 화면 버퍼 정보를 저장할 구조체
//	CONSOLE_SCREEN_BUFFER_INFO csbi;
//	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//
//	COORD preCursorPos = csbi.dwCursorPosition;
//	int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
//	string clearLine(width, ' ');
//
//	cout << clearLine << endl;
//	cout << clearLine << endl;
//	MoveCursor(preCursorPos.X, preCursorPos.Y);
//}
//
//void LogManager::UpdateStatusLog()
//{
//	// 콘솔 화면 버퍼 정보를 저장할 구조체
//	CONSOLE_SCREEN_BUFFER_INFO csbi;
//	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//
//
//	COORD preCursorPos = csbi.dwCursorPosition;
//
//	cout << "------------------------" << endl;
//	cout << "플레이어 정보";
//
//	//원래 있던 커서 위치
//	MoveCursor(preCursorPos.X, preCursorPos.Y);
//}