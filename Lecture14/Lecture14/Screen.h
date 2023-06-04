#pragma once

#include"Object.h"
#include<Windows.h>

#define WIDTH 200        // 게임판 너비
#define HEIGHT 100       // 게임판 높이
#define VIEW_WIDTH 50    // 시야 너비
#define VIEW_HEIGHT 25   // 시야 높이
#define INITIAL_LENGTH 5 // 뱀 초기 길이
#define MAX_LENGTH 100   // 뱀 최대 길이



// 메뉴 선택
int menuSelect;
// 난이도
int mode;
int speed;
// 모양

// 게임판
char gameBoard[WIDTH][HEIGHT];
int gameState;
// 뱀
Snake snake;
// 뱀의 꼬리 (꼬리의 위치를 기록하기 위한 배열)
Snake tail[MAX_LENGTH];
int tailLength;
/* 화면이 차지하는 최대 메모리를 65,536*/
char ScreenBuffer[65536];
void stringA();
void stringB();
void stringC();
void stringLecture();
void stringProgress();
void ReSet();
void Jumsu();
void stringJumsu();

void InputBuffer();
void setScreenSize(int width, int height);
void setCursorPos(int x, int y);
void SetColor(unsigned short backgroundColor, unsigned short textColor);
void ClearBuffer();
int WriteToBuffer(int x, int y, const char* str);
DWORD WINAPI updateFruitShapes(LPVOID arg);
void handleFruitCollision();
void handleWallCollision();
bool isWallInArray(int x, int y, struct Wall* walls, int numWalls);
bool isFruitInArray(int x, int y, struct Fruit* fruits, int numFruitss);
void generateFruits();
void generateWalls();
