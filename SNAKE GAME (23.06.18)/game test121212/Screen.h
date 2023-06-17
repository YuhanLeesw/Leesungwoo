#pragma once
#include <windows.h>
#include "Object.h"

#define UP 72   
#define DOWN 80
#define LEFT 75
#define RIGHT 77

inline void SetColor(int color)     // ���� ���� ������ ���� �Լ�.
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

extern int stage;  // ���� �������� �ܰ�
extern int lev;    // ���� ���̵�(easy, normal, hard)
int speed;    // ���� �ӵ�
int tail;     // ��������
int food;   // ���� ��
int add;    // ���� ������
int food_x;   // ���̰� ��µ� x��ǥ
int food_y;   // ���̰� ��µ� y��ǥ
char ran_food; // ǥ�õ� ����(1~5) 
int mov;  // �� �������� ���� 
int eat; // ���� ���̼�
int tailadd;  //�þ ������
int mv;  //  Ű����� �Է� ���� ����Ű ����
int way;  // gate ��ȣ �����
int temp_sp;// ���� �⺻ �ӵ� ����뵵
extern int life;// ����



enum {       // ���� ����
	BLOCK,   /*  0 : ��� */
	DARK_BLUE,  /*  1 : ��ο� �Ķ� */
	DARK_GREEN,  /*  2 : ��ο� �ʷ� */
	DARK_SKY_BLUE, /*  3 : ��ο� �ϴ� */
	DARK_RED,  /*  4 : ��ο� ���� */
	DARK_VOILET, /*  5 : ��ο� ���� */
	DARK_YELLOW, /*  6 : ��ο� ��� */
	GRAY,   /*  7 : ȸ�� */
	DARK_GRAY,  /*  8 : ��ο� ȸ�� */
	BLUE,   /*  9 : �Ķ� */
	GREEN,   /* 10 : �ʷ� */
	SKY_BLUE,  /* 11 : �ϴ� */
	RED,   /* 12 : ���� */
	VOILET,   /* 13 : ���� */
	YELLOW,   /* 14 : ��� */
	WHITE,   /* 15 : �Ͼ� */
};



int menu(void);  // ���Ӹ޴�

inline void map(int st_lv);  // ���� ��������

void infor(void);  // ���ӳ� ���� ���

void option(void);  // ���̵� ����

void help(void);  // ����

inline int move(void);  // ���� �����̱� ���� �Լ�

void rank(void); // ��ŷ���� �Լ�

void inputRankName(void); // ��ŷ�� ���� �̸��� �Է¹޴´�.

inline void sortRank(void); // ��ŷ ����

inline int chck(int x, int y);  // �ش���ǥ�� ���ڸ� üũ�� ���� �Լ�