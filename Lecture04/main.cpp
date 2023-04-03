#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    while (1) 
    {
        
	    std::cout << "Input Key!!!" << std::endl;
        if (GetAsyncKeyState(VK_SPACE)||GetAsyncKeyState(VK_ESCAPE)) 
	{   
            break;
        }
	
    }

    return 0;
}

