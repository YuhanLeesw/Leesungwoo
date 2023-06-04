#pragma once
#include "Screen.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>


// ������ũ ���
char snakeHead = 'O';

void snakeHeadSetting()
{
    snakeHead++;
    if (snakeHead >= 'Z') snakeHead = 'A';
}

/* ȭ�� ���μ��� ����*/
int screenWidth = 80;
int screenHeight = 25;

void setScreenSize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
}

/*����*/
int Lecture;
int A;
int B;
int C;
int Progress;
Lecture = NUM_FRUITS;

double Hakjum;
double jumsu;

void Jumsu()
{
    jumsu = Hakjum / Lecture;
}

char strJumsu[10];
void stringJumsu()
{
    snprintf(strJumsu, sizeof(strJumsu), "%.2f", jumsu);

}

void ReSet()
{
    memset(ScreenBuffer, '\0', sizeof(ScreenBuffer));
    A = 0;
    B = 0;
    C = 0;
    Progress = 0;
    Hakjum = 0;
    setScreenSize(70, 20);
    ClearBuffer();
    snake.x = WIDTH / 2;
    snake.y = HEIGHT / 2;
    gameState = 0;

    // �� ����
    generateWalls();
    // ���� ����
    generateFruits();
    // �ʱ� ���� ����
    tailLength = 5; // ���� ���� �ʱ�ȭ
    for (int i = 0; i < tailLength; i++) {
        tail[i].x = snake.x - (i + 1);
        tail[i].y = snake.y;
    }

}

char strA[4];
void stringA()
{
    snprintf(strA, sizeof(strA), "%d", A);
}

char strB[4];
void stringB()
{
    snprintf(strB, sizeof(strB), "%d", B);

}

char strC[4];
void stringC()
{
    snprintf(strC, sizeof(strC), "%d", C);
}

char strProgress[4];
void stringProgress()
{
    snprintf(strProgress, sizeof(strProgress), "%d", Progress);
}

char strLecture[4];
void stringLecture()
{
    snprintf(strLecture, sizeof(strLecture), "%d", Lecture);
}

char strHead[2];
void stringHead()
{
    strHead[0] = snakeHead;
}



/* Ŀ����ġ */
void setCursorPos(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/* ���, �۾� ��*/
void SetColor(unsigned short backgroundColor, unsigned short textColor)
{
    unsigned short color = textColor;
    color = color + (backgroundColor << 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* �޴�ȭ�� ����*/
void ClearBuffer()
{
    int y = 0;
    while (y < screenHeight + 2)
    {
        int x = 0;
        while (x < screenWidth + 2)
        {
            if (y == 0 || y == (screenHeight + 1))
                ScreenBuffer[x + (y * (screenWidth + 3))] = '-';
            else
            {
                if (x == 0 || x == (screenWidth + 1))
                    ScreenBuffer[x + (y * (screenWidth + 3))] = '|';
                else
                    ScreenBuffer[x + (y * (screenWidth + 3))] = ' ';
            }
            x = x + 1;
        }
        ScreenBuffer[x + (y * (screenWidth + 3))] = '\n';
        y = y + 1;
    }
    ScreenBuffer[(y * (screenWidth + 3))] = '\0';
}

/*���� �ȿ� �۾�����*/
int WriteToBuffer(int x, int y, const char* str)
{
    int i = 0;

    while (i < strlen(str))
    {
        ScreenBuffer[x + (y * (screenWidth + 3)) + i] = str[i];
        i = i + 1;
    }

    return 0;
}

/* ���� ��ġ�� �� �����ϱ�*/
void generateWalls()
{
    walls = (struct Wall*)malloc(NUM_WALLS * sizeof(struct Wall));


    if (walls == NULL)
    {
        // ���� �޸� �Ҵ� ����
        printf("���� ���� �޸� �Ҵ翡 �����߽��ϴ�.\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < NUM_WALLS; i++) {
        int x, y;

        //���ƴ��� Ȯ��
        bool overlap;
        do {
            x = rand() % (WIDTH - 2) + 1;
            y = rand() % (HEIGHT - 2) + 1;
            overlap = false;

            for (int j = 0; j < i; j++)
            {
                if (walls[j].x == x && walls[j].y == y)
                {
                    overlap = true;
                    break;
                }
            }
        } while (overlap || (abs(snake.x - x) < 15 && abs(snake.y - y) < 8)); // Check if wall is within 10x10 range of snake

        walls[i].x = x;
        walls[i].y = y;
        walls[i].shape = 'F';
    }
}

/* ���� ��ġ�� ���� �����ϱ�*/
void generateFruits()
{
    fruits = (struct Fruit*)malloc(NUM_FRUITS * sizeof(struct Fruit));

    //�� ������ȣ
    unsigned int seed2 = rand();

    if (fruits == NULL)
    {
        // ���� �޸� �Ҵ� ����
        printf("������ ���� �޸� �Ҵ翡 �����߽��ϴ�.\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < NUM_FRUITS; i++)
    {
        int x, y;

        //���ƴ��� Ȯ��
        bool overlap;
        do {
            x = rand() % (WIDTH - 2) + 1;
            y = rand() % (HEIGHT - 2) + 1;
            overlap = false;

            for (int j = 0; j < i; j++)
            {
                if (fruits[j].x == x && fruits[j].y == y)
                {
                    overlap = true;
                    break;
                }
            }

            for (int j = 0; j < NUM_WALLS; j++)
            {
                if (walls[j].x == x && walls[j].y == y)
                {
                    overlap = true;
                    break;
                }
            }

        } while (overlap || (abs(snake.x - x) < 15 && abs(snake.y - y) < 8)); // Check if fruit is within 10x10 range of snake

        fruits[i].x = x;
        fruits[i].y = y;
        fruits[i].shape = 'F';
    }
}

/* �񵿱�� ABCD���� ������*/
DWORD WINAPI updateFruitShapes(LPVOID arg)
{
    int currentIndex = 0;

    while (1)
    {
        for (int i = 0; i < NUM_FRUITS; i++)
        {
            fruits[i].shape = 'A' + currentIndex % 3;
            currentIndex++;
        }

        Sleep(1000); // 1�� ���
    }

    return 0;
}

/* �÷��� ȭ�鿡�� �� �׸��� üũ�Ϸ���*/
bool isWallInArray(int x, int y, struct Wall* walls, int numWalls)
{
    for (int i = 0; i < numWalls; i++)
    {
        if (walls[i].x == x && walls[i].y == y)
        {
            return true;
        }
    }

    return false;
}

/* �÷��� ȭ�鿡�� ���� �׸��� üũ�Ϸ���*/
bool isFruitInArray(int x, int y, struct Fruit* fruits, int numFruitss)
{
    for (int i = 0; i < numFruitss; i++)
    {
        if (fruits[i].x == x && fruits[i].y == y)
        {
            return true;
        }
    }

    return false;
}

/* ���� �浹 ����*/
void handleFruitCollision()
{
    for (int i = 0; i < NUM_FRUITS; i++)
    {
        if (snake.x == fruits[i].x && snake.y == fruits[i].y)
        {
            // �浹�� ������ �� ������ �ʱ�ȭ�Ͽ� ����
            fruits[i].x = -1;
            fruits[i].y = -1;
            Progress++;

            // ���� ���̸� ������Ŵ
            tailLength++;
            if (fruits->shape == 'A')
            {
                A++;
                Hakjum += 4;
            }
            else if (fruits->shape == 'B')
            {
                B++;
                Hakjum += 3;
            }
            else if (fruits->shape == 'C')
            {
                C++;
                Hakjum += 2;
            }
            break;
        }
    }
}

/* �� �浹 ����*/
void handleWallCollision()
{
    for (int i = 0; i < NUM_WALLS; i++)
    {
        if (snake.x == walls[i].x && snake.y == walls[i].y)
        {
            printf("  �� F ��!!");
            Sleep(2500);
            system("cls");
            ClearBuffer();
            gameState = 4;
            break;
        }
    }
}


/* ���۸� �ѹ��� �׸��� ���� ���� �ȿ� ���� �ִ� �Լ�*/
void InputBuffer()
{

    if (gameState == 0) // ���� �޴� ȭ��
    {
        WriteToBuffer(27, 7, "_______________");
        WriteToBuffer(26, 4, "    ���� ����");
        WriteToBuffer(30, 9, "���� ����");
        WriteToBuffer(30, 11, "���� ����");
        WriteToBuffer(30, 13, "���� ����");
        WriteToBuffer(33, 15, "�ɼ�");
        WriteToBuffer(27, 17, "---------------");
        WriteToBuffer(2, 17, "W/S : ��/�Ʒ�");
        WriteToBuffer(2, 18, "Ent : ����");



        WriteToBuffer(28, 9, "  ");
        WriteToBuffer(28, 11, "  ");
        WriteToBuffer(28, 13, "  ");
        WriteToBuffer(30, 15, "  ");
        if (menuSelect == 1)WriteToBuffer(28, 9, "��");
        if (menuSelect == 2)WriteToBuffer(28, 11, "��");
        if (menuSelect == 3)WriteToBuffer(28, 13, "��");
        if (menuSelect == 4)WriteToBuffer(30, 15, "��");

    }
    if (gameState == 1) // ���� ���� ȭ�� 
    {
        // ȭ�� ���� �ʱ�ȭ
        for (int i = 0; i < VIEW_WIDTH * VIEW_HEIGHT + VIEW_HEIGHT; i++)
        {
            ScreenBuffer[i] = ' ';
        }

        // ������ �׸���
        for (int i = 0; i < VIEW_HEIGHT; i++)
        {
            for (int j = 0; j < VIEW_WIDTH; j++)
            {
                int mapX = snake.x - (VIEW_WIDTH / 2) + j;
                int mapY = snake.y - (VIEW_HEIGHT / 2) + i;

                // �׵θ��� ���
                if (mapX < 0 || mapX >= WIDTH || mapY < 0 || mapY >= HEIGHT)
                {
                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = '~'; // ���� �� �ٱ�
                }
                // ������ ����
                else if (i == 0 || i == VIEW_HEIGHT - 1 || j == 0 || j == VIEW_WIDTH - 1)
                {
                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = '*'; // �þ��� �׵θ�
                }
                // ������ ���
                else if (isFruitInArray(mapX, mapY, fruits, NUM_FRUITS))
                {
                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = fruits->shape; //�� ���
                }

                // ���� ��� 
                else if (isWallInArray(mapX, mapY, walls, NUM_WALLS))
                {
                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = walls->shape; //�� ���
                }


                else
                {
                    // ���� ��ġ
                    if (mapX == snake.x && mapY == snake.y)
                    {
                        ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = snakeHead;
                    }

                    // ������ ��ġ
                    else
                    {
                        int isTail = 0;
                        int isBody = 0;

                        for (int k = 0; k < tailLength; k++)
                        {
                            if (tail[k].x == mapX && tail[k].y == mapY)
                            {

                                if (k == 0)
                                {
                                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = 'o';  // ���� ����
                                }

                                else
                                {
                                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = 'o';  // ���� ����
                                    isBody = 1;
                                }

                                isTail = 1;
                                break;
                            }
                        }

                        if (!isTail && !isBody) {
                            ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = ' ';
                        }
                    }
                }
            }


            ScreenBuffer[i * (VIEW_WIDTH + 1) + VIEW_WIDTH] = '\n';

            WriteToBuffer(106, 16, "\n\n����     /      ");
            WriteToBuffer(113, 16, strLecture);
            WriteToBuffer(120, 16, strProgress);

            WriteToBuffer(123, 16, "\n\n���� ���  A :    B :    C : ");
            WriteToBuffer(138, 16, strA);
            WriteToBuffer(145, 16, strB);
            WriteToBuffer(152, 16, strC);



            // �׾����� ȭ�� ����� ���� �� �ϰ� �� �õ� ���� ������������ �ϰ� ���Ӽ��� �ϰ� ��


        }



    }

    if (gameState == 2)
    {
        WriteToBuffer(26, 4, "�ݥϰ��� �Դ� ���o");
        WriteToBuffer(18, 7, "�ҽ��� ���� ���Ͱ��� ������ �޾Ҵ�....");
        WriteToBuffer(13, 9, "??? : _(��_��)/ �̰� ���ϸ� ��ŵ��� �׾�� �Ť���");
        WriteToBuffer(18, 12, "����;;; ���� ���� ������ ��ġ����");
        WriteToBuffer(5, 16, "1. wasd�� ���� �����Ͽ� ����(A/B/C)�� �Ծ�ġ���� �Ѵ�.");
        WriteToBuffer(5, 17, "2. Ÿ�ֿ̹� ���� ���� ����� ������ �Դ°��� Point");
        WriteToBuffer(5, 18, "3. ������ �� ���� ���� �þ����� �ε����� ����!");
        WriteToBuffer(55, 2, "X : �ڷΰ���");
    }

    // �ɼ� ȭ��
    if (gameState == 3)
    {
        WriteToBuffer(27, 7, "_______________");
        WriteToBuffer(26, 4, "�ݥϰ��� �Դ� ���o");
        WriteToBuffer(30, 10, "���̵�");


        if (mode == 0)
        {
            WriteToBuffer(37, 10, "��");
            speed = 120;
        }
        if (mode == 1)
        {
            WriteToBuffer(37, 10, "��");
            speed = 70;
        }
        if (mode == 2)
        {
            WriteToBuffer(37, 10, "��");
            speed = 200;
        }

        WriteToBuffer(30, 13, "�� �Ӹ�");
        WriteToBuffer(38, 13, strHead);
        WriteToBuffer(27, 16, "---------------");

        WriteToBuffer(27, 10, "  ");
        WriteToBuffer(27, 13, "  ");

        if (menuSelect == 1)WriteToBuffer(27, 10, "��");
        if (menuSelect == 2)WriteToBuffer(27, 13, "��");
        WriteToBuffer(55, 2, "X : �ڷΰ���");
        WriteToBuffer(2, 17, "W/S : ��/�Ʒ�");
        WriteToBuffer(2, 18, "Ent : ����");

    }
    if (gameState == 4)
    {
        WriteToBuffer(17, 7, "___________________________________");
        if (jumsu < 1)
        {
            WriteToBuffer(20, 5, "������ 1���� �� ������ ����.....");
            WriteToBuffer(20, 13, "F����F����F����F����F����F����");
            WriteToBuffer(20, 14, "F����F����F����F����F����F����");
        }
        else if (jumsu < 2)
        {
            WriteToBuffer(18, 5, "�׷��� ������ ���Գ�.. F�� ���ߴ�");
            WriteToBuffer(20, 13, "D����D����D����D����D����D����");
            WriteToBuffer(20, 14, "D����D����D����D����D����D����");
        }
        else if (jumsu < 3)
        {
            WriteToBuffer(18, 5, "���� �ƽ�����, �� �й��ϵ��� �Ϸ�");
            WriteToBuffer(20, 13, "C����C����C����C����C����C����");
            WriteToBuffer(20, 14, "C����C����C����C����C����C����");
        }
        else if (jumsu < 3.5)
        {
            WriteToBuffer(18, 5, "��...���� ���ߴµ� ���� �ƽ����?");
            WriteToBuffer(20, 13, "B����B����B����B����B����B����");
            WriteToBuffer(20, 14, "B����B����B����B����B����B����");
        }
        else if (jumsu < 3.9)
        {
            WriteToBuffer(18, 5, "��û ������ �߱���, ���� ���߾�^^");
            WriteToBuffer(20, 13, "A����A����A����A����A����A����");
            WriteToBuffer(20, 14, "A����A����A����A����A����A����");
        }
        else if (jumsu == 4)
        {
            WriteToBuffer(18, 5, "....�ڳ� ���п��� �غ� ���� ����?");
            WriteToBuffer(16, 13, "�̰� ������?�̰� ������?�̰� ������?");
            WriteToBuffer(16, 14, "�̰� ������?�̰� ������?�̰� ������?");
        }
        WriteToBuffer(18, 9, "������ ����      /    ");
        WriteToBuffer(31, 9, strLecture);
        WriteToBuffer(39, 9, strProgress);
        WriteToBuffer(25, 10, "���  A :    B :    C : ");
        WriteToBuffer(35, 10, strA);
        WriteToBuffer(42, 10, strB);
        WriteToBuffer(49, 10, strC);


        WriteToBuffer(25, 11, "����");
        WriteToBuffer(31, 11, strJumsu);

        WriteToBuffer(17, 16, "-----------------------------------");

        WriteToBuffer(18, 18, "*** X Ű�� ������ ���� �޴��� ***");


    }
}