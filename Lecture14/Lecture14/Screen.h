#pragma once

#include"Object.h"
#include<Windows.h>

#define WIDTH 200        // ������ �ʺ�
#define HEIGHT 100       // ������ ����
#define VIEW_WIDTH 50    // �þ� �ʺ�
#define VIEW_HEIGHT 25   // �þ� ����
#define INITIAL_LENGTH 5 // �� �ʱ� ����
#define MAX_LENGTH 100   // �� �ִ� ����



// �޴� ����
int menuSelect;
// ���̵�
int mode;
int speed;
// ���

// ������
char gameBoard[WIDTH][HEIGHT];
int gameState;
// ��
Snake snake;
// ���� ���� (������ ��ġ�� ����ϱ� ���� �迭)
Snake tail[MAX_LENGTH];
int tailLength;
/* ȭ���� �����ϴ� �ִ� �޸𸮸� 65,536*/
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
