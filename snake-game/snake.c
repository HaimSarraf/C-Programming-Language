#include <stdio.h>
#include <stdlib.h>

void clear_screen();

int main()
{


    return 0;
}

void clear_screen()
{
    #if defined(_WIN32)  //#ifdef _Win32
        system("cls");
    #else
        system("clear");
    #endif
}