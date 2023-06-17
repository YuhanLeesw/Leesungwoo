#pragma once
#include <windows.h>
#include "Object.h"

#define UP 72   
#define DOWN 80
#define LEFT 75
#define RIGHT 77

inline void SetColor(int color)     // 문자 색깔 변경을 위한 함수.
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

extern int stage;  // 게임 스테이지 단계
extern int lev;    // 게임 난이도(easy, normal, hard)
int speed;    // 게임 속도
int tail;     // 꼬리길이
int food;   // 먹이 수
int add;    // 꼬리 증가량
int food_x;   // 먹이가 출력될 x좌표
int food_y;   // 먹이가 출력될 y좌표
char ran_food; // 표시될 먹이(1~5) 
int mov;  // 뱀 움직임을 저장 
int eat; // 먹은 먹이수
int tailadd;  //늘어날 꼬리양
int mv;  //  키보드로 입력 받은 방향키 저장
int way;  // gate 번호 저장용
int temp_sp;// 게임 기본 속도 저장용도
extern int life;// 생명



enum {       // 색깔 지정
	BLOCK,   /*  0 : 까망 */
	DARK_BLUE,  /*  1 : 어두운 파랑 */
	DARK_GREEN,  /*  2 : 어두운 초록 */
	DARK_SKY_BLUE, /*  3 : 어두운 하늘 */
	DARK_RED,  /*  4 : 어두운 빨강 */
	DARK_VOILET, /*  5 : 어두운 보라 */
	DARK_YELLOW, /*  6 : 어두운 노랑 */
	GRAY,   /*  7 : 회색 */
	DARK_GRAY,  /*  8 : 어두운 회색 */
	BLUE,   /*  9 : 파랑 */
	GREEN,   /* 10 : 초록 */
	SKY_BLUE,  /* 11 : 하늘 */
	RED,   /* 12 : 빨강 */
	VOILET,   /* 13 : 보라 */
	YELLOW,   /* 14 : 노랑 */
	WHITE,   /* 15 : 하양 */
};



int menu(void);  // 게임메뉴

inline void map(int st_lv);  // 게임 스테이지

void infor(void);  // 게임내 정보 출력

void option(void);  // 난이도 설정

void help(void);  // 도움말

inline int move(void);  // 뱀을 움직이기 위한 함수

void rank(void); // 랭킹보기 함수

void inputRankName(void); // 랭킹을 위해 이름을 입력받는다.

inline void sortRank(void); // 랭킹 소팅

inline int chck(int x, int y);  // 해당좌표의 문자를 체크를 위한 함수