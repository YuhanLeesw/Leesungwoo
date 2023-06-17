#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "Screen.h"
#include <time.h>
#include <tchar.h>
#include "Object.h"

struct point {
	int x;
	int y;
}head, tails[1200], del, gate[4] = { 8,6,71,6,8,16,71,16 };// 구조체로 머리와 꼬리, 꼬리삭제용 del의 x,y좌표를 저장

life = 5;// 생명
stage = 1; // 게임 스테이지 단계
lev = 2; // 게임 난이도(easy, normal, hard)
int flag = 0;  // 3을 먹으면 플레그가 3으로 바뀌면서 키보드 반대로 동작
int ffl = 0;		  // 제한 시간을 넘었다는 표시를 하기 위한 플레그
int movcheck = RIGHT;  // 현재 뱀의 이동 방향을 저장
int li_time = 60;   // 제한 시간



void gotoxy(int x, int y)   // gotoxy를 사용하기 위한 함수
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



clock_t st_time, la_time;  // 제한 시간을 넣기 위해 사용


void main()
{
	int con;  // 메뉴에서 선택한 결과값 저장
	int ret;  // 게임오버나 스테이지 클리어시 메인화면으로 돌아오기 위한 플레그
	int resu = 16;
	int re2;

	srand((unsigned)time(NULL));  // rand()함수를 사용키 위한 함수
	while (1) {
		ret = 0;
		while (1) {
			con = menu();
			if (con == 1) break;  // 1번 게임 시작을 선택하면 메뉴화면을 빠져나가 게임이 시작된다
			if (con == 2) option();   // option함수를 호출
			if (con == 3) help();  //help함수를 호출하여 도움말을 보여줌
			/* 랭킹 */
			if (con == 4)
			{
				rank();
			}
			if (con == 5)
			{
				// 게임종료
				system("cls");
				gotoxy(32, 11);
				printf("게임을 종료 합니다\n");
				Sleep(1000);
				exit(0);
			}
		}
		/* 랭킹 */
		// 게임 초기화
		stage = 1;
		life = 1;


		// 게임 시작?
		while (1) {
			map(stage);						// 게임이 시작될 맵을 출력
			for (eat = 0;; ) {					// 스테이지가 넘어가기 전에는 먹은 먹이양을 0으로 수정하여 게임을 시작한다. 사망하였을때
				infor();					// 게임정보 표시
				do {							//  맵에 먹이를 생성한다. 적어도 먹이가 하나는 출력 되야 하므로 do while 사용
					ran_food = rand() % 5 + 49;			// 생성될 먹이 결정됨 (1~5)
					food_x = rand() % 79;				// 먹이가 출력될 x축 좌표 설정
					food_y = rand() % 22;				// 먹이가 출력될 y축 좌표 설정
				} while ((chck(food_x, food_y) != ' '));   // 먹이가 출력될 좌표에 아무런 문자가 없으면 반복문을 빠져 나옴
				gotoxy(food_x, food_y); printf("%c", ran_food);  // 해당 좌표에 결정된 먹이를 출력

				if (eat == 0) {					// 게임이 시작되면 getch()함수로 대기 시간을 줌
					movcheck = RIGHT;			// 초기 뱀의 모양으로 인해 현재 진행중인 방향을 오른쪽으로 지정
					if (224 != _getch()) {
						break;
					}
				}
				if (move() == 3) {					// move함수를 호출. 리턴 값이 트루이면 뱀이 사망하게되어 아래 명령을 수행
					gotoxy(33, 12); SetColor(RED); puts("뱀이 죽었습니다.");
					mov = 0;					   		// 뱀의 움직임을 초기화
					life -= 1;						// 생명 하나 감소
					Sleep(1500);
					fflush(stdin);
					if (life == 0)
					{
						// 생명 5개 소모시 게임 종료
						system("cls");
						gotoxy(35, 12); puts("GAME OVER");
						gotoxy(30, 14); SetColor(GREEN); puts("이어서 하시겠습니까?");
						gotoxy(40, 16); puts("네");
						gotoxy(40, 17); puts("아니오");

						while (1) {									// 방향키로 "▶"를 움직여 메뉴를 가리킴
							gotoxy(36, resu); printf("▶");
							re2 = _getch();							// 키를 하나 입력 받음
							if (re2 == 72) {							// ↑키 입력시 "▶"가 위로 이동					
								resu--;
								gotoxy(36, resu + 1); puts("  ");
								if (resu < 16) resu = 16;						// 가장 상위 메뉴의 좌표 위로는 이동 할수 없음
							}
							if (re2 == 80) {							// ↓키 입력시 "▶"가 아래로 이동
								resu++;
								gotoxy(36, resu - 1); puts("  ");
								if (resu > 17) resu = 17;						// 가장 하위 메뉴의 좌표 아래로는 이동 할수 없음
							}
							if (re2 == 13)								// 엔터를 입력 하면 반복문 빠져나옴
								break;
						}
						if (resu == 16) {
							life = 5;
						}
						if (resu == 17) {
							//getch();
							system("cls");
							ret = 1;						// ret가 1이 되면 반복문을 빠져나가 메인화면으로 돌아감
						}
					}
					break;
				}
				if (stage == 5 && food - eat == 0) {   // 해당 조건은 전 스테이지를 클리어 하였기에 아래 명령 실행
					system("cls");
					gotoxy(35, 12); SetColor(GREEN); puts("STAGE ALL CLEAR!!");
					gotoxy(35, 14); puts("수고 하셨습니다!");
					Sleep(1000);
					_getch();
					system("cls");
					ret = 1;

					/* 랭킹 */
					inputRankName();

					break;

				}
				if (eat == food && eat != 0) {			// 먹은 먹이와 먹어야할 먹이 양이 같은 경우 스테이지 클리어
					system("cls");
					gotoxy(35, 12); puts("STAGE CLEAR!");
					gotoxy(28, 14); puts("다음 스테이지로 넘어 갑니다!");
					Sleep(500);
					flag = 0;						// '3'을 먹어 키보드가 반대로 작용 할경우 초기화
					mov = 0;
					_getch();
					fflush(stdin);
					stage++;					// 스테이지 1단계 상승
					break;
				}
			}
			if (ret == 1) break;
		}
		/* 랭킹 */
		if (stage != 5)
			inputRankName();

	}
}


int move() {// 뱀의 움직일 함수

	int mi;// 반복문을 돌리기 위한 변수
	int go = 0;// 반복문을 빠져 나오기 위한 변수

	for (go = 0;;) {

		gotoxy(73, 23); printf("%3d", tail);// 현재 꼬리길이를 출력.
		if (moving() != 1) {// moving 함수를 호출 한다 리턴 값이 1이 아니면 아래 명령을 실행
			if (tailadd == 0) {// 늘어날 꼬리가 없을 경우의 뱀의 움직임
				del.x = tails[tail - 1].x;			// 배열 tails[tail(꼬리길이)-1] 값이 꼬리의 가장 끝의 좌표를 가지고 있으므로 
				del.y = tails[tail - 1].y;			// 해당 꼬리의 좌표를 del에 저장
				for (mi = tail - 1; mi > 0; mi--) {		// 꼬리들이 자기 꼬리 앞의 꼬리의 좌표를 저장 하도록 함
					tails[mi].x = tails[mi - 1].x;
					tails[mi].y = tails[mi - 1].y;
				}
				tails[0].x = head.x;				// 선두 꼬리가 머리의 좌표를 저장
				tails[0].y = head.y;

				if (mov == UP) head.y--;			// moving에서 mov값이 변화 되고 해당 값에 따라 아래 조건문을 실행
				else if (mov == DOWN) head.y++;
				else if (mov == RIGHT) head.x++;
				else if (mov == LEFT) head.x--;

				if (chck(head.x, head.y) == ':') {	// 필드에 생성된 게이트 체크
					way = rand() % 4;			// 4개의 게이트중 하나를 랜덤으로 선택
					if (movcheck == LEFT) {			// 현재 움직임에 따라 게이트에서 나올 방향 지정
						head.x = gate[way].x - 1;
						head.y = gate[way].y;
					}
					else if (movcheck == RIGHT) {
						head.x = gate[way].x + 1;
						head.y = gate[way].y;
					}
					else if (movcheck == UP) {
						head.x = gate[way].x;
						head.y = gate[way].y - 1;
					}
					else if (movcheck == DOWN) {
						head.x = gate[way].x;
						head.y = gate[way].y + 1;
					}
				}

				if (chck(head.x, head.y) != ' ') {			// 머리가 출력되야 할 좌표가 빈공간이 아니면 go를 1로 바꾸고
					go = 1;								// 조건문을 빠져 나감
					break;
				}
				gotoxy(del.x, del.y); puts(" ");			// 머리가 출력될 좌표가 빈공간이면 뱀이 이동 한다. del로 꼬리 끝 지음
				gotoxy(tails[0].x, tails[0].y); SetColor(YELLOW); puts("N");		// 머리가 있던 곳에 꼬리 출력
				gotoxy(head.x, head.y);

				if (flag != 3) SetColor(GREEN);
				if (flag == 3) SetColor(RED);
				puts("O");				// 한칸 진행해서 머리 출력
				SetColor(WHITE);
				la_time = clock();			// 게임이 진행에 따른 현재 시간 저장
				if (ffl == 0 && ((la_time - st_time) / CLOCKS_PER_SEC) > li_time) {	// ffl이 0일때 현재 시간에서 st_time을 뺀시간이
					speed = 50;												// li_time(60초) 이상이 되면 속도가 50으로 바뀜
					ffl = 1;													// 60초가 지나서 게임속도가 증가 했다는 플레그
				}
				Sleep(speed);									// 게임 스피드 설정
			}

			else if (tailadd > 0) {					// 늘어날 꼬리가 있을 경우의 뱀의 움직임

				tails[tail].x = tails[tail - 1].x;
				tails[tail].y = tails[tail - 1].y;

				for (mi = tail - 1; mi > 0; mi--) {
					tails[mi].x = tails[mi - 1].x;
					tails[mi].y = tails[mi - 1].y;
				}

				del.x = tails[tail].x;
				del.y = tails[tail].y;

				tails[0].x = head.x;
				tails[0].y = head.y;

				if (mov == UP) head.y--;
				else if (mov == DOWN) head.y++;
				else if (mov == RIGHT) head.x++;
				else if (mov == LEFT) head.x--;

				if (chck(head.x, head.y) == ':') {	// 필드에 게이트 생성
					way = rand() % 4;
					if (movcheck == LEFT) {
						head.x = gate[way].x - 1;
						head.y = gate[way].y;
					}
					else if (movcheck == RIGHT) {
						head.x = gate[way].x + 1;
						head.y = gate[way].y;
					}
					else if (movcheck == UP) {
						head.x = gate[way].x;
						head.y = gate[way].y - 1;
					}
					else if (movcheck == DOWN) {
						head.x = gate[way].x;
						head.y = gate[way].y + 1;
					}
				}

				if (chck(head.x, head.y) != ' ') {
					go = 1;
					break;
				}
				gotoxy(tails[0].x, tails[0].y); SetColor(YELLOW); puts("N");  // 꼬리가 늘어 나고 있는 중이기 때문에 del은 사용치 않는다
				gotoxy(head.x, head.y);

				if (flag != 3) SetColor(GREEN);
				if (flag == 3) SetColor(RED);
				puts("O");
				SetColor(WHITE);
				tailadd--;									// 꼬리가 하나 늘어 날때마다 늘어날 꼬리양이 하나씩 감소
				tail++;										// 꼬리가 하나씩 증가
				la_time = clock();
				if (ffl == 0 && ((la_time - st_time) / CLOCKS_PER_SEC) > li_time) {
					speed = 50;
					ffl = 1;
				}
				Sleep(speed);
			}

			if (go == 1) break;
		}
		if (go == 1) break;
	}

	if (chck(head.x, head.y) == '3') {				// 먹이 3을 먹으면 플레그를 3으로 바꾼다. 방향키가 반대로 동작하게 한다
		flag = 3;
	}

	else if (chck(head.x, head.y) == 'H' || chck(head.x, head.y) == 'N') {		// 머리가 출력될 좌표에 H(벽)이나 N(꼬리)가 있을경우
		if (tailadd == 0) {												// 늘어날 꼬리가 없을 경우의 뱀 모양 출력
			gotoxy(del.x, del.y); puts(" ");
		}
		gotoxy(head.x, head.y); SetColor(RED); puts("X");
		gotoxy(tails[0].x, tails[0].y); SetColor(YELLOW); puts("N");
		flag = 0;														// flag가 3이 었을 수도 있으므로 0으로 되돌린다.
		SetColor(WHITE);
		return 3;												// 부딪혀 뱀이 죽은 경우 3 반환
	}
	else if (chck(head.x, head.y) != '3') {
		flag = 0;
	}
	st_time = clock();								// 먹이를 먹으면 시작시간을 리셋한다
	gotoxy(tails[0].x, tails[0].y); SetColor(YELLOW); puts("N");	// 벽에 부딪힌게 아니면 먹이를 먹은경우므로
	gotoxy(head.x, head.y);
	if (flag != 3) SetColor(GREEN);
	if (flag == 3) SetColor(RED);
	puts("O");				// 뱀이 계속 이동케 한다
	Sleep(speed);
	SetColor(WHITE);
	if (tailadd == 0) {// 늘어날 꼬리가 없을 경우 마지막 꼬리를 지움
		gotoxy(del.x, del.y); puts(" ");
	}
	if (go == 1) {
		if (ffl == 1) {
			speed += 10;// ffl==1 일때 먹이를 먹으면 속도를 10씩 늦춰준다.
			if ((temp_sp - 10) <= speed) speed = temp_sp - 10;// 최대 증가치를 기본속도 - 10으로 지정.
		}
		eat += 1;// 먹이를 먹었기 때문에 먹은 먹이가 하나 증가 하고
		tailadd = eat * add;// 늘어날 꼬리값이 정해진다.

	}// 늘어날 양은 먹은 먹이양 * 꼬리 증가양
	return 2;// 죽은 경우가 아니므로 2반환
}

int moving() {

	if (!_kbhit()) {// 키보드 입력 값이 없으면 되돌아간다.// 되돌아 가면 이전의 mov값으로 계속 이동케 된다
		return 2;
	}
	else if (_kbhit()) {// 키보드가 입력 되게 될경우
		mv = _getch();// mv에 키보드로 입력 받은 값을 저장
		if (mv == 224 || mv == 0) {
			mv = _getch();
		}
		if (flag == 3) {// flag가 3이면 방향키 반대로 동작
			if (mv == UP) mv = DOWN;
			else if (mv == DOWN) mv = UP;
			else if (mv == RIGHT) mv = LEFT;
			else if (mv == LEFT) mv = RIGHT;
		}
		switch (mv) {// mv값에 따라 아래 명령 실행
		case UP:// mv가 UP일 경우 현재 진향 방향이 반대방향인 DOWN이
			if (movcheck != DOWN) {// 아니라면 mv는 UP으로 된다.
				mv = UP;
			}
			else { mv = DOWN; }	// 위 경우가 아니면 현재 진행방향이 반대인 DOWN이므로
			movcheck = mv;// mv를 DOWN으로 바꿔준다.
			mov = mv;// 진행할 방향을 나타낼 mov와 현재 진행 방향을 저장할
			break;	// movcheck에 mv(입력된 방향)를 넣어 준다
		case DOWN:
			if (movcheck != UP) {
				mv = DOWN;
			}
			else { mv = UP; }
			movcheck = mv;
			mov = mv;
			break;
		case RIGHT:
			if (movcheck != LEFT) {
				mv = RIGHT;
			}
			else { mv = LEFT; }
			movcheck = mv;
			mov = mv;
			break;
		case LEFT:
			if (movcheck != RIGHT) {
				mv = LEFT;
			}
			else { mv = RIGHT; }
			movcheck = mv;
			mov = mv;
			break;
		case 43:// +키를 누르면 속도가 상승한다.
			speed = speed - 10;
			break;
		case 32:// 스페이스를 누르면 키가 하나 입력 될때까지 일시 정지된다.
			_getch();
		}
		return 2;
	}
	return 1;// 위 경우가 아니면 리턴값을 1로 준다. move를 실행치 않는다.
}
void map(int st_lv) {// 맵을 출력 함. 스테이지 레벨을 받아온다
	int i;

	tail = 2;// 초기 꼬리길이 2로 설정
	tailadd = 0;// 늘어날 꼬리양 0으로 설정
	movcheck = RIGHT;
	flag = 0;// flag 0으로 설정  3이 되면 방향키 반대로 작동

	system("cls");
	head.x = 7;// 초기 머리의 좌표가 지정
	head.y = 5;
	tails[0].x = 6;// 초기 꼬리의 좌표 값 지정
	tails[0].y = 5;
	tails[1].x = 5;
	tails[1].y = 5;

	st_time = clock();// 게임 시작시 시작시간을 저장
	ffl = 0;// 게임 시간시 ffl을 0으로 초기화

	del.x = 4;// del좌표값 지정
	del.y = 5;
	SetColor(YELLOW);
	gotoxy(5, 5); puts("NN");// 초기 뱀 모양 출력
	SetColor(GREEN);
	gotoxy(7, 5); puts("O");
	SetColor(DARK_GRAY);
	for (i = 0; i < 80; i++) {// 게임 화면의 가로 벽 출력
		gotoxy(i, 0); printf("H");
		gotoxy(i, 22); printf("H");
		gotoxy(i, 24); printf("H");
	}
	for (i = 1; i < 22; i++) {// 게임화면의 세로 벽 출력
		gotoxy(0, i); printf("H");
		gotoxy(79, i); printf("H");
	}

	gotoxy(71, 6); puts(":");// 필드에 게이트 생성
	gotoxy(8, 6); puts(":");
	gotoxy(8, 16); puts(":");
	gotoxy(71, 16); puts(":");

	SetColor(WHITE);
	gotoxy(2, 23); printf("stage : %d         life : ", stage);  // 현제 스테이지 출력

	switch (st_lv) {// 현재 스테이지에 따라 장애물과 난이도가 틀려짐
	case 1:	// 옵션에서 설정한 난이도에 따라 스테이지별로 난이도 틀려짐(속도, 먹이양, 늘어나는 꼬리양)
		gotoxy(24, 11);
		for (i = 0; i < 31; i++) {// 장애물 출력
			printf("H");
		}
		if (lev == 1) {// easy난이도의 게임 설정
			speed = 220; add = 2; food = 1;
		}
		if (lev == 2) {// normal난이도의 게임 설정
			speed = 200; add = 2; food = 5;
		}
		if (lev == 3) {// hard난이도의 게임 설정
			speed = 180; add = 3; food = 8;
		}
		break;
	case 2:
		gotoxy(24, 11);
		for (i = 0; i < 31; i++) {
			printf("H");
		}
		for (i = 0; i < 11; i++) {
			gotoxy(39, 6 + i);	printf("H");
		}
		if (lev == 1) {
			speed = 200; add = 2; food = 1;
		}
		if (lev == 2) {
			speed = 180; add = 3; food = 7;
		}
		if (lev == 3) {
			speed = 150; add = 4; food = 7;
		}
		break;
	case 3:
		for (i = 0; i < 11; i++) {
			gotoxy(39, 6 + i);	printf("H");
		}
		gotoxy(24, 6);
		for (i = 0; i < 31; i++) {
			printf("H");
		}
		gotoxy(24, 17);
		for (i = 0; i < 31; i++) {
			printf("H");
		}
		if (lev == 1) {
			speed = 180; add = 3; food = 1;
		}
		if (lev == 2) {
			speed = 150; add = 3; food = 10;
		}
		if (lev == 3) {
			speed = 120; add = 4; food = 10;
		}
		break;
	case 4:
		for (i = 0; i < 15; i++) {
			gotoxy(39, 4 + i);	printf("H");
		}
		for (i = 0; i < 11; i++) {
			gotoxy(20, 6 + i);	printf("H");
		}
		for (i = 0; i < 11; i++) {
			gotoxy(58, 6 + i);	printf("H");
		}
		if (lev == 1) {
			speed = 150; add = 3; food = 1;
		}
		if (lev == 2) {
			speed = 110; add = 4; food = 12;
		}
		if (lev == 3) {
			speed = 90; add = 5; food = 17;
		}
		break;
	case 5:
		for (i = 0; i < 15; i++) {
			gotoxy(39, 4 + i);	printf("H");
		}
		for (i = 0; i < 11; i++) {
			gotoxy(20, 6 + i);	printf("H");
		}
		for (i = 0; i < 11; i++) {
			gotoxy(58, 6 + i);	printf("H");
		}
		gotoxy(24, 11);
		for (i = 0; i < 31; i++) {
			printf("H");
		}
		if (lev == 1) {
			speed = 100; add = 4; food = 1;
		}
		if (lev == 2) {
			speed = 70; add = 5; food = 15;
		}
		if (lev == 3) {
			speed = 60; add = 6; food = 20;
		}
		break;
	}
	temp_sp = speed;// 게임속도를 temp_sp에 저장한다.
	SetColor(WHITE);
}