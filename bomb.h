#ifndef _BOMB_H_
#define _BOMB_H_

#include <bits/stdc++.h>
#include <graphics.h>
#define fs first
#define sc second
#define forw(i, f, e, c) for (int (i) = (f); (i) <= (e); (i) += (c))

using namespace std;

typedef long long ll;
typedef long double ldb;
typedef pair <int,int> pp;

const int charColor[] = {0,COLOR(35,189,223),COLOR(111,146,26),COLOR(198,50,108),COLOR(38,91,190),COLOR(190,52,52),6,3,1};
const int bgColor = COLOR(50,55,61);

// 1 : 35 189 223
// 2 : 111 146 26
// 3 : 198 50 108
// 4 : 38 91 190
// 5 : 190 52 52
// 103 183 255

class Bomb {
    public:
    bool Flag, isBomb, openClose;
    int sizeBox, num = 0, x, y, left,top,bot,right, midx, midy;

    Bomb (bool _openClose = 0, bool _isBomb = 0, bool _Flag = 0, int _x = 0, int _y = 0, int _sizeBox = 0){
        openClose = _openClose; isBomb = _isBomb; Flag = _Flag; x = _x; y = _y; sizeBox = _sizeBox;
        left = sizeBox*(x-1)+10; top = sizeBox*(y-1) + 10; right = sizeBox*x + 10; bot = sizeBox*y + 10;
        midx = (left + right) >> 1; midy = (top + bot) >> 1;
    }

    void printBomb(){
        if (!isBomb)return;
        int res = sizeBox / 4;
        readimagefile("pics/bomb.gif",left+1,top+1,right-1,bot-1);
    }

    void printFlag(){
        setfillstyle(SOLID_FILL,YELLOW);
        bar(left,top,right,bot);
        setcolor(bgColor);
        rectangle(sizeBox*(x-1)+10, sizeBox*(y-1) + 10, sizeBox*x + 10, sizeBox*y + 10);
        int res = sizeBox / 4;
        readimagefile("pics/flag.bmp",left+res,top+res,right-res,bot-res);
    }

    void printClose(){
        if (Flag){printFlag(); return;}

        setfillstyle(SOLID_FILL,COLOR(103,183,255));
        bar(left,top,right,bot);
        setcolor(bgColor);
        rectangle(sizeBox*(x-1)+10, sizeBox*(y-1) + 10, sizeBox*x + 10, sizeBox*y + 10);
    }

    void printOpen(){
        cout << x << " " << y << endl;
        setfillstyle(SOLID_FILL,COLOR(254,254,254));
        setbkcolor(COLOR(254,254,254));
////        cout << Button_color << " " << midx << " " << midy << endl;
////        cout << top << " " << left << " " << bot << " " << right << endl;
        bar(left, top, right, bot);
//
        setcolor(bgColor);
        rectangle(left,top,right,bot);

        if (!num)return;

        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != sizeBox/20)
        settextstyle(BOLD_FONT, HORIZ_DIR, sizeBox / 20);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);

        setcolor(charColor[num]);
        string Text = to_string(num);
        outtextxy(midx,midy+sizeBox/8,&Text[0]);
    }

    void printBox(){
        if (openClose)printOpen(); else printClose();
    }
};

#endif // _BOMB_H_
