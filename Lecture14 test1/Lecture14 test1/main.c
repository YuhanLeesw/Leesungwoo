#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "screen.h"
#include "Util.h"

int Initialize();
int Release();
void CheckError(int e);
int drawBuffer();

int GameState = 0;

int main()
{
	int isGameRunning = 1;

	CheckError(Initialize());

	unsigned long time_end = GetTickCount();
	unsigned long time = GetTickCount();

	while (isGameRunning)
	{
		drawBuffer();

		time = GetTickCount() - time_end;
		time_end = GetTickCount();

		if (time < 30)
		{

			Sleep(30 - time);
		}
		if (time != 0)
		{

			printf("time : %d \nfps : %d", time, 1000 / time);
		}

	}

	Release();

	return 0;
}

int Initialize()
{
	GameState = 0;

	setScreenSize(70, 20);
	SetColor(0b1000, 0b1111);

	ClearBuffer();
	WriteBuffer(25, 10, "게임 제목");
	WriteBuffer(25, 12, "1. 게임시작");
	WriteBuffer(25, 13, "2. 게임종료");

	 
	return 0;
}

int drawBuffer()
{
	setCursorPos(0, 0);
	printf("%s", ScreenBuffer);

	return 0;
}

int Release()
{
	printf("프로그래밍 패턴 / C 프로그래밍 기초\n");

	return 0;
}