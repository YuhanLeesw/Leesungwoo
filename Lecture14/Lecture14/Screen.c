#pragma once
#include "Screen.h"
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>


// 스네이크 헤드
char snakeHead = 'O';

void snakeHeadSetting()
{
    snakeHead++;
    if (snakeHead >= 'Z') snakeHead = 'A';
}

/* 화면 가로세로 설정*/
int screenWidth = 80;
int screenHeight = 25;

void setScreenSize(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
}

/*학점*/
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

    // 벽 생성
    generateWalls();
    // 과일 생성
    generateFruits();
    // 초기 꼬리 생성
    tailLength = 5; // 뱀의 길이 초기화
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



/* 커서위치 */
void setCursorPos(int x, int y)
{
    COORD pos = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

/* 배경, 글씨 색*/
void SetColor(unsigned short backgroundColor, unsigned short textColor)
{
    unsigned short color = textColor;
    color = color + (backgroundColor << 4);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* 메뉴화면 버퍼*/
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

/*버퍼 안에 글씨쓰기*/
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

/* 랜덤 위치에 벽 생성하기*/
void generateWalls()
{
    walls = (struct Wall*)malloc(NUM_WALLS * sizeof(struct Wall));


    if (walls == NULL)
    {
        // 동적 메모리 할당 실패
        printf("벽에 대한 메모리 할당에 실패했습니다.\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < NUM_WALLS; i++) {
        int x, y;

        //겹쳤는지 확인
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

/* 랜덤 위치에 학점 생성하기*/
void generateFruits()
{
    fruits = (struct Fruit*)malloc(NUM_FRUITS * sizeof(struct Fruit));

    //맵 고유번호
    unsigned int seed2 = rand();

    if (fruits == NULL)
    {
        // 동적 메모리 할당 실패
        printf("학점에 대한 메모리 할당에 실패했습니다.\n");
        exit(1);
    }

    srand(time(NULL));

    for (int i = 0; i < NUM_FRUITS; i++)
    {
        int x, y;

        //겹쳤는지 확인
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

/* 비동기로 ABCD학점 돌리기*/
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

        Sleep(1000); // 1초 대기
    }

    return 0;
}

/* 플레이 화면에서 벽 그릴때 체크하려고*/
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

/* 플레이 화면에서 학점 그릴때 체크하려고*/
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

/* 학점 충돌 감지*/
void handleFruitCollision()
{
    for (int i = 0; i < NUM_FRUITS; i++)
    {
        if (snake.x == fruits[i].x && snake.y == fruits[i].y)
        {
            // 충돌한 과일을 빈 값으로 초기화하여 제거
            fruits[i].x = -1;
            fruits[i].y = -1;
            Progress++;

            // 뱀의 길이를 증가시킴
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

/* 벽 충돌 감지*/
void handleWallCollision()
{
    for (int i = 0; i < NUM_WALLS; i++)
    {
        if (snake.x == walls[i].x && snake.y == walls[i].y)
        {
            printf("  응 F 다!!");
            Sleep(2500);
            system("cls");
            ClearBuffer();
            gameState = 4;
            break;
        }
    }
}


/* 버퍼를 한번에 그리기 위해 버퍼 안에 문자 넣는 함수*/
void InputBuffer()
{

    if (gameState == 0) // 메인 메뉴 화면
    {
        WriteToBuffer(27, 7, "_______________");
        WriteToBuffer(26, 4, "    게임 제목");
        WriteToBuffer(30, 9, "게임 시작");
        WriteToBuffer(30, 11, "게임 설명");
        WriteToBuffer(30, 13, "게임 종료");
        WriteToBuffer(33, 15, "옵션");
        WriteToBuffer(27, 17, "---------------");
        WriteToBuffer(2, 17, "W/S : 위/아래");
        WriteToBuffer(2, 18, "Ent : 선택");



        WriteToBuffer(28, 9, "  ");
        WriteToBuffer(28, 11, "  ");
        WriteToBuffer(28, 13, "  ");
        WriteToBuffer(30, 15, "  ");
        if (menuSelect == 1)WriteToBuffer(28, 9, "▶");
        if (menuSelect == 2)WriteToBuffer(28, 11, "▶");
        if (menuSelect == 3)WriteToBuffer(28, 13, "▶");
        if (menuSelect == 4)WriteToBuffer(30, 15, "▶");

    }
    if (gameState == 1) // 게임 진행 화면 
    {
        // 화면 버퍼 초기화
        for (int i = 0; i < VIEW_WIDTH * VIEW_HEIGHT + VIEW_HEIGHT; i++)
        {
            ScreenBuffer[i] = ' ';
        }

        // 게임판 그리기
        for (int i = 0; i < VIEW_HEIGHT; i++)
        {
            for (int j = 0; j < VIEW_WIDTH; j++)
            {
                int mapX = snake.x - (VIEW_WIDTH / 2) + j;
                int mapY = snake.y - (VIEW_HEIGHT / 2) + i;

                // 테두리인 경우
                if (mapX < 0 || mapX >= WIDTH || mapY < 0 || mapY >= HEIGHT)
                {
                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = '~'; // 게임 판 바깥
                }
                // 게임판 내부
                else if (i == 0 || i == VIEW_HEIGHT - 1 || j == 0 || j == VIEW_WIDTH - 1)
                {
                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = '*'; // 시야의 테두리
                }
                // 과일인 경우
                else if (isFruitInArray(mapX, mapY, fruits, NUM_FRUITS))
                {
                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = fruits->shape; //뱀 모양
                }

                // 벽인 경우 
                else if (isWallInArray(mapX, mapY, walls, NUM_WALLS))
                {
                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = walls->shape; //벽 모양
                }


                else
                {
                    // 뱀의 위치
                    if (mapX == snake.x && mapY == snake.y)
                    {
                        ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = snakeHead;
                    }

                    // 꼬리의 위치
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
                                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = 'o';  // 뱀의 몸통
                                }

                                else
                                {
                                    ScreenBuffer[i * (VIEW_WIDTH + 1) + j] = 'o';  // 뱀의 꼬리
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

            WriteToBuffer(106, 16, "\n\n과제     /      ");
            WriteToBuffer(113, 16, strLecture);
            WriteToBuffer(120, 16, strProgress);

            WriteToBuffer(123, 16, "\n\n과제 등급  A :    B :    C : ");
            WriteToBuffer(138, 16, strA);
            WriteToBuffer(145, 16, strB);
            WriteToBuffer(152, 16, strC);



            // 죽었을때 화면 재시작 같은 거 하고 맵 시드 말고 랜덤생성으로 하고 게임설명 하고 끝


        }



    }

    if (gameState == 2)
    {
        WriteToBuffer(26, 4, "◎Ο과제 먹는 뱀οo");
        WriteToBuffer(18, 7, "불쌍한 뱀은 마귀같은 과제를 받았다....");
        WriteToBuffer(13, 9, "??? : _(▤_▤)/ 이거 못하면 당신들은 죽어야 돼ㅋㅋ");
        WriteToBuffer(18, 12, "ㅎㅎ;;; 뱀을 도와 과제를 해치우자");
        WriteToBuffer(5, 16, "1. wasd로 뱀을 조작하여 과제(A/B/C)를 먹어치워야 한다.");
        WriteToBuffer(5, 17, "2. 타이밍에 맞춰 높은 등급의 과제를 먹는것이 Point");
        WriteToBuffer(5, 18, "3. 과제를 할 수록 몸이 늘어지니 부딪히지 말것!");
        WriteToBuffer(55, 2, "X : 뒤로가기");
    }

    // 옵션 화면
    if (gameState == 3)
    {
        WriteToBuffer(27, 7, "_______________");
        WriteToBuffer(26, 4, "◎Ο과제 먹는 뱀οo");
        WriteToBuffer(30, 10, "난이도");


        if (mode == 0)
        {
            WriteToBuffer(37, 10, "중");
            speed = 120;
        }
        if (mode == 1)
        {
            WriteToBuffer(37, 10, "상");
            speed = 70;
        }
        if (mode == 2)
        {
            WriteToBuffer(37, 10, "하");
            speed = 200;
        }

        WriteToBuffer(30, 13, "뱀 머리");
        WriteToBuffer(38, 13, strHead);
        WriteToBuffer(27, 16, "---------------");

        WriteToBuffer(27, 10, "  ");
        WriteToBuffer(27, 13, "  ");

        if (menuSelect == 1)WriteToBuffer(27, 10, "▶");
        if (menuSelect == 2)WriteToBuffer(27, 13, "▶");
        WriteToBuffer(55, 2, "X : 뒤로가기");
        WriteToBuffer(2, 17, "W/S : 위/아래");
        WriteToBuffer(2, 18, "Ent : 선택");

    }
    if (gameState == 4)
    {
        WriteToBuffer(17, 7, "___________________________________");
        if (jumsu < 1)
        {
            WriteToBuffer(20, 5, "평점이 1점도 안 나오면 ㅋㅋ.....");
            WriteToBuffer(20, 13, "F학점F학점F학점F학점F학점F학점");
            WriteToBuffer(20, 14, "F학점F학점F학점F학점F학점F학점");
        }
        else if (jumsu < 2)
        {
            WriteToBuffer(18, 5, "그래도 학점은 나왔네.. F는 면했다");
            WriteToBuffer(20, 13, "D학점D학점D학점D학점D학점D학점");
            WriteToBuffer(20, 14, "D학점D학점D학점D학점D학점D학점");
        }
        else if (jumsu < 3)
        {
            WriteToBuffer(18, 5, "많이 아쉽구나, 더 분발하도록 하렴");
            WriteToBuffer(20, 13, "C학점C학점C학점C학점C학점C학점");
            WriteToBuffer(20, 14, "C학점C학점C학점C학점C학점C학점");
        }
        else if (jumsu < 3.5)
        {
            WriteToBuffer(18, 5, "흠...뭔가 잘했는데 조금 아쉬운걸?");
            WriteToBuffer(20, 13, "B학점B학점B학점B학점B학점B학점");
            WriteToBuffer(20, 14, "B학점B학점B학점B학점B학점B학점");
        }
        else if (jumsu < 3.9)
        {
            WriteToBuffer(18, 5, "엄청 열심히 했구나, 아주 잘했어^^");
            WriteToBuffer(20, 13, "A학점A학점A학점A학점A학점A학점");
            WriteToBuffer(20, 14, "A학점A학점A학점A학점A학점A학점");
        }
        else if (jumsu == 4)
        {
            WriteToBuffer(18, 5, "....자네 대학원생 해볼 생각 없나?");
            WriteToBuffer(16, 13, "이걸 성공해?이걸 성공해?이걸 성공해?");
            WriteToBuffer(16, 14, "이걸 성공해?이걸 성공해?이걸 성공해?");
        }
        WriteToBuffer(18, 9, "제출한 과제      /    ");
        WriteToBuffer(31, 9, strLecture);
        WriteToBuffer(39, 9, strProgress);
        WriteToBuffer(25, 10, "등급  A :    B :    C : ");
        WriteToBuffer(35, 10, strA);
        WriteToBuffer(42, 10, strB);
        WriteToBuffer(49, 10, strC);


        WriteToBuffer(25, 11, "평점");
        WriteToBuffer(31, 11, strJumsu);

        WriteToBuffer(17, 16, "-----------------------------------");

        WriteToBuffer(18, 18, "*** X 키를 눌러서 메인 메뉴로 ***");


    }
}