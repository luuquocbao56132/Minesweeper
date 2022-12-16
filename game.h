#ifndef _GAME_H_
#define _GAME_H_

#include <bits/stdc++.h>
#include <graphics.h>
#include "bomb.h"
#include "scoreboard.h"
#include "button.h"
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

// background RGB(51,56,62) RGB(50,55,61)
// bar RGB(48,54,60) RGB(48,53,59)

class Game{
public:
    pair <int,int> Stt[35*35];
    vector <int> Ran_first;
    int LOSE = 0, Flagleft, mode;
    bool flagTime = 1, firstLeftclick = 1;
    int height, width, numBomb, numSquare, sizeBox, closeBox, startTime = 0, endTime = 0, duration = 0;
    Bomb boxBomb[35][35];

    Button Restart_button = Button(1000,700,150,50,COLOR(164, 113, 71),COLOR(255, 204, 165),"Restart");
    Button Home_button = Button(1000,600,150,50,COLOR(164, 113, 71),COLOR(255, 204, 165),"Home");

    Game (int _width = 0, int _height = 0, int _numBomb = 0, int _mode = 0){
        height = _height; width = _width; numBomb = _numBomb; Flagleft = numBomb; mode = _mode;
        numSquare = width * height; closeBox = numSquare;
        sizeBox = min({80,890 / width, 790 / height});
        cout << sizeBox << endl;
        forw(i,1,width,1) forw (j,1,height,1) boxBomb[i][j] = Bomb(0,0,0,i,j,sizeBox,width,height);
    }

    void printBoard(){
        setbkcolor(bgColor);
        readimagefile("pics/play.gif",0,0,1200,800);

        forw(i,1,width,1) forw (j,1,height,1)boxBomb[i][j].printBox();

        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != 4)
            settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);

        setcolor(COLOR(48, 50, 53)); setbkcolor(COLOR(154, 103, 59));
        setfillstyle(SOLID_FILL,COLOR(154, 103, 59));

        setfillstyle(SOLID_FILL,COLOR(110, 80, 50));
        bar(1000-80,300-30,1000+80,300+20);
        bar(1000-80,300-30,1000+80,300+20+60);
        setfillstyle(SOLID_FILL,COLOR(154, 103, 59));
        bar(1000-75,300-25,1000+75,300+15);
        bar(1000-75,300+20,1000+75,300+15+60);
        setcolor(COLOR(48, 50, 53));
        outtextxy(1000,302,"TIME");
        printTime();


        setfillstyle(SOLID_FILL,COLOR(110, 80, 50));
        bar(1000-80,450-30,1000+80,450+20);
        bar(1000-80,450-30,1000+80,450+20+60);
        setfillstyle(SOLID_FILL,COLOR(154, 103, 59));
        bar(1000-75,450-25,1000+75,450+15);
        bar(1000-75,450+20,1000+75,450+15+60);
        setcolor(COLOR(48, 50, 53));
        outtextxy(1000,452,"BOMB");
        printFlagleft();

        Home_button.drawButton();
        Restart_button.drawButton();
    }

    void printTime(){
        string t = to_string(duration);
        while (t.size() < 4)t = "0" + t;

        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != 4)
            settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);
        setcolor(COLOR(48, 50, 53)); setbkcolor(COLOR(154, 103, 59));
        outtextxy(1000,355,&t[0]);
    }

    void printFlagleft(){
        setfillstyle(SOLID_FILL,COLOR(154, 103, 59));
        string res = to_string(abs(Flagleft));
        while (res.size() < 3)res = "0" + res;
        if (Flagleft < 0)res = "-" + res;

        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != 4)
            settextstyle(BOLD_FONT, HORIZ_DIR, 4);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);
        setcolor(COLOR(48, 50, 53)); setbkcolor(COLOR(154, 103, 59));
        outtextxy(1000,505,&res[0]);
    }

    int printallBomb(){
        forw(i,0,numBomb-1,1){
            int x = Stt[Ran_first[i]].fs, y = Stt[Ran_first[i]].sc;
            boxBomb[x][y].printBomb();
        }
    }

    void initBoard(int x, int y){
        int ii = 0, hieu = x*y - numBomb;

        cout << width << " " << height << endl;

        forw(i,1,width,1) forw(j,1,height,1){
            if (abs(x-i) < 2 && abs(y-j) < 2){
                if(hieu >= 9)continue;
                Stt[++ii] = {i,j};
                Ran_first.push_back(ii);
                ++hieu;
            } else {
                Stt[++ii] = {i,j};
                Ran_first.push_back(ii);
            }
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
            forw(i,1,width,1)cout << boxBomb[i][j].num << " ";
            cout << '\n';
        }
    }

    pp findBox(int coor_x, int coor_y){
        int x = -1,y = -1,l = 1, r = width;
        while (l <= r){
            int mid = (l + r) >> 1;
            if (coor_x >= boxBomb[mid][1].left && coor_x <= boxBomb[mid][1].right){
                x = mid; break;
            }
            if (coor_x < boxBomb[mid][1].right)r = mid - 1; else l = mid + 1;
        }

        l = 1; r = height;
        while (l <= r){
            int mid = (l + r) >> 1;
            if (coor_y >= boxBomb[1][mid].top && coor_y <= boxBomb[1][mid].bot){
                y = mid; break;
            }
            if (coor_y < boxBomb[1][mid].bot)r = mid - 1; else l = mid + 1;
        }

        if (x == -1 || y == -1)return make_pair(-1,-1);
        return make_pair(x,y);
    }

    bool inside(int x, int y){
        return min(x,y) > 0 && x <= width && y <= height;
    }

    void openzero(int x, int y){
        queue <pp> q; q.push({x,y});
        while (!q.empty()){
            x = q.front().fs; y = q.front().sc; q.pop();
            if (boxBomb[x][y].openClose)continue;
            boxBomb[x][y].openClose = 1; boxBomb[x][y].printBox(); --closeBox;
            if (boxBomb[x][y].Flag)++Flagleft;
            if (boxBomb[x][y].num)continue;

            forw(k,0,7,1){
                int xx = x + dx[k], yy = y + dy[k];
                if (inside(xx,yy) && !boxBomb[xx][yy].isBomb && !boxBomb[xx][yy].openClose)
                    q.push({xx,yy});
            }
        }
    }

    bool checkBoxLeft(){
        int x,y; getmouseclick(WM_LBUTTONDOWN,x,y);
        pp coor = findBox(x,y);
        x = coor.fs; y = coor.sc;

        if (x == -1 || boxBomb[x][y].openClose || boxBomb[x][y].Flag)return 0;

        if (firstLeftclick)initBoard(x,y), firstLeftclick = 0;
        flagTime = 0;

        if (boxBomb[x][y].isBomb){
            boxBomb[x][y].printBomb();
            LOSE = 1; return 0;
        }

        openzero(x,y);
        printFlagleft();
        return 1;
    }

    bool checkBoxRight(){
        int x,y; getmouseclick(WM_RBUTTONDOWN,x,y);
        pp coor = findBox(x,y);
        x = coor.fs; y = coor.sc;

        if (x == -1 || boxBomb[x][y].openClose)return 0;

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

        return 1;

        //saveBoard();
    }

    bool checkBoxDouble(){
        int x,y; getmouseclick(WM_LBUTTONDBLCLK,x,y);
        pp coor = findBox(x,y);
        x = coor.fs; y = coor.sc;

        if (x == -1 || boxBomb[x][y].Flag || !boxBomb[x][y].num)return 0;

        if (boxBomb[x][y].isBomb){
            boxBomb[x][y].printBomb();
            LOSE = 1; return 0;
        }

        if (!boxBomb[x][y].openClose)openzero(x,y);
        if (!boxBomb[x][y].num)return 1;
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
                if (boxBomb[xx][yy].isBomb){LOSE = 1; boxBomb[xx][yy].printBomb(); return 0;}
                openzero(xx,yy); printFlagleft();
            }
        }

        return 1;
        //saveBoard();
    }

    void saveTime(int t){
        ofstream tfile;
        tfile.open("save\\time.log");
        tfile << t;
        tfile.close();
    }

    void saveBoard(){
        ofstream tfile; tfile.open("save\\game.log");
        tfile << width << " " << height << " " << numBomb << " " << mode << '\n';
        forw(i,1,width,1) {
            forw(j,1,height,1){
                int t = boxBomb[i][j].openClose << 2;
                t |= (boxBomb[i][j].isBomb << 1);
                t |= boxBomb[i][j].Flag;
                tfile << t << " ";
            }
            tfile << '\n';
        } //cout << endl;

        forw(i,1,width,1) {
            forw(j,1,height,1) tfile << boxBomb[i][j].num << " ";
            tfile << '\n';
        } //cout << endl;

        tfile.close();
    }

    void clearfile(){
        ofstream tfile;
        tfile.open("save\\time.log");
        tfile.close();
        tfile.open("save\\game.log");
        tfile.close();
    }

    void saveScore(){
        string T;
        if (!mode)T = "Easy"; else
        if (mode == 1)T = "Medium"; else
        if (mode == 2)T = "Expert"; else
        if (mode == 3)T = "Master";
        int Rank[15];
        ifstream infile; infile.open("save\\"+T+".log");
        forw(i,1,10,1)infile >> Rank[i]; Rank[11] = duration;
        infile.close();
        sort(Rank+1,Rank+12);
        ofstream outfile; outfile.open("save\\"+T+".log");
        forw(i,1,10,1)outfile << Rank[i] << '\n';
        outfile.close();
        //code save diem
    }
    void checkTime(){
        if (!flagTime){
                endTime = time(NULL);
                if (endTime - startTime > duration){
                    duration = endTime - startTime;
                    printTime();
                    saveTime(duration);
                }
            }
    }

    bool checkIn(int x, int y,int left, int top, int right, int bot)
    {return left <= x && x <= right && top <= y && y <= bot;}

    bool checkMousein(bool t, int left, int top, int right, int bot){
        if (!checkIn(mousex(), mousey(),left,top,right,bot)){return 0;}
        setcolor(Hover); rectangle(left,top,right,bot);
        rectangle(left+1,top+1,right-1,bot-1);
        do {
            checkTime();
            while (ismouseclick(WM_LBUTTONDOWN)){
                int x,y; getmouseclick(WM_LBUTTONDOWN,x,y);
                if (checkIn(x,y,left,top,right,bot))return 1;
            }
        } while (checkIn(mousex(), mousey(),left,top,right,bot));

        if (!t)Home_button.drawButton(); else Restart_button.drawButton();
        return 0;
    }

    int play(){
        while (closeBox > numBomb){
            //cout << "closeBox: " << closeBox << endl;
            delay(25);
            checkTime();
            if (ismouseclick(WM_LBUTTONDOWN)){
                if (checkBoxLeft())saveBoard();
                if (!flagTime && !startTime)startTime = time(NULL);
            }
            if (LOSE)return 0;
            if (ismouseclick(WM_RBUTTONDOWN)){
                if (checkBoxRight())saveBoard();
                if (!flagTime && !startTime)startTime = time(NULL);
            }
            if (ismouseclick(WM_LBUTTONDBLCLK)){
                if(checkBoxDouble())saveBoard();
                if (!flagTime && !startTime)startTime = time(NULL);
            }
            if (LOSE)return 0;

            if (checkMousein(0,Home_button.left,Home_button.top,Home_button.right,Home_button.bot)){return 2;}
            if (checkMousein(1,Restart_button.left,Restart_button.top,Restart_button.right,Restart_button.bot)){clearfile(); return 3;}
        }
        //clearfile();
        if (mode < 4)saveScore();
        return 1;
    }
};


#endif // _GAME_H_
