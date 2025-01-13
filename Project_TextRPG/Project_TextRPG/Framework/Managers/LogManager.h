#pragma once
#include <string>
#include <thread>

//���� Framework�� Tick �Լ��� ������ �� ������ �۵����� ����
//�̴� �⺻�����δ� �ܼ��� ���� �Է��� ��ٸ��� cin ������ �������� ����
//���� ����� �� Tick���� �۵��ϰ� �ϰ� ������ ���� �Է� ���� �ٸ� �����忡�� �޾ƾ����� ����� �۵��Ѵ�
//��� Status ������ �����带 ���� �ʴ� �̻� ������ �ǽð� ������ �Ұ����ϴ�.
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
	
	//���� ������ ����
	void RunStatusThread();
	//����
	void StopStatusThread();
	void Pause(); 
	void Clear();
	void Draw(EDraw draw);

private:
	//�������ͽ� ȭ�� ����
	void ShowStatus();
	void EnableInput();
	void DisableInput();
	void MoveCursor(int x, int y);
	void ShowCursor(bool value);

	LogManager() = default;
};