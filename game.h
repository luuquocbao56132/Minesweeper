#ifndef _GAME_H_
#define _GAME_H_

#include <bits/stdc++.h>
#include <graphics.h>
#include "bomb.h"
#include "button.h"
//#include "menu.h"
#define pb push_back
#define fs first
#define sc second
#define forw(i, f, e, c) for (int (i) = (f); (i) <= (e); (i) += (c))

using namespace std;

typedef long long ll;
typedef long double ldb;
typedef pair <int,int> pp;
const int dx[] = {0,1,0,-1,1,1,-1,-1}, dy[] = {1,0,-1,0,-1,1,1,-1};
const char dir[] = {'R','D','L','U'};
const int mod = 1e9 + 7, base = 307;
const int MOD[] = {(int)1e9 + 2777, (int) 1e9 + 5277, (int) 1e9 + 8277};
const ll oo = 1e16;

//bool Loadgame(){
//    ifstream gfile("savegame\\game.log");
//
//    if (!(gfile >> height >> width >> numBomb)) return 0;
//
//    forw(i,0,height,1) forw(j,0,width,1) {
//        if (!(gfile >> b[i][j]))return 0;
//
//    }
//}

// background RGB(51,56,62) RGB(50,55,61)
// bar RGB(48,54,60) RGB(48,53,59)

class Game{
public:
    int LOSE = 0, Flagleft;
    bool flagTime = 1;
    int height, width, numBomb, numSquare, sizeBox, closeBox, startTime = 0, endTime, duration = 0;
    Bomb boxBomb[35][35];

    Button Restart_button = Button(1000,700,150,50,COLOR(223,134,33),"Restart");
    Button Home_button = Button(1000,600,150,50,COLOR(223,134,33),"Home");

    Game (int _width = 0, int _height = 0, int _numBomb = 0){
        height = _height; width = _width; numBomb = _numBomb; Flagleft = numBomb;
        numSquare = width * height; closeBox = numSquare;
        sizeBox = min(890 / width, 790 / height);
        cout << sizeBox << endl;
        initBoard();
    }

    void printBoard(){
        setbkcolor(bgColor); cleardevice();

        forw(i,1,width,1) forw (j,1,height,1)
            boxBomb[i][j].printBox();
    }

    void printTime(string TimePrint){
        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != 4)
            settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);
        setcolor(WHITE); setbkcolor(bgColor);
        outtextxy(1000,350,&TimePrint[0]);
    }

    void printFlagleft(){
        string res = to_string(abs(Flagleft));
        while (res.size() < 3)res = "0" + res;
        if (Flagleft < 0)res = "-" + res;

        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != 4)
            settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);
        setcolor(WHITE); setbkcolor(bgColor);
        outtextxy(1000,500,&res[0]);
    }

    void initBoard(){
        int ii = 0;
        pair <int,int> Stt[35*35];
        vector <int> Ran_first;

        cout << width << " " << height << endl;

        forw(i,1,width,1) forw(j,1,height,1){
            Stt[++ii] = {i,j};
            Ran_first.push_back(ii);
            boxBomb[i][j] = Bomb(0,0,0,i,j,sizeBox);
        }

        random_shuffle(Ran_first.begin(), Ran_first.end());
        forw(i,0,numBomb-1,1){
            int x = Stt[Ran_first[i]].fs, y = Stt[Ran_first[i]].sc;
            boxBomb[x][y].isBomb = 1;
//            boxBomb[x][y].openClose = 0; boxBomb[x][y].Flag = 1;

            forw(k,0,7,1){
                int xx = x + dx[k], yy = y + dy[k];
                boxBomb[xx][yy].num++;
            }
        }

        forw(j,1,height,1) {
            forw(i,1,width,1)cout << boxBomb[i][j].isBomb << " ";
            cout << '\n';
        }

        printBoard();
        setcolor(WHITE); setbkcolor(bgColor);
        outtextxy(1000,300,"TIME");
        printTime("0000");

        outtextxy(1000,450,"Bomb");
        printFlagleft();

        Home_button.drawButton();
//        setfillstyle(SOLID_FILL,COLOR(223,134,33)); bar(470,395,630,445);
        Restart_button.drawButton();
    }

    pp findBox(int coor_x, int coor_y){
        int x = -1,y = -1,l = 1, r = width;
        while (l <= r){
            int mid = (l + r) >> 1;
//            cout << boxBomb[l][1].left << " " << boxBomb[l][1].right << " " << boxBomb[r][1].left << " " << boxBomb[r][1].right << endl;
//            cout << boxBomb[mid][1].left << " " << boxBomb[mid][1].right << endl;
            if (coor_x >= boxBomb[mid][1].left && coor_x <= boxBomb[mid][1].right){
                x = mid; break;
            }
            if (coor_x < boxBomb[mid][1].right)r = mid - 1; else l = mid + 1;
        }

        cout << x << endl;

        l = 1; r = height;
        while (l <= r){
            int mid = (l + r) >> 1;
            cout << boxBomb[1][mid].top << " " << boxBomb[1][mid].bot << endl;
            if (coor_y >= boxBomb[1][mid].top && coor_y <= boxBomb[1][mid].bot){
                y = mid; break;
            }
            if (coor_y < boxBomb[1][mid].bot)r = mid - 1; else l = mid + 1;
        }

        cout << y << endl;

        if (x == -1 || y == -1)return make_pair(-1,-1);
        return make_pair(x,y);
    }

    bool inside(int x, int y){
        return min(x,y) > 0 && x <= width && y <= height;
    }

    void openzero(int x, int y){
        boxBomb[x][y].openClose = 1; boxBomb[x][y].printBox(); --closeBox;
        if (boxBomb[x][y].num)return;

        forw(k,0,7,1){
            int xx = x + dx[k], yy = y + dy[k];
            if (inside(xx,yy) && !boxBomb[xx][yy].isBomb && !boxBomb[xx][yy].openClose && !boxBomb[xx][yy].Flag)
                openzero(xx,yy);
        }
    }

    void checkBoxLeft(){
        int x,y; getmouseclick(WM_LBUTTONDOWN,x,y);
        cout << "initial: " << x << " " << y << endl;
        pp coor = findBox(x,y);
        x = coor.fs; y = coor.sc;
        cout << x << " " << y << endl;

        if (x == -1 || boxBomb[x][y].openClose)return;

        flagTime = 0;

        if (boxBomb[x][y].isBomb){
            boxBomb[x][y].printBomb();
            LOSE = 1; return;
        }

        openzero(x,y);
    }

    void checkBoxRight(){
        int x,y; getmouseclick(WM_RBUTTONDOWN,x,y);
        cout << "initial: " << x << " " << y << endl;
        pp coor = findBox(x,y);
        x = coor.fs; y = coor.sc;
        cout << x << " " << y << endl;

        if (x == -1 || boxBomb[x][y].openClose)return;

        flagTime = 0;

        if (boxBomb[x][y].Flag){
            boxBomb[x][y].Flag = 0;
            boxBomb[x][y].printBox();
            ++Flagleft; printFlagleft();
        } else {
            boxBomb[x][y].printFlag();
            boxBomb[x][y].Flag = 1;
            --Flagleft; printFlagleft();
        }
    }

    void checkBoxDouble(){
        int x,y; getmouseclick(WM_LBUTTONDBLCLK,x,y);
        pp coor = findBox(x,y);
        x = coor.fs; y = coor.sc;

        if (x == -1 || !boxBomb[x][y].openClose || !boxBomb[x][y].num)return;

        flagTime = 0;

        int Fleft = boxBomb[x][y].num;
        forw(k,0,7,1){
            int xx = x + dx[k], yy = y + dy[k];
            if (!inside(xx,yy))continue;
            if (boxBomb[xx][yy].Flag)--Fleft;
        }
        if (!Fleft){
            forw(k,0,7,1){
                int xx = x + dx[k], yy = y + dy[k];
                if (!inside(xx,yy))continue;
                if (boxBomb[xx][yy].Flag || boxBomb[xx][yy].openClose)continue;
                if (boxBomb[xx][yy].isBomb){LOSE = 1; boxBomb[xx][yy].printBomb(); return;}
                openzero(xx,yy);
            }
        }
    }
//viet tiep checkBox, binsearch findbox
    int play(){
        while (closeBox > numBomb){
            delay(25);
            if (!flagTime){
                endTime = time(NULL);
                if (endTime - startTime > duration){
                    duration = endTime - startTime;
                    string t = to_string(duration);
                    while (t.size() < 4)t = "0" + t;
                    printTime(t);
                }
            }
            if (ismouseclick(WM_LBUTTONDOWN)){
                checkBoxLeft();
                cout << "start time: " << startTime << endl;
                if (!flagTime && !startTime)startTime = time(NULL);
            }
            if (LOSE)return 0;
            if (ismouseclick(WM_RBUTTONDOWN)){
                checkBoxRight();
                if (!flagTime && !startTime)startTime = time(NULL);
            }
            if (ismouseclick(WM_LBUTTONDBLCLK)){
                checkBoxDouble();
                if (!flagTime && !startTime)startTime = time(NULL);
            }
            if (LOSE)return 0;

            if (Home_button.checkMousein())return 2;
            if (Restart_button.checkMousein())return 3;
        }
        return 1;
    }
};


#endif // _GAME_H_
