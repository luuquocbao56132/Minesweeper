#include <graphics.h>
//#include "game.h"
#include "menu.h"
#include <windows.h>
#include <bits/stdc++.h>
// check debug outtext, in test board ban dau

void HideConsole()
{
    ::ShowWindow(::GetConsoleWindow(), SW_HIDE);
}

int main(){
    //HideConsole();
    srand(time(NULL));
    initwindow(1200, 800, "Minesweeper");
    Menu menu;
    menu.startMenu();
    getch();
    closegraph();
}


