#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include "Screen.h"


// 방향
enum Direction { UP, DOWN, LEFT, RIGHT };

// 게임 상태
int gameOver;
int selectMenu;
// 뱀의 이동 방향
enum Direction dir;

void Setup();
int DrawBuffer();
void Input();
void Logic();
void Update();


int main() {
    unsigned long time_end = GetTickCount64();
    unsigned long deltaTime = GetTickCount64();
    Setup();
    while (!gameOver) {
        Update();
        DrawBuffer();
        deltaTime = GetTickCount64() - time_end;
        time_end = GetTickCount64();
        if (deltaTime < 16)
            Sleep(16 - deltaTime);

        if (deltaTime != 0)
            //printf("time : %d \nfps :%d\n", deltaTime, 1000 / deltaTime);
            Input();
        Logic();

        // 게임 속도 조절 (Sleep 함수는 windows.h에 포함되어 있습니다.)
        Sleep(speed);
    }
    return 0;
}


// 초기화
void Setup() {

    gameState = 0;
    gameOver = 0;
    dir = RIGHT;
    //ReSet();

    // 게임판 초기화
    setScreenSize(70, 20);

    ClearBuffer();
    // memset(ScreenBuffer, '\0', sizeof(ScreenBuffer));

    // 뱀의 초기 위치
    snake.x = WIDTH / 2;
    snake.y = HEIGHT / 2;


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


    HANDLE thread;
    DWORD threadId;
    srand(time(NULL));

    // 쓰레드 생성
    thread = CreateThread(NULL, 0, updateFruitShapes, NULL, 0, &threadId);
    if (thread == NULL) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

}
void Update()
{
    InputBuffer();
}

int DrawBuffer()
{
    // 화면 버퍼 출력
    setCursorPos(0, 0);
    printf("%s", ScreenBuffer);
    return 0;
}

// 입력 처리
void Input() {
    if (gameState == 0)
    {
        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                selectMenu -= 1;
                if (selectMenu <= 0) selectMenu = 4;
                break;
            case 's':
                selectMenu += 1;
                if (selectMenu == 5) selectMenu = 1;
                break;
            case 'W':
                selectMenu -= 1;
                if (selectMenu <= 0) selectMenu = 4;
                break;
            case 'S':
                selectMenu += 1;
                if (selectMenu == 5) selectMenu = 1;
                break;

                gameOver = 1;
                break;
            case 13:
                if (selectMenu == 1)
                {
                    dir = RIGHT;
                    gameState = 1;
                    system("cls");
                }
                else if (selectMenu == 2)
                {
                    gameState = 2;
                    ClearBuffer();
                }
                else if (selectMenu == 3) gameOver = 1;
                else if (selectMenu == 4)
                {
                    gameState = 3;
                    ClearBuffer();

                }
                break;
            }
        }
    }
    if (gameState == 1)
    {
        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'x':
                gameOver = 1;
                break;
            case 'W':
                dir = UP;
                break;
            case 'S':
                dir = DOWN;
                break;
            case 'A':
                dir = LEFT;
                break;
            case 'D':
                dir = RIGHT;
                break;
            case 'X':
                gameOver = 1;
                break;
            }
        }
    }
    if (gameState == 2)
    {
        if (_kbhit()) {
            switch (_getch()) {
            case 'x':
                gameState = 0;
                ClearBuffer();
                break;
            case 'X':
                gameState = 0;
                ClearBuffer();
                break;
            }
        }
    }
    if (gameState == 3)
    {

        if (_kbhit()) {
            switch (_getch()) {
            case 'w':
                selectMenu -= 1;
                if (selectMenu <= 0) selectMenu = 2;
                break;
            case 's':
                selectMenu += 1;
                if (selectMenu >= 3) selectMenu = 1;
                break;
            case 'x':
                gameState = 0;
                selectMenu = 4;
                ClearBuffer();
                break;
            case 'W':
                selectMenu -= 1;
                if (selectMenu <= 0) selectMenu = 2;
                break;
            case 'S':
                selectMenu += 1;
                if (selectMenu >= 3) selectMenu = 1;
                break;
            case 'X':
                gameState = 0;
                selectMenu = 4;
                ClearBuffer();
                break;
            case 13:
                if (selectMenu == 1)
                {
                    mode++;
                    if (mode >= 3) mode = 0;
                    ClearBuffer();
                }
                else if (selectMenu == 2)
                {
                    snakeHeadSetting();
                    ClearBuffer();
                }
            }
        }
    }
    if (gameState == 4)
    {
        if (_kbhit()) {
            switch (_getch()) {

            case 'x':
                ReSet();
                break;

            case 'X':
                ReSet();
                break;
            }
        }

    }
}

// 게임 로직 업데이트
void Logic() {
    // 메인 메뉴
    if (gameState == 0 || gameState == 3)
    {
        //입력받은 키보드값 화면 업데이트
        switch (selectMenu)
        {
        case 1:
            menuSelect = 1;

            break;
        case 2:
            menuSelect = 2;

            break;
        case 3:
            menuSelect = 3;

            break;

        case 4:
            menuSelect = 4;

            break;
        default:
            break;
        }
        if (mode == 0)
        {
            speed = 100;
        }
        if (mode == 1)
        {
            speed = 50;
        }
        if (mode == 2)
        {
            speed = 200;
        }
    }

    if (gameState == 1)
    {
        memset(ScreenBuffer, '\0', sizeof(ScreenBuffer));

        stringA();
        stringB();
        stringC();
        stringLecture();
        stringProgress();
        Jumsu();
        stringJumsu();
        // 꼬리 위치 업데이트
        Snake prevTail = tail[tailLength];
        for (int i = tailLength - 1; i > 0; i--) {
            tail[i] = tail[i - 1];
        }
        tail[0] = snake;

        // 뱀의 이동
        switch (dir) {
        case UP:
            snake.y = snake.y - 1;
            break;
        case DOWN:
            snake.y = snake.y + 1;
            break;
        case LEFT:
            snake.x = snake.x - 1;
            break;
        case RIGHT:
            snake.x = snake.x + 1;
            break;
        }

        // 벽에 부딪혔는지 체크
        if (snake.x < 0 || snake.x >= WIDTH || snake.y < 0 || snake.y >= HEIGHT)
        {
            printf("  으아아아아아앙 아프(F) 다!!");
            Sleep(2500);
            system("cls");
            ClearBuffer();
            gameState = 4;
        }
        // 자기 자신에게 부딪혔는지 체크
        for (int i = 0; i < tailLength; i++) {
            if (snake.x == tail[i].x && snake.y == tail[i].y)
            {
                printf("  으아아아아아앙 아프(F) 다!!");
                Sleep(2500);
                system("cls");
                ClearBuffer();
                gameState = 4;
                break;
            }
        }

        handleFruitCollision();
        handleWallCollision();
    }

    if (gameState == 3)
    {
        stringHead();
    }
}

