#include <bits/stdc++.h>
#include <graphics.h>
#include "button.h"
#include "game.h"

// 18 103 72

class Menu{

public:

    void EndAnounce(char* Text, int x, int y, int bomb){
        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != 4)
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);

        setbkcolor(COLOR(213,64,58)); setcolor(WHITE);
        //Khung nen xanh
        setfillstyle(SOLID_FILL,COLOR(18,103,72)); bar(100,300,700,500);
        //Dong thong bao
        setfillstyle(SOLID_FILL,COLOR(213,64,58)); bar(100,300,700,350);
        outtextxy(400,330,Text);

//        setfillstyle(SOLID_FILL,COLOR(223,134,33)); bar(180,395,320,445);
        Button Home_button = Button(250,425,150,50,COLOR(223,134,33),"Home");
        Home_button.drawButton();

//        setfillstyle(SOLID_FILL,COLOR(223,134,33)); bar(470,395,630,445);
        Button Restart_button = Button(550,425,150,50,COLOR(223,134,33),"Restart");
        Restart_button.drawButton();

        while (1){
            if (Home_button.checkMousein()){startMenu(); return;}
            if (Restart_button.checkMousein()){Newgame(x,y,bomb); return;}
            delay(25);
        }
    }

    void Newgame(int x, int y, int bomb){
        Game game = Game(x,y,bomb);
        bool status = game.play();

        if (status)EndAnounce("You Win!",x,y,bomb); else EndAnounce("You Lose!",x,y,bomb);
    }

    void startMenu(){
        //print menu
        Button easy_but = Button(250,300,250,60,COLOR(60,148,39), "Easy 9x9");
        Button medium_but = Button(600,300,250,60,COLOR(213,117,4), "Medium 16x16");
        Button expert_but = Button(950,300,250,60,COLOR(204,54,47), "Expert 30x16");
        Button loadgame_but = Button(600,450,250,60,COLOR(3,114,197),"Load game");
        Button score_but = Button(600,600,250,60,COLOR(3,114,197),"Scoreboard");

        setbkcolor(COLOR(18,103,72));
        cleardevice();
        setfillstyle(SOLID_FILL,COLOR(13,72,51));
        bar(0,0,1200,135);
        settextstyle(BOLD_FONT,0,6);
        setbkcolor(COLOR(13,72,51));
        settextjustify(CENTER_TEXT, CENTER_TEXT);
        outtextxy(600,80,"Minesweeper");

        easy_but.drawButton();
        medium_but.drawButton();
        expert_but.drawButton();

        loadgame_but.drawButton();
        score_but.drawButton();

        // check what user doing
        while(1){
            if (easy_but.checkMousein()){Newgame(9,9,10); return;}
            if (medium_but.checkMousein()){Newgame(16,16,40); return;}
            if (expert_but.checkMousein()){Newgame(32,16,100); return; }
//            if (loadgame_but.checkMousein()){Loadgame(); return; }
//            if (score_but.checkMousein()){PrintScore(); return; }
            delay(25);
        }
    }
};
