#pragma once
#include <string>
#include <thread>

//현재 Framework에 Tick 함수가 실제로 매 프레임 작동하지 않음
//이는 기본적으로는 콘솔의 유저 입력을 기다리는 cin 때문에 벌어지는 현상
//만약 제대로 된 Tick으로 작동하게 하고 싶으면 유저 입력 등을 다른 쓰레드에서 받아야지만 제대로 작동한다
//고로 Status 갱신은 쓰레드를 쓰지 않는 이상 실제론 실시간 반응이 불가능하다.
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

	int statusShowLine = -1;
	std::thread statusThread;

public:
	static LogManager& Get();
	
	//갱신 쓰레드 실행
	void RunStatusThread();
	//정지
	void StopStatusThread();
	void Pause(); 
	void Clear();
	void Draw(EDraw draw);

private:
	//스테이터스 화면 갱신
	void ShowStatus();
	void EnableInput();
	void DisableInput();
	void MoveCursor(int x, int y);
	void ShowCursor(bool value);

	LogManager() = default;
};