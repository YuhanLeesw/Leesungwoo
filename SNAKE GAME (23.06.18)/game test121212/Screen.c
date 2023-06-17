#include "Screen.h"
#include "Object.h"
#include <Windows.h>
#include <time.h>
#include <tchar.h>



/* 랭킹 */
// 랭킹관리를 위한 구조체
typedef struct _rank
{
	int ClearStage;
	char Name[20];
}RANK;

/* 랭킹 */
RANK rankRecord[100]; // 100명까지 랭킹저장
int ClearCount = 0;




int menu(void) { // 메뉴 화면 출력
	char title[1][30] = {

			"   SNAKE  GAME"
	};
	/* 랭킹 */
	char menulist[7][60] = {
			"┏━━━━━━━━━━━━━━┓",
			"┃          게임시작          ┃",
			"┃          옵    션          ┃",
			"┃          도 움 말          ┃",
			"┃          랭킹보기          ┃",
			"┃          게임종료          ┃",
			"┗━━━━━━━━━━━━━━┛"
	};
	int i, j = 11;
	char sel;

	/* 랭킹 */
	/* 커서 감추기*/
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	/* 커서 감추기 끝 */

	gotoxy(31, 5 + 1);
	SetColor(GREEN);	  printf("%s", title[0]);

	for (i = 0; i < 7; i++) {							// 게임 메뉴를 출력
		gotoxy(24, 10 + i);
		SetColor(GRAY);	printf("%s", menulist[i]);
	}
	SetColor(WHITE);
	while (1) {									// 방향키로 "▶"를 움직여 메뉴를 가리킴
		gotoxy(32, j); printf("▶");
		sel = _getch();							// 키를 하나 입력 받음
		if (sel == 72) {							// ↑키 입력시 "▶"가 위로 이동					
			j--;
			gotoxy(32, j + 1); puts("  ");
			if (j < 11) j = 11;						// 가장 상위 메뉴의 좌표 위로는 이동 할수 없음
		}
		if (sel == 80) {							// ↓키 입력시 "▶"가 아래로 이동
			j++;
			gotoxy(32, j - 1); puts("  ");
			if (j > 15) j = 15;						// 가장 하위 메뉴의 좌표 아래로는 이동 할수 없음
		}
		if (sel == 13)								// 엔터를 입력 하면 반복문 빠져나옴
			break;
	}
	return j - 10;								// "▶"가 가리키는 y좌표에서 10을 뺀 값을 리턴. 위의 con에 들어가게 됨
}


void option() {// 난이도를 설정 하는 option함수.

	int selec;
	int i, op_j = lev + 8;// 현재 난이도 위치에 "▶"를 표시하기 위함
	char op_menu[3][7] = { "easy", "normal", "hard" };// 출력될 문자
	system("cls");	// 화면을 지운후
	gotoxy(10, 3);  puts("-옵    션-");
	gotoxy(37, 7); printf("OPTION");// 옵션화면을 출력 시킨다.
	for (i = 0; i < 3; i++) {
		gotoxy(40, 9 + i);
		printf("%s", op_menu[i]);
	}
	while (1) {
		gotoxy(37, op_j); printf("▶");
		selec = _getch();// 방향키로 메뉴 선택 한다.
		if (selec == 72) {// 상 하로 이동 가능
			op_j--;
			gotoxy(37, op_j + 1); puts("  ");
			if (op_j < 9) op_j = 9;
		}
		if (selec == 80) {
			op_j++;
			gotoxy(37, op_j - 1); puts("  ");
			if (op_j > 11) op_j = 11;
		}
		if (selec == 13)// 엔터 입력시 빠져 나감
			break;
	}
	lev = op_j - 8;// 현재 y좌표에서 8뺀 값을 lev에 저장하여 난이도가 조정 되게 한다.
	system("cls");
}

void help() {									// 도움말 출력
	system("cls");
	gotoxy(10, 3);  puts("-도 움 말-");
	gotoxy(36, 8);	SetColor(GRAY);	puts("작동키");
	gotoxy(36, 10);	puts("상 : ↑");
	gotoxy(36, 11);	puts("하 : ↓");
	gotoxy(36, 12);	puts("좌 : ←");
	gotoxy(36, 13);	puts("우 : →");
	gotoxy(32, 14);  puts("스피드 상승 : +");
	gotoxy(30, 15);  puts("일시정지 : space");
	gotoxy(28, 16);	SetColor(RED);	puts("3을 먹으면 방향키 반대로 동작");
	gotoxy(15, 17);  puts("필드의 :로 들어가게되면 네장소중 한장소에서 랜덤하게 나옴");
	SetColor(WHITE);
	_getch();
	system("cls");
}

/* 랭킹 */
// 랭킹 메뉴
void rank()
{
	int i;

	system("cls"); // 화면을 지운후

	if (ClearCount == 0)
	{
		SetColor(RED);
		gotoxy(20, 10);
		puts("현재 랭킹 기록이 존재하지 않습니다.");
	}
	else
	{
		sortRank();
		gotoxy(10, 1);
		SetColor(GREEN);
		puts("** 랭    킹 **");
		lev = 2;(WHITE);
		gotoxy(1, 3);
		puts("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");
		gotoxy(5, 4);
		puts(" 순 위 ");
		gotoxy(30, 4);
		puts(" 이  름 ");
		gotoxy(55, 4);
		puts(" 스테이지 ");
		gotoxy(1, 5);
		puts("━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━");


		// 순위
		for (i = 0; i < ClearCount; i++) {
			gotoxy(8, 6 + i * 2);
			printf("%d", i + 1);
		}

		// 이름
		for (i = 0; i < ClearCount; i++) {
			gotoxy(31, 6 + i * 2);
			printf("%s", rankRecord[i].Name);
		}

		// 스테이지
		for (i = 0; i < ClearCount; i++) {
			gotoxy(57, 6 + i * 2);
			printf("%d stage", rankRecord[i].ClearStage);
		}
	}

	_getch();
	system("cls");
}

/* 랭킹 */
// 랭킹에 들어갈 이름 입력
void inputRankName()
{
	gotoxy(20, 10);
	printf("이름 입력 : ");
	gets(rankRecord[ClearCount].Name);
	rankRecord[ClearCount].ClearStage = stage;
	ClearCount++;

	system("cls");

}

/* 랭킹 */
// 랭킹 구조체 버블소트
void sortRank(void)
{
	int i, j;
	RANK temp;

	for (i = 0; i < ClearCount - 1; i++)
	{
		for (j = 0; j < ClearCount - i - 1; j++)
		{
			if (rankRecord[j].ClearStage < rankRecord[j + 1].ClearStage)
			{
				temp = rankRecord[j];
				rankRecord[j] = rankRecord[j + 1];
				rankRecord[j + 1] = temp;
			}
		}
	}
}

void infor(void) { // 게임내 정보 출력
	int i;
	gotoxy(43, 23); printf("남은먹이 : %2d", food - eat);
	gotoxy(64, 23); printf("꼬리수 : ");  // 먹이, 꼬리수 출력
	for (i = 0; i < life; i++) {
		gotoxy(27 + 2 * i, 23); puts("♡  ");   // 생명 숫자 만큼 ♡ 출력
	}
}



