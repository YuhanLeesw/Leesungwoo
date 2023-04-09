//#define DEBUG
#include<iostream>
#include<conio.h>
#include<Windows.h>


// game_state == 0 일때
int print_title_screen()
{
    std::cout << "******************************************" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*                                        *" << std::endl;
    std::cout << "*              지렁이 게임               *" << std::endl;
    std::cout << "*             (Snake  Bite)              *" << std::endl;

#ifdef DEBUG
    std::cout << "*            - 디버그 모드 -             *" << std::endl;
#else
    std::cout << "*                                        *" << std::endl;
#endif  
    std::cout << "*   1. 게임 시작                         *" << std::endl;
    std::cout << "*   2. 게임 설명                         *" << std::endl;
    std::cout << "*   3. 게임 랭킹 보기                    *" << std::endl;
    std::cout << "*   4. 게임 종료 (esc)                   *" << std::endl;
    std::cout << "******************************************" << std::endl;

    return 0;
}

void gotoxy(int x, int y) {
    //x, y 좌표 설정
    COORD pos = { x,y };
    //커서 이동
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int print_game_screen(int width,int height  )
{
    char** stage = new char* [height];
    for (int i = 0; i < height; i++)
    {
        stage[i] = new char[width];
        memset(stage[i], 0, width);
    }

    // 스테이지 벽 그리기
    for (int i = 0; i < width; i++)
    {
        stage[0][i] = '#';
        stage[height - 1][i] = '#';
    }
    for (int i = 0; i < height; i++)
    {
        stage[i][0] = '#';
        stage[i][width - 1] = '#';
    }

    // 스테이지 출력
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (stage[i][j] == 0)
                std::cout << " ";
            else
                std::cout << stage[i][j];
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < height; i++)
    {
        delete[] stage[i];
    }
    delete[] stage;

    return 0;

}



// game_state == 2 일때
int print_introduction_screen()
{
    std::cout << "******************************************" << std::endl;
    std::cout << "타이틀화면으로 돌아갈까요? (Y/N)" << std::endl;
    return 0;
}

int main()
{

    int game_state = 0;
    int is_game_running = 1;

    while (is_game_running)
    {
        char key_input = '0';
        switch (game_state)
        {
        case 0:
            print_title_screen();
            key_input = _getch();
            switch (key_input)
            {
            case '1':
                int width, height;
                std::cout << "스테이지 너비와 높이를 입력하세요: ";
                std::cin >> width >> height;
                
                print_game_screen(width, height); // 스테이지 출력
                
                break;
                
            case '2':
                game_state = 2;
                break;
            case '3':
                break;
            case '4':
                is_game_running = 0;
                break;
            case 27:
                is_game_running = 0;
                break;
            default:
                break;
            }
            break;
        case 1:
            print_game_screen(10,10);
            key_input = _getch();
            break;
        case 2:
            print_introduction_screen();
            key_input = _getch();
            switch (key_input)
            {
            case 'y':
                game_state = 0;
                break;
            case 'n':
                
                break;
            default:
                break;
            }
            break;

        default:
            break;
        }


    }

    return 0;
}


//int print_title_screen()
//{
//	std::cout << "**********************************" << std::endl;
//	std::cout << "*                                *" << std::endl;
//	std::cout << "*                                *" << std::endl;
//	std::cout << "*          지렁이 게임           *" << std::endl;
//	std::cout << "*         (Snake Bite)           *" << std::endl;
//#ifdef DEBUG
//	std::cout << "*        - 디버그 모드 -         *" << std::endl;
//#else
//	std::cout << "*                                *" << std::endl;
//#endif
//	std::cout << "*   1. 게임 시작                 *" << std::endl;
//	std::cout << "*   2. 게임 설명                 *" << std::endl;
//	std::cout << "*   3. 게임 랭킹 보기            *" << std::endl;
//	std::cout << "*   4. 게임 종료 (ESC)           *" << std::endl;
//	std::cout << "**********************************" << std::endl;
//	
//		return 0;
//}
//
//int pirnt_introduction_screnn()
//{
//	std::cout << "**********************************" << std::endl;
//	std::cout << "타이틀화면으로 돌아갈까요?(Y/N)   " << std::endl;
//	return 0;
//}
//
//void gotoxy(int x, int y)
//{	
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
//}
//int print_title_screen(int stage_width, int stage_height)
//{	
//	gotoxy(5,5);
//	
//	return;
//}
//int main()
//{
//	char InputKey;
//	int is_game_running = 1;
//	int game_state = 0;
//	print_title_screen();
//
//	while (is_game_running)
//	{
//		switch (game_state) {
//		case 0:
//			print_title_screen();
//			InputKey = _getch();
//			switch (InputKey)
//			{
//			case '1':
//				game_state = 1;
//				break;
//			case '2':
//				game_state = 2;
//				break;
//			case '3':
//				break;
//			case '4':
//				is_game_running = 0;
//				break;
//			case 27:
//				is_game_running = 0;
//				break;
//			default:
//				break;
//			}
//			break;
//		case 2:
//			pirnt_introduction_screnn();
//			InputKey = _getch();
//			switch (InputKey)
//			{
//			case 'y':
//				game_state = 0;
//				break;
//			case 'n':
//				break;
//			default:
//				break;
//			}
//			break;
//	
//		}
//	}
//		//while (1)
//		//{
//		//	//메인화면 출력 함수 호출
//		//	print_title_screen();
//
//		//	//4. 게임종료(esc)
//		//	InputKey = _getch();
//		//	while (1)
//		//	{
//		//		if (InputKey == 27 || InputKey == '4')
//		//		{
//		//			break;
//		//		}
//		//	}
//		//	break;
//
//		//	//2 게임 설명창 만들기
//		//	if (InputKey == '2')
//		//	{	
//		//		while (1)
//		//		{
//		//			pirnt_introduction_screnn();
//		//			InputKey = _getch();
//		//			if (InputKey == 'Y' || InputKey == 'y')
//		//			{
//		//				break;
//		//			}
//		//			else if (InputKey == 'N' || InputKey == 'n')
//		//			{
//		//				continue;						
//		//			}
//		//			else {
//		//				std::cout << "(Y/N)중에서만 입력해주세요." << std::endl;
//		//				continue;
//		//			}
//		//		}	
//		//	}
//		//	
//		//}
//		
//	return 0;
//}