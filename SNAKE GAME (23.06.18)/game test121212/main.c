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
}head, tails[1200], del, gate[4] = { 8,6,71,6,8,16,71,16 };// ����ü�� �Ӹ��� ����, ���������� del�� x,y��ǥ�� ����

life = 5;// ����
stage = 1; // ���� �������� �ܰ�
lev = 2; // ���� ���̵�(easy, normal, hard)
int flag = 0;  // 3�� ������ �÷��װ� 3���� �ٲ�鼭 Ű���� �ݴ�� ����
int ffl = 0;		  // ���� �ð��� �Ѿ��ٴ� ǥ�ø� �ϱ� ���� �÷���
int movcheck = RIGHT;  // ���� ���� �̵� ������ ����
int li_time = 60;   // ���� �ð�



void gotoxy(int x, int y)   // gotoxy�� ����ϱ� ���� �Լ�
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}



clock_t st_time, la_time;  // ���� �ð��� �ֱ� ���� ���


void main()
{
	int con;  // �޴����� ������ ����� ����
	int ret;  // ���ӿ����� �������� Ŭ����� ����ȭ������ ���ƿ��� ���� �÷���
	int resu = 16;
	int re2;

	srand((unsigned)time(NULL));  // rand()�Լ��� ���Ű ���� �Լ�
	while (1) {
		ret = 0;
		while (1) {
			con = menu();
			if (con == 1) break;  // 1�� ���� ������ �����ϸ� �޴�ȭ���� �������� ������ ���۵ȴ�
			if (con == 2) option();   // option�Լ��� ȣ��
			if (con == 3) help();  //help�Լ��� ȣ���Ͽ� ������ ������
			/* ��ŷ */
			if (con == 4)
			{
				rank();
			}
			if (con == 5)
			{
				// ��������
				system("cls");
				gotoxy(32, 11);
				printf("������ ���� �մϴ�\n");
				Sleep(1000);
				exit(0);
			}
		}
		/* ��ŷ */
		// ���� �ʱ�ȭ
		stage = 1;
		life = 1;


		// ���� ����?
		while (1) {
			map(stage);						// ������ ���۵� ���� ���
			for (eat = 0;; ) {					// ���������� �Ѿ�� ������ ���� ���̾��� 0���� �����Ͽ� ������ �����Ѵ�. ����Ͽ�����
				infor();					// �������� ǥ��
				do {							//  �ʿ� ���̸� �����Ѵ�. ��� ���̰� �ϳ��� ��� �Ǿ� �ϹǷ� do while ���
					ran_food = rand() % 5 + 49;			// ������ ���� ������ (1~5)
					food_x = rand() % 79;				// ���̰� ��µ� x�� ��ǥ ����
					food_y = rand() % 22;				// ���̰� ��µ� y�� ��ǥ ����
				} while ((chck(food_x, food_y) != ' '));   // ���̰� ��µ� ��ǥ�� �ƹ��� ���ڰ� ������ �ݺ����� ���� ����
				gotoxy(food_x, food_y); printf("%c", ran_food);  // �ش� ��ǥ�� ������ ���̸� ���

				if (eat == 0) {					// ������ ���۵Ǹ� getch()�Լ��� ��� �ð��� ��
					movcheck = RIGHT;			// �ʱ� ���� ������� ���� ���� �������� ������ ���������� ����
					if (224 != _getch()) {
						break;
					}
				}
				if (move() == 3) {					// move�Լ��� ȣ��. ���� ���� Ʈ���̸� ���� ����ϰԵǾ� �Ʒ� ����� ����
					gotoxy(33, 12); SetColor(RED); puts("���� �׾����ϴ�.");
					mov = 0;					   		// ���� �������� �ʱ�ȭ
					life -= 1;						// ���� �ϳ� ����
					Sleep(1500);
					fflush(stdin);
					if (life == 0)
					{
						// ���� 5�� �Ҹ�� ���� ����
						system("cls");
						gotoxy(35, 12); puts("GAME OVER");
						gotoxy(30, 14); SetColor(GREEN); puts("�̾ �Ͻðڽ��ϱ�?");
						gotoxy(40, 16); puts("��");
						gotoxy(40, 17); puts("�ƴϿ�");

						while (1) {									// ����Ű�� "��"�� ������ �޴��� ����Ŵ
							gotoxy(36, resu); printf("��");
							re2 = _getch();							// Ű�� �ϳ� �Է� ����
							if (re2 == 72) {							// ��Ű �Է½� "��"�� ���� �̵�					
								resu--;
								gotoxy(36, resu + 1); puts("  ");
								if (resu < 16) resu = 16;						// ���� ���� �޴��� ��ǥ ���δ� �̵� �Ҽ� ����
							}
							if (re2 == 80) {							// ��Ű �Է½� "��"�� �Ʒ��� �̵�
								resu++;
								gotoxy(36, resu - 1); puts("  ");
								if (resu > 17) resu = 17;						// ���� ���� �޴��� ��ǥ �Ʒ��δ� �̵� �Ҽ� ����
							}
							if (re2 == 13)								// ���͸� �Է� �ϸ� �ݺ��� ��������
								break;
						}
						if (resu == 16) {
							life = 5;
						}
						if (resu == 17) {
							//getch();
							system("cls");
							ret = 1;						// ret�� 1�� �Ǹ� �ݺ����� �������� ����ȭ������ ���ư�
						}
					}
					break;
				}
				if (stage == 5 && food - eat == 0) {   // �ش� ������ �� ���������� Ŭ���� �Ͽ��⿡ �Ʒ� ��� ����
					system("cls");
					gotoxy(35, 12); SetColor(GREEN); puts("STAGE ALL CLEAR!!");
					gotoxy(35, 14); puts("���� �ϼ̽��ϴ�!");
					Sleep(1000);
					_getch();
					system("cls");
					ret = 1;

					/* ��ŷ */
					inputRankName();

					break;

				}
				if (eat == food && eat != 0) {			// ���� ���̿� �Ծ���� ���� ���� ���� ��� �������� Ŭ����
					system("cls");
					gotoxy(35, 12); puts("STAGE CLEAR!");
					gotoxy(28, 14); puts("���� ���������� �Ѿ� ���ϴ�!");
					Sleep(500);
					flag = 0;						// '3'�� �Ծ� Ű���尡 �ݴ�� �ۿ� �Ұ�� �ʱ�ȭ
					mov = 0;
					_getch();
					fflush(stdin);
					stage++;					// �������� 1�ܰ� ���
					break;
				}
			}
			if (ret == 1) break;
		}
		/* ��ŷ */
		if (stage != 5)
			inputRankName();

	}
}


int move() {// ���� ������ �Լ�

	int mi;// �ݺ����� ������ ���� ����
	int go = 0;// �ݺ����� ���� ������ ���� ����

	for (go = 0;;) {

		gotoxy(73, 23); printf("%3d", tail);// ���� �������̸� ���.
		if (moving() != 1) {// moving �Լ��� ȣ�� �Ѵ� ���� ���� 1�� �ƴϸ� �Ʒ� ����� ����
			if (tailadd == 0) {// �þ ������ ���� ����� ���� ������
				del.x = tails[tail - 1].x;			// �迭 tails[tail(��������)-1] ���� ������ ���� ���� ��ǥ�� ������ �����Ƿ� 
				del.y = tails[tail - 1].y;			// �ش� ������ ��ǥ�� del�� ����
				for (mi = tail - 1; mi > 0; mi--) {		// �������� �ڱ� ���� ���� ������ ��ǥ�� ���� �ϵ��� ��
					tails[mi].x = tails[mi - 1].x;
					tails[mi].y = tails[mi - 1].y;
				}
				tails[0].x = head.x;				// ���� ������ �Ӹ��� ��ǥ�� ����
				tails[0].y = head.y;

				if (mov == UP) head.y--;			// moving���� mov���� ��ȭ �ǰ� �ش� ���� ���� �Ʒ� ���ǹ��� ����
				else if (mov == DOWN) head.y++;
				else if (mov == RIGHT) head.x++;
				else if (mov == LEFT) head.x--;

				if (chck(head.x, head.y) == ':') {	// �ʵ忡 ������ ����Ʈ üũ
					way = rand() % 4;			// 4���� ����Ʈ�� �ϳ��� �������� ����
					if (movcheck == LEFT) {			// ���� �����ӿ� ���� ����Ʈ���� ���� ���� ����
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

				if (chck(head.x, head.y) != ' ') {			// �Ӹ��� ��µǾ� �� ��ǥ�� ������� �ƴϸ� go�� 1�� �ٲٰ�
					go = 1;								// ���ǹ��� ���� ����
					break;
				}
				gotoxy(del.x, del.y); puts(" ");			// �Ӹ��� ��µ� ��ǥ�� ������̸� ���� �̵� �Ѵ�. del�� ���� �� ����
				gotoxy(tails[0].x, tails[0].y); SetColor(YELLOW); puts("N");		// �Ӹ��� �ִ� ���� ���� ���
				gotoxy(head.x, head.y);

				if (flag != 3) SetColor(GREEN);
				if (flag == 3) SetColor(RED);
				puts("O");				// ��ĭ �����ؼ� �Ӹ� ���
				SetColor(WHITE);
				la_time = clock();			// ������ ���࿡ ���� ���� �ð� ����
				if (ffl == 0 && ((la_time - st_time) / CLOCKS_PER_SEC) > li_time) {	// ffl�� 0�϶� ���� �ð����� st_time�� ���ð���
					speed = 50;												// li_time(60��) �̻��� �Ǹ� �ӵ��� 50���� �ٲ�
					ffl = 1;													// 60�ʰ� ������ ���Ӽӵ��� ���� �ߴٴ� �÷���
				}
				Sleep(speed);									// ���� ���ǵ� ����
			}

			else if (tailadd > 0) {					// �þ ������ ���� ����� ���� ������

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

				if (chck(head.x, head.y) == ':') {	// �ʵ忡 ����Ʈ ����
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
				gotoxy(tails[0].x, tails[0].y); SetColor(YELLOW); puts("N");  // ������ �þ� ���� �ִ� ���̱� ������ del�� ���ġ �ʴ´�
				gotoxy(head.x, head.y);

				if (flag != 3) SetColor(GREEN);
				if (flag == 3) SetColor(RED);
				puts("O");
				SetColor(WHITE);
				tailadd--;									// ������ �ϳ� �þ� �������� �þ �������� �ϳ��� ����
				tail++;										// ������ �ϳ��� ����
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

	if (chck(head.x, head.y) == '3') {				// ���� 3�� ������ �÷��׸� 3���� �ٲ۴�. ����Ű�� �ݴ�� �����ϰ� �Ѵ�
		flag = 3;
	}

	else if (chck(head.x, head.y) == 'H' || chck(head.x, head.y) == 'N') {		// �Ӹ��� ��µ� ��ǥ�� H(��)�̳� N(����)�� �������
		if (tailadd == 0) {												// �þ ������ ���� ����� �� ��� ���
			gotoxy(del.x, del.y); puts(" ");
		}
		gotoxy(head.x, head.y); SetColor(RED); puts("X");
		gotoxy(tails[0].x, tails[0].y); SetColor(YELLOW); puts("N");
		flag = 0;														// flag�� 3�� ���� ���� �����Ƿ� 0���� �ǵ�����.
		SetColor(WHITE);
		return 3;												// �ε��� ���� ���� ��� 3 ��ȯ
	}
	else if (chck(head.x, head.y) != '3') {
		flag = 0;
	}
	st_time = clock();								// ���̸� ������ ���۽ð��� �����Ѵ�
	gotoxy(tails[0].x, tails[0].y); SetColor(YELLOW); puts("N");	// ���� �ε����� �ƴϸ� ���̸� �������Ƿ�
	gotoxy(head.x, head.y);
	if (flag != 3) SetColor(GREEN);
	if (flag == 3) SetColor(RED);
	puts("O");				// ���� ��� �̵��� �Ѵ�
	Sleep(speed);
	SetColor(WHITE);
	if (tailadd == 0) {// �þ ������ ���� ��� ������ ������ ����
		gotoxy(del.x, del.y); puts(" ");
	}
	if (go == 1) {
		if (ffl == 1) {
			speed += 10;// ffl==1 �϶� ���̸� ������ �ӵ��� 10�� �����ش�.
			if ((temp_sp - 10) <= speed) speed = temp_sp - 10;// �ִ� ����ġ�� �⺻�ӵ� - 10���� ����.
		}
		eat += 1;// ���̸� �Ծ��� ������ ���� ���̰� �ϳ� ���� �ϰ�
		tailadd = eat * add;// �þ �������� ��������.

	}// �þ ���� ���� ���̾� * ���� ������
	return 2;// ���� ��찡 �ƴϹǷ� 2��ȯ
}

int moving() {

	if (!_kbhit()) {// Ű���� �Է� ���� ������ �ǵ��ư���.// �ǵ��� ���� ������ mov������ ��� �̵��� �ȴ�
		return 2;
	}
	else if (_kbhit()) {// Ű���尡 �Է� �ǰ� �ɰ��
		mv = _getch();// mv�� Ű����� �Է� ���� ���� ����
		if (mv == 224 || mv == 0) {
			mv = _getch();
		}
		if (flag == 3) {// flag�� 3�̸� ����Ű �ݴ�� ����
			if (mv == UP) mv = DOWN;
			else if (mv == DOWN) mv = UP;
			else if (mv == RIGHT) mv = LEFT;
			else if (mv == LEFT) mv = RIGHT;
		}
		switch (mv) {// mv���� ���� �Ʒ� ��� ����
		case UP:// mv�� UP�� ��� ���� ���� ������ �ݴ������ DOWN��
			if (movcheck != DOWN) {// �ƴ϶�� mv�� UP���� �ȴ�.
				mv = UP;
			}
			else { mv = DOWN; }	// �� ��찡 �ƴϸ� ���� ��������� �ݴ��� DOWN�̹Ƿ�
			movcheck = mv;// mv�� DOWN���� �ٲ��ش�.
			mov = mv;// ������ ������ ��Ÿ�� mov�� ���� ���� ������ ������
			break;	// movcheck�� mv(�Էµ� ����)�� �־� �ش�
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
		case 43:// +Ű�� ������ �ӵ��� ����Ѵ�.
			speed = speed - 10;
			break;
		case 32:// �����̽��� ������ Ű�� �ϳ� �Է� �ɶ����� �Ͻ� �����ȴ�.
			_getch();
		}
		return 2;
	}
	return 1;// �� ��찡 �ƴϸ� ���ϰ��� 1�� �ش�. move�� ����ġ �ʴ´�.
}
void map(int st_lv) {// ���� ��� ��. �������� ������ �޾ƿ´�
	int i;

	tail = 2;// �ʱ� �������� 2�� ����
	tailadd = 0;// �þ ������ 0���� ����
	movcheck = RIGHT;
	flag = 0;// flag 0���� ����  3�� �Ǹ� ����Ű �ݴ�� �۵�

	system("cls");
	head.x = 7;// �ʱ� �Ӹ��� ��ǥ�� ����
	head.y = 5;
	tails[0].x = 6;// �ʱ� ������ ��ǥ �� ����
	tails[0].y = 5;
	tails[1].x = 5;
	tails[1].y = 5;

	st_time = clock();// ���� ���۽� ���۽ð��� ����
	ffl = 0;// ���� �ð��� ffl�� 0���� �ʱ�ȭ

	del.x = 4;// del��ǥ�� ����
	del.y = 5;
	SetColor(YELLOW);
	gotoxy(5, 5); puts("NN");// �ʱ� �� ��� ���
	SetColor(GREEN);
	gotoxy(7, 5); puts("O");
	SetColor(DARK_GRAY);
	for (i = 0; i < 80; i++) {// ���� ȭ���� ���� �� ���
		gotoxy(i, 0); printf("H");
		gotoxy(i, 22); printf("H");
		gotoxy(i, 24); printf("H");
	}
	for (i = 1; i < 22; i++) {// ����ȭ���� ���� �� ���
		gotoxy(0, i); printf("H");
		gotoxy(79, i); printf("H");
	}

	gotoxy(71, 6); puts(":");// �ʵ忡 ����Ʈ ����
	gotoxy(8, 6); puts(":");
	gotoxy(8, 16); puts(":");
	gotoxy(71, 16); puts(":");

	SetColor(WHITE);
	gotoxy(2, 23); printf("stage : %d         life : ", stage);  // ���� �������� ���

	switch (st_lv) {// ���� ���������� ���� ��ֹ��� ���̵��� Ʋ����
	case 1:	// �ɼǿ��� ������ ���̵��� ���� ������������ ���̵� Ʋ����(�ӵ�, ���̾�, �þ�� ������)
		gotoxy(24, 11);
		for (i = 0; i < 31; i++) {// ��ֹ� ���
			printf("H");
		}
		if (lev == 1) {// easy���̵��� ���� ����
			speed = 220; add = 2; food = 1;
		}
		if (lev == 2) {// normal���̵��� ���� ����
			speed = 200; add = 2; food = 5;
		}
		if (lev == 3) {// hard���̵��� ���� ����
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
	temp_sp = speed;// ���Ӽӵ��� temp_sp�� �����Ѵ�.
	SetColor(WHITE);
}