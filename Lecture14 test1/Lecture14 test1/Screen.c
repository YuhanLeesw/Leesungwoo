#include "screen.h"
#include <Windows.h>

int screenWidth = 70;
int screenHeight = 20;

void setScreenSize(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

void setCursorPos(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void SetColor(unsigned short backgroundColor, unsigned short TextColor)
{
	unsigned short color = TextColor;
	color = color + (backgroundColor << 4);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ClearBuffer()
{
	int y = 0;
	while (y < screenHeight + 2)
	{
		int x = 0;
		while (x < screenWidth + 2)
		{
			if (y == 0 || y == screenHeight + 1)
				ScreenBuffer[x + (y * (screenWidth + 3))] = '-';
			else
			{
				if (x == 0 || x == screenWidth + 1)
					ScreenBuffer[x + (y * (screenWidth + 3))] = 'I';
				else ScreenBuffer[x + (y * (screenWidth + 3))] = ' ';
			}
			x++;
		}
		ScreenBuffer[x + (y * (screenWidth + 3))] = '\n';
		y++;
	}
	ScreenBuffer[y * (screenWidth + 3)] = '\0';
}

int WriteBuffer(int x, int y, const char* str)
{
	int i = 0;
	while (i < strlen(str))
	{
		ScreenBuffer[x + (y * (screenWidth + 3)) + i] = str[i];
		i++;
	}

	return 0;
}