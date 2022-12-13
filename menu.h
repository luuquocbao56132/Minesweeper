#include <bits/stdc++.h>
#include <graphics.h>
#include "button.h"
#include "game.h"
#include "scoreboard.h"

// 18 103 72

class Menu{

public:
    int mode = 0;
    void EndAnounce(char* Text, int x, int y, int bomb){
        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != 4)
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);

        setbkcolor(COLOR(213,64,58)); setfillstyle(SOLID_FILL,COLOR(213,64,58));
        setcolor(WHITE);
        //Khung nen xanh
//        setfillstyle(SOLID_FILL,COLOR(18,103,72)); bar(100,300,700,500);
        //Dong thong bao
        bar(900,100,1100,200);
        outtextxy(1000,150,Text);

//        setfillstyle(SOLID_FILL,COLOR(223,134,33)); bar(180,395,320,445);
        Button Restart_button = Button(1000,700,150,50,COLOR(223,134,33),"Restart");
        Button Home_button = Button(1000,600,150,50,COLOR(223,134,33),"Home");
        Home_button.drawButton();
//
////        setfillstyle(SOLID_FILL,COLOR(223,134,33)); bar(470,395,630,445);
        Restart_button.drawButton();

        while (1){
            if (Home_button.checkMousein()){startMenu(); return;}
            if (Restart_button.checkMousein()){Newgame(x,y,bomb); return;}
            delay(25);
        }
    }

    void playgame(Game game, int x, int y, int bomb){
        int status = game.play();

        if (status == 1)EndAnounce("You win!",x,y,bomb); else
        if (status == 0){
            game.clearfile();
            int st = game.printallBomb();
            if (st == 2)startMenu(); else
            if (st == 3)Newgame(x,y,bomb);
            EndAnounce("You lose!",x,y,bomb);
        }
        else if (status == 2)startMenu(); else
        if (status == 3)Newgame(x,y,bomb);
    }

    bool Loadgame(){
        ifstream fi; fi.open("save\\game.log");

        int width, height, numBomb, mode, timeLast;

        if (!(fi >> width >> height >> numBomb >> mode)) return 0;

        Game game = Game(width,height,numBomb,mode);
        game.firstLeftclick = 0; game.flagTime = 0;
//debug load game
        forw(i,1,width,1) forw(j,1,height,1) {
            int x, openClose = 0, isBomb = 0, Flag = 0;
            fi >> x;
            cout << x << " ";
            while (x){
                if (x&1)Flag = 1, --game.Flagleft; x >>= 1;
                if (x&1)isBomb = 1; x >>= 1;
                if (x&1)openClose = 1, --game.closeBox; x >>= 1;
            }
            game.boxBomb[i][j].Flag = Flag;
            game.boxBomb[i][j].isBomb = isBomb;
            game.boxBomb[i][j].openClose = openClose;
        }

        forw(i,1,width,1) forw(j,1,height,1)
            fi >> game.boxBomb[i][j].num;

        fi.close(); fi.open("save\\time.log");
        fi >> timeLast; game.startTime = time(NULL) - timeLast; game.duration = timeLast;
        fi.close();

        game.printBoard();
        playgame(game, width, height, numBomb);
    }

    void Newgame(int x, int y, int bomb){
        Game game = Game(x,y,bomb,mode);
        game.printBoard();
        playgame(game, x, y, bomb);
    }

    void PrintScore(){
        Scoreboard score(2);
        Button Reset_button = Button(1100,600,150,50,COLOR(3,114,197),"Reset");
        Button Home_button = Button(1100,700,150,50,COLOR(3,114,197),"Home");
        Button Easy_button = Button(300,125,200,50,COLOR(60,148,39),"Easy");
        Button Medium_button = Button(600,125,200,50,COLOR(213,117,4),"Medium");
        Button Expert_button = Button(900,125,200,50,COLOR(204,54,47),"Expert");
        Expert_button.drawButton();
        Easy_button.drawButton();
        Medium_button.drawButton();
        Home_button.drawButton();
        Reset_button.drawButton();
        while (1){
            if (Easy_button.checkMousein()){mode = 0; score.print(mode);}
            if (Medium_button.checkMousein()){mode = 1; score.print(mode);}
            if (Expert_button.checkMousein()){mode = 2; score.print(mode);}
            if (Home_button.checkMousein())return;
            if (Reset_button.checkMousein()){
                score.reset(mode); score.print(mode);
            }
            delay(25);
        }
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
            if (easy_but.checkMousein()){mode = 0; Newgame(9,9,10); return;}
            if (medium_but.checkMousein()){mode = 1; Newgame(16,16,40); return;}
            if (expert_but.checkMousein()){mode = 2; Newgame(32,16,100); return; }
            if (loadgame_but.checkMousein()){if (Loadgame()) return; }
            if (score_but.checkMousein()){PrintScore(); startMenu(); return;}
            delay(25);
        }
    }
};
