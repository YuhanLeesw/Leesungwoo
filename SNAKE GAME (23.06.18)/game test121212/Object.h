#include <stdbool.h>
#ifndef OBJECT_H
#define OBJECT_H
#define NUM_FRUITS 100
#define NUM_WALLS 1000


int chck(int x, int y)// �ش� x, y��ǥ�� ���ڸ� ���� �Ͽ� ��ȯ �� �ش�.
{
	COORD Cur;
	TCHAR Char;
	DWORD dwRead;

	Cur.X = x;
	Cur.Y = y;

	ReadConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),
		&Char, 1, Cur, &dwRead);
	return Char;
}
#endif