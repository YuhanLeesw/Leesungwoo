#include "Screen.h"
#include "Object.h"
#include <Windows.h>
#include <time.h>
#include <tchar.h>



/* ��ŷ */
// ��ŷ������ ���� ����ü
typedef struct _rank
{
	int ClearStage;
	char Name[20];
}RANK;

/* ��ŷ */
RANK rankRecord[100]; // 100����� ��ŷ����
int ClearCount = 0;




int menu(void) { // �޴� ȭ�� ���
	char title[1][30] = {

			"   SNAKE  GAME"
	};
	/* ��ŷ */
	char menulist[7][60] = {
			"��������������������������������",
			"��          ���ӽ���          ��",
			"��          ��    ��          ��",
			"��          �� �� ��          ��",
			"��          ��ŷ����          ��",
			"��          ��������          ��",
			"��������������������������������"
	};
	int i, j = 11;
	char sel;

	/* ��ŷ */
	/* Ŀ�� ���߱�*/
	CONSOLE_CURSOR_INFO CurInfo;
	CurInfo.dwSize = 1;
	CurInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
	/* Ŀ�� ���߱� �� */

	gotoxy(31, 5 + 1);
	SetColor(GREEN);	  printf("%s", title[0]);

	for (i = 0; i < 7; i++) {							// ���� �޴��� ���
		gotoxy(24, 10 + i);
		SetColor(GRAY);	printf("%s", menulist[i]);
	}
	SetColor(WHITE);
	while (1) {									// ����Ű�� "��"�� ������ �޴��� ����Ŵ
		gotoxy(32, j); printf("��");
		sel = _getch();							// Ű�� �ϳ� �Է� ����
		if (sel == 72) {							// ��Ű �Է½� "��"�� ���� �̵�					
			j--;
			gotoxy(32, j + 1); puts("  ");
			if (j < 11) j = 11;						// ���� ���� �޴��� ��ǥ ���δ� �̵� �Ҽ� ����
		}
		if (sel == 80) {							// ��Ű �Է½� "��"�� �Ʒ��� �̵�
			j++;
			gotoxy(32, j - 1); puts("  ");
			if (j > 15) j = 15;						// ���� ���� �޴��� ��ǥ �Ʒ��δ� �̵� �Ҽ� ����
		}
		if (sel == 13)								// ���͸� �Է� �ϸ� �ݺ��� ��������
			break;
	}
	return j - 10;								// "��"�� ����Ű�� y��ǥ���� 10�� �� ���� ����. ���� con�� ���� ��
}


void option() {// ���̵��� ���� �ϴ� option�Լ�.

	int selec;
	int i, op_j = lev + 8;// ���� ���̵� ��ġ�� "��"�� ǥ���ϱ� ����
	char op_menu[3][7] = { "easy", "normal", "hard" };// ��µ� ����
	system("cls");	// ȭ���� ������
	gotoxy(10, 3);  puts("-��    ��-");
	gotoxy(37, 7); printf("OPTION");// �ɼ�ȭ���� ��� ��Ų��.
	for (i = 0; i < 3; i++) {
		gotoxy(40, 9 + i);
		printf("%s", op_menu[i]);
	}
	while (1) {
		gotoxy(37, op_j); printf("��");
		selec = _getch();// ����Ű�� �޴� ���� �Ѵ�.
		if (selec == 72) {// �� �Ϸ� �̵� ����
			op_j--;
			gotoxy(37, op_j + 1); puts("  ");
			if (op_j < 9) op_j = 9;
		}
		if (selec == 80) {
			op_j++;
			gotoxy(37, op_j - 1); puts("  ");
			if (op_j > 11) op_j = 11;
		}
		if (selec == 13)// ���� �Է½� ���� ����
			break;
	}
	lev = op_j - 8;// ���� y��ǥ���� 8�� ���� lev�� �����Ͽ� ���̵��� ���� �ǰ� �Ѵ�.
	system("cls");
}

void help() {									// ���� ���
	system("cls");
	gotoxy(10, 3);  puts("-�� �� ��-");
	gotoxy(36, 8);	SetColor(GRAY);	puts("�۵�Ű");
	gotoxy(36, 10);	puts("�� : ��");
	gotoxy(36, 11);	puts("�� : ��");
	gotoxy(36, 12);	puts("�� : ��");
	gotoxy(36, 13);	puts("�� : ��");
	gotoxy(32, 14);  puts("���ǵ� ��� : +");
	gotoxy(30, 15);  puts("�Ͻ����� : space");
	gotoxy(28, 16);	SetColor(RED);	puts("3�� ������ ����Ű �ݴ�� ����");
	gotoxy(15, 17);  puts("�ʵ��� :�� ���ԵǸ� ������� ����ҿ��� �����ϰ� ����");
	SetColor(WHITE);
	_getch();
	system("cls");
}

/* ��ŷ */
// ��ŷ �޴�
void rank()
{
	int i;

	system("cls"); // ȭ���� ������

	if (ClearCount == 0)
	{
		SetColor(RED);
		gotoxy(20, 10);
		puts("���� ��ŷ ����� �������� �ʽ��ϴ�.");
	}
	else
	{
		sortRank();
		gotoxy(10, 1);
		SetColor(GREEN);
		puts("** ��    ŷ **");
		lev = 2;(WHITE);
		gotoxy(1, 3);
		puts("��������������������������������������������������������������������������");
		gotoxy(5, 4);
		puts(" �� �� ");
		gotoxy(30, 4);
		puts(" ��  �� ");
		gotoxy(55, 4);
		puts(" �������� ");
		gotoxy(1, 5);
		puts("��������������������������������������������������������������������������");


		// ����
		for (i = 0; i < ClearCount; i++) {
			gotoxy(8, 6 + i * 2);
			printf("%d", i + 1);
		}

		// �̸�
		for (i = 0; i < ClearCount; i++) {
			gotoxy(31, 6 + i * 2);
			printf("%s", rankRecord[i].Name);
		}

		// ��������
		for (i = 0; i < ClearCount; i++) {
			gotoxy(57, 6 + i * 2);
			printf("%d stage", rankRecord[i].ClearStage);
		}
	}

	_getch();
	system("cls");
}

/* ��ŷ */
// ��ŷ�� �� �̸� �Է�
void inputRankName()
{
	gotoxy(20, 10);
	printf("�̸� �Է� : ");
	gets(rankRecord[ClearCount].Name);
	rankRecord[ClearCount].ClearStage = stage;
	ClearCount++;

	system("cls");

}

/* ��ŷ */
// ��ŷ ����ü �����Ʈ
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

void infor(void) { // ���ӳ� ���� ���
	int i;
	gotoxy(43, 23); printf("�������� : %2d", food - eat);
	gotoxy(64, 23); printf("������ : ");  // ����, ������ ���
	for (i = 0; i < life; i++) {
		gotoxy(27 + 2 * i, 23); puts("��  ");   // ���� ���� ��ŭ �� ���
	}
}



