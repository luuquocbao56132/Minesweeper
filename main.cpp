#include <graphics.h>
//#include "game.h"
#include "menu.h"
#include <bits/stdc++.h>
// check debug outtext, in test board ban dau
int main(){
    srand(time(NULL));
    initwindow(1200, 800, "Minesweeper");
    Menu menu;
    menu.startMenu();
    //initBomb();
//    setbkcolor(LIGHTGRAY); cleardevice();
//    setcolor(WHITE);
    //forw(i,1,a,1) forw(i,1,b,1)cout << i;
    getch();
    closegraph();

}


