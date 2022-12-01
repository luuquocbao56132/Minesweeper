#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <bits/stdc++.h>
#define fs first
#define sc second
#include <graphics.h>
#define pb push_back

using namespace std;

int Hover = COLOR(214,244,255), Bar = COLOR(164,185,177);

class Button{
public:
    int top,bot,left,right,midx,midy,width,height,textSize, Button_color;
    char *Text;
    bool sta;

    Button(int _midx, int _midy, int _width, int _height, int Buttoncolor, char *_Text){
        midx = _midx; midy = _midy; width = _width; height = _height; Button_color = Buttoncolor; Text = _Text;
        top = midy - (height>>1); bot = midy + (height>>1);
        left = midx - (width>>1); right = midx + (width>>1);
    }

    bool checkIn(int x, int y)
    {return left <= x && x <= right && top <= y && y <= bot;}

    bool checkMousein(){
        if (!checkIn(mousex(), mousey())){return 0;}
//        setfillstyle(SOLID_FILL, Hover); bar(left,top,right,bot);
        setcolor(Hover); rectangle(left,top,right,bot);
        rectangle(left+1,top+1,right-1,bot-1);
        do {
            while (ismouseclick(WM_LBUTTONDOWN)){
                int x,y; getmouseclick(WM_LBUTTONDOWN,x,y);
                if (checkIn(x,y))return 1;
            }
        } while (checkIn(mousex(), mousey()));

        drawButton();
        return 0;
    }

    void drawButton(){
        setfillstyle(SOLID_FILL,Button_color);
//        cout << Button_color << " " << midx << " " << midy << endl;
//        cout << top << " " << left << " " << bot << " " << right << endl;
        bar(left, top, right+1, bot+1);

//        setcolor(Bar);
//        rectangle(left,top,right,bot);

        setbkcolor(Button_color);

        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != 3)
            settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);

        setcolor(WHITE);
        outtextxy(midx,midy,Text);
    }
};

#endif // _BUTTON_H_
