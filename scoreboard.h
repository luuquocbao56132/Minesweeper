#ifndef _SCOREBOARD_H_
#define _SCOREBOARD_H_

#include <bits/stdc++.h>
#define fs first
#define sc second
#define MASK(i) (1LL << (i))
#define BIT(i,n) (((n) >> (i)) & 1LL)
#define forw(i, f, e, c) for (int (i) = (f); (i) <= (e); (i) += (c))
#define ford(i, e, f, c) for (int (i) = (e); (i) >= (f); (i) -= (c))
#define __builtin_popcount __builtin_popcountll
#define pf push_front
#define pb push_back

class Scoreboard{
public:
    string modeArray[3] = {"Easy","Medium","Expert"};
    int Rank[3][11], color[3] = {COLOR(60,148,39),COLOR(213,117,4),COLOR(204,54,47)};

    Scoreboard(int t) {
        setbkcolor(COLOR(18,103,72));
        cleardevice();
        print(0);
    }

    void reset(int mode){ cout << mode << endl;
        ofstream tfile;  tfile.open("save\\"+modeArray[mode]+".log"); cout << 1 << endl;
        forw(j,1,10,1)tfile << 1000000 << '\n';
        tfile.close();
    }

    void getRank(string T, int mode){
        ifstream tfile; tfile.open("save\\"+T+".log");
        forw(i,1,10,1)tfile >> Rank[mode][i];
        tfile.close();
    }

    void print(int mode){
        string Text;
        Text = modeArray[mode];
        getRank(Text, mode);

        setfillstyle(SOLID_FILL,color[mode]); //bar(200*(mode+1)+100*(mode),100,200*(mode+1)+100*(mode)+200,150);
        textsettingstype charsetting; gettextsettings(&charsetting);
        if (charsetting.font != BOLD_FONT || charsetting.direction != HORIZ_DIR || charsetting.charsize != 4)
        settextstyle(BOLD_FONT, HORIZ_DIR, 3);
        if (charsetting.horiz != CENTER_TEXT || charsetting.vert != CENTER_TEXT)
            settextjustify(CENTER_TEXT, CENTER_TEXT);
        setcolor(WHITE); setbkcolor(color[mode]);
        //outtextxy(300+200*mode+100*mode,125,&Text[0]);

        bar(200,150,1000,720);
        Text = "Rank";
        outtextxy(475,225,&Text[0]); rectangle(400,200,550,250);
        forw(i,1,10,1){
            Text = to_string(i);
            Text = "#" + Text;
            outtextxy(475,250+40*(i-1)+25,&Text[0]);
            rectangle(400,250+40*(i-1),550,250+40*i);

            if (Rank[mode][i] != 1000000){
                Text = to_string(Rank[mode][i]);
                while (Text.size() < 4)Text = "0" + Text;
            } else Text = "N/A";
            outtextxy(680,250+40*(i-1)+25,&Text[0]);
            rectangle(550,250+40*(i-1),800,250+40*i);
        }
        Text = "Score (Time)";
        outtextxy(680,225,&Text[0]); rectangle(550,200,800,250);
    }
};

#endif // _SCOREBOARD_H_
