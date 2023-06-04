#pragma once

char ScreenBuffer[65536];
void setScreenSize(int width, int height);
void setCursorPos(int x, int y);
void SetColor(unsigned short backgroundColor, unsigned short TextColor);
void ClearBuffer();
int WriteBuffer(int x, int y, const char* str);