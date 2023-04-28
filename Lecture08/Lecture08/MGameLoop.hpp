#pragma once // #define _IS_THIS_HEADER_INCLUDED

#define Key_ESC 27
#define Key_RIGHT 'd'
#define Key_LEFT 'a'
#define Key_ENTER 13

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

namespace MuSoeun
{
	void gotoxy(int x, int y) {
		//x, y ��ǥ ����
		COORD pos = { x,y };
		//Ŀ�� �̵�
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}

	class MGameLoop
	{
	public:

		bool isGameRunning = false;

		MGameLoop() {}
		~MGameLoop() {}

		void Initialize()
		{
			isGameRunning = true;
			gotoxy(0, 10);
			std::cout << ANSI_COLOR_MAGENTA "초기화 완료" << std::endl;
		}

		void Release()
		{
			gotoxy(0, 10);
			std::cout << ANSI_COLOR_MAGENTA "시스템 해제 완료" << std::endl;
		}

		void Update()
		{
			gotoxy(0, 10);
			std::cout << ANSI_COLOR_MAGENTA "업데이트중 완료" << std::endl;
			if (_kbhit())
			{

				keyEvent(_getch());
			}

		}
		void Render()
		{
			gotoxy(0, 10);
			std::cout << ANSI_COLOR_MAGENTA "렌더링 완료" << std::endl;
		}

		void Run()
		{
			Initialize();

			while (isGameRunning)
			{
				Update();
				
				Render();
			}

			Release();

		}

		void keyEvent(char KeyInput)
		{	
			static bool isMenuActive = false; //메뉴 활성화 여부
			static bool isChoosingYes = false; // "예" 선택 여부
			int a, b;
			switch (KeyInput)
			{
				
			case Key_LEFT:	//왼쪽 화살표키
				gotoxy(1, 7);
				std::cout << ANSI_COLOR_YELLOW" [예]" << std::endl;
				
				gotoxy(10, 7);
				std::cout << ANSI_COLOR_RESET" [아니요]" << std::endl;
				isMenuActive = true;
				break;
			case Key_RIGHT:	//오른쪽 화살표키
				gotoxy(10, 7);
				std::cout << ANSI_COLOR_YELLOW" [아니요]" << std::endl;
			
				gotoxy(1, 7);
				std::cout << ANSI_COLOR_RESET" [예]" << std::endl;
				isMenuActive = false;
				break;
				/* 27 : esc 고 게임 종료키 입니다.
				*  한번 눌렀을땐 일시정지
				*  두번 눌렀을땐 게임 종료
				*/
			case Key_ESC:
				if (!isMenuActive) { //메뉴가 활성화되지 않은 경우
					isMenuActive = true;
					isChoosingYes = true;

					gotoxy(2, 5);
					std::cout << ANSI_COLOR_RESET"종료하시겠습니까?\n" << std::endl;
					gotoxy(1, 7);
					std::cout << ANSI_COLOR_RESET" [예]" << std::endl;
					gotoxy(10, 7);
					std::cout << ANSI_COLOR_RESET" [아니요]" << std::endl;


					
				}//24일 8주차 과제
				else { // 메뉴가 활성화된 경우
					if (isChoosingYes) {// "예"를 선택한 경우
						isGameRunning = false;
						return;
					}
					else {//"아니오"를 선택한 경우
						isMenuActive = false;
						gotoxy(2, 5);
						std::cout << "예를 선택하세요." << std::endl; // 메시지 지우기
						
					}
				}
				break;
			case Key_ENTER: //Enter 키
				if (isMenuActive) {
					if (isChoosingYes) {//"예"를 선택한 경우
						isGameRunning = false;
						return;
					}
					else { // "아니오"를 선택한 경우
						isMenuActive = false;
						gotoxy(1, 5);
						std::cout << "                    " << std::endl; // 메시지 지우기
					}
				}
				break;
				
				default:
				gotoxy(2, 5);
				break;
			}
		}
	};
}