#include <bits/stdc++.h>
#include <graphics.h>
#include "button.h"
#include "game.h"
#include "scoreboard.h"

class Menu{

public:
    int mode = 0;

    void clearmouse(){
        clearmouseclick(WM_LBUTTONDBLCLK);
        clearmouseclick(WM_LBUTTONDOWN);
        clearmouseclick(WM_RBUTTONDOWN);
    }

    void EndAnounce(char* Text, int x, int y, int bomb){
        clearmouse();
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
        Button Restart_button = Button(1000,700,150,50,COLOR(164, 113, 71),COLOR(255, 204, 165),"Restart");
        Button Home_button = Button(1000,600,150,50,COLOR(164, 113, 71),COLOR(255, 204, 165),"Home");
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
        cout << game.width << " " << game.height << endl;

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
        clearmouse();
        ifstream fi; fi.open("save\\game.log");

        int width, height, numBomb, mode, timeLast,ii=0;

        if (!(fi >> width >> height >> numBomb >> mode)) return 0;

        Game game = Game(width,height,numBomb,mode);
        game.firstLeftclick = 0; game.flagTime = 0;
//debug load game
        forw(i,1,width,1) forw(j,1,height,1) {
            int x, openClose = 0, isBomb = 0, Flag = 0;
            fi >> x;
            while (x){
                if (x&1)Flag = 1, --game.Flagleft; x >>= 1;
                if (x&1){
                    isBomb = 1;
                    game.Stt[++ii] = {i,j}; game.Ran_first.push_back(ii);
                }
                x >>= 1;
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
        return 1;
    }

    void Newgame(int x, int y, int bomb){
        clearmouse();
        Game game = Game(x,y,bomb,mode);
        game.printBoard();
        playgame(game, x, y, bomb);
    }

    void PrintScore(){
        Scoreboard score(2);
        clearmouse();
        Button Reset_button = Button(1100,600,150,50,COLOR(164, 113, 71),COLOR(255, 204, 165),"Reset");
        Button Home_button = Button(1100,700,150,50,COLOR(164, 113, 71),COLOR(255, 204, 165),"Home");
        Button Easy_button = Button(300,125,200,50,COLOR(207, 158, 78),COLOR(255, 204, 165),"Easy");
        Button Medium_button = Button(500,125,200,50,COLOR(150, 103, 39),COLOR(255, 204, 165),"Medium");
        Button Expert_button = Button(700,125,200,50,COLOR(123, 73, 9),COLOR(255, 204, 165),"Expert");
        Button Master_button = Button(900,125,200,50,COLOR(79, 50, 24),COLOR(255, 204, 165),"Master");
        Expert_button.drawButton();
        Easy_button.drawButton();
        Medium_button.drawButton();
        Master_button.drawButton();
        Home_button.drawButton();
        Reset_button.drawButton();
        while (1){
            if (Easy_button.checkMousein()){mode = 0; score.print(mode);}
            if (Medium_button.checkMousein()){mode = 1; score.print(mode);}
            if (Expert_button.checkMousein()){mode = 2; score.print(mode);}
            if (Master_button.checkMousein()){mode = 3; score.print(mode);}
            if (Home_button.checkMousein()){startMenu(); return;}
            if (Reset_button.checkMousein()){
                score.reset(mode); score.print(mode);
            }
            delay(25);
        }
    }

    int checkBomb(int wid, int hei, int bom){
        if (bom > wid*hei)bom = wid*hei / 5;
        return max(bom,0);
    }

    void correctSta(int i, int chiso[]){
        if (i < 3){
            chiso[i] = max(chiso[i],1);
            chiso[i] = min(chiso[i],32);
        }
        chiso[3] = checkBomb(chiso[1],chiso[2],chiso[3]);
    }

    void printCusnum(int i, string T){
        setbkcolor(COLOR(189, 113, 72)); setcolor(COLOR(255, 204, 165));
        cout << i << ": " << T << endl;
        if (i == 1)outtextxy(900,255,&T[0]);
        if (i == 2)outtextxy(900,350,&T[0]);
        if (i == 3)outtextxy(900,445,&T[0]);
    }

    void drawCusnum(int left, int top, int right, int bot, string T){
        setfillstyle(SOLID_FILL,COLOR(189, 113, 72)); setbkcolor(COLOR(189, 113, 72)); setcolor(COLOR(255, 204, 165));
        bar(left,top,right,bot);
        outtextxy((left + right)>>1,((top+bot)>>1)+5,&T[0]);
    }

    void duyetInputcustom(char c, int chiso[], int cusSta){
        int chisoF[4] = {chiso[0],chiso[1],chiso[2],chiso[3]};
        if ((int)c == 8) chiso[cusSta] /= 10;
        else {
            chiso[cusSta] *= 10; chiso[cusSta] += (int)(c-'0');
            if (cusSta < 3 && chiso[cusSta] > 32)chiso[cusSta] /= 10;
            if (cusSta == 3 && chiso[cusSta] > 999)chiso[cusSta] /= 10;
        }
        chiso[3] = checkBomb(chiso[1],chiso[2],chiso[3]);
        cout << chiso[1] << " " << chiso[2] << " " << chiso[3] << endl;

        if (chiso[1] != chisoF[1])drawCusnum(800,230,1000,270,to_string(chiso[1]));
        if (chiso[2] != chisoF[2])drawCusnum(800,325,1000,365,to_string(chiso[2]));
        if (chiso[3] != chisoF[3])drawCusnum(800,420,1000,460,to_string(chiso[3]));
    }

    bool checkIn(int x, int y, int left, int top, int right, int bot)
    {return left <= x && x <= right && top <= y && y <= bot;}

    bool checkMousein(int left, int top, int right, int bot){
        if (!checkIn(mousex(), mousey(),left,top,right,bot)){return 0;}
        int x,y; getmouseclick(WM_LBUTTONDOWN,x,y);
        if (checkIn(x,y,left,top,right,bot))return 1;
        //drawButton();
        return 0;
    }

    void menuplay(){
        int chiso[4] = {0,9,9,10}, cusSta = 0;
        clearmouse();

        readimagefile("pics/background.gif",0,0,1200,800);
        Button easy_but = Button(330,250,250,60,COLOR(127, 84, 74), COLOR(255, 204, 165), "Easy 9x9");
        Button medium_but = Button(330,345,250,60,COLOR(127, 84, 74), COLOR(255, 204, 165),"Medium 16x16");
        Button expert_but = Button(330,440,250,60,COLOR(127, 84, 74), COLOR(255, 204, 165),"Expert 32x16");
        Button master_but = Button(330,535,250,60,COLOR(127, 84, 74), COLOR(255, 204, 165),"Master 32x32");
        Button Home_but = Button(900,640,250,60,COLOR(127, 84, 74), COLOR(255, 204, 165),"Home");
        Button Playcus_but = Button(900,535,250,60,COLOR(127, 84, 74), COLOR(255, 204, 165),"Play custom");

        easy_but.drawButton();
        medium_but.drawButton();
        expert_but.drawButton();
        master_but.drawButton();
        Home_but.drawButton();
        Playcus_but.drawButton();

        forw(i,1,3,1)printCusnum(i,to_string(chiso[i]));

        //width
        string st; setbkcolor(COLOR(127, 84, 74));
        setfillstyle(SOLID_FILL,COLOR(127, 84, 74));
        bar(650,220,1025,280);
        st = "Width";
        outtextxy(725,255,&st[0]);
        setfillstyle(SOLID_FILL,COLOR(189, 113, 72));
        bar(800,230,1000,270);

        //height
        setfillstyle(SOLID_FILL,COLOR(127, 84, 74));
        bar(650,315,1025,375);
        st = "Height";
        outtextxy(725,350,&st[0]);
        setfillstyle(SOLID_FILL,COLOR(189, 113, 72));
        bar(800,325,1000,365);

        //bomb
        setfillstyle(SOLID_FILL,COLOR(127, 84, 74));
        bar(650,410,1025,470);
        st = "Bomb";
        outtextxy(725,445,&st[0]);
        setfillstyle(SOLID_FILL,COLOR(189, 113, 72));
        bar(800,420,1000,460);

        setbkcolor(COLOR(189, 113, 72)); setcolor(COLOR(255, 204, 165));
        string T = "9"; outtextxy(900,255,&T[0]);
        T = "9"; outtextxy(900,350,&T[0]);
        T = "10"; outtextxy(900,445,&T[0]);

        while(1){
            if (kbhit()){
                char c = getch(); cout << "cusSta: " << cusSta << endl;
                if ((c < '0' || c > '9') && (int)c != 8)continue;
                cout << "c: " << (int)c << endl;
                if (cusSta)duyetInputcustom(c,chiso,cusSta);
            }
            if (easy_but.checkMousein()){mode = 0; Newgame(9,9,10); return;}
            if (medium_but.checkMousein()){mode = 1; Newgame(16,16,40); return;}
            if (expert_but.checkMousein()){mode = 2; Newgame(32,16,100); return; }
            if (master_but.checkMousein()){mode = 3; Newgame(32,32,200); return; }
            if (checkMousein(800,230,1000,270)){if (cusSta)correctSta(cusSta,chiso); cusSta = 1;}
            if (checkMousein(800,325,1000,365)){if (cusSta)correctSta(cusSta,chiso); cusSta = 2;}
            if (checkMousein(800,420,1000,460)){if (cusSta)correctSta(cusSta,chiso); cusSta = 3;}
            if (Playcus_but.checkMousein()){
                mode = 4;
                if (cusSta)correctSta(cusSta,chiso);
                printCusnum(1,to_string(chiso[1]));
                printCusnum(2,to_string(chiso[2]));
                printCusnum(3,to_string(chiso[3]));
                delay(200);
                Newgame(chiso[1],chiso[2],chiso[3]); return;
            }

            if (Home_but.checkMousein())return;
            delay(25);
        }
    }

    void startMenu(){
        //print menu
        clearmouse();

        Button play_but = Button(600,300,250,60,COLOR(127, 84, 74),COLOR(255, 204, 165),"Play");
        Button loadgame_but = Button(600,450,250,60,COLOR(127, 84, 74),COLOR(255, 204, 165),"Load game");
        Button score_but = Button(600,600,250,60,COLOR(127, 84, 74),COLOR(255, 204, 165),"Scoreboard");

        readimagefile("pics/background.gif",0,0,1200,800);

        loadgame_but.drawButton();
        play_but.drawButton();
        score_but.drawButton();

        // check what user doing
        while(1){
            if (play_but.checkMousein()){menuplay(); startMenu(); return; }
            if (loadgame_but.checkMousein()){if (Loadgame()) return; }
            if (score_but.checkMousein()){PrintScore(); startMenu(); return;}
            delay(25);
        }
    }
};
