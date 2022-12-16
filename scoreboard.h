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
    string modeArray[4] = {"Easy","Medium","Expert","Master"};
    int Rank[11], color[4] = {COLOR(207, 158, 78),COLOR(150, 103, 39),COLOR(123, 73, 9), COLOR(79, 50, 24)};

    Scoreboard(int t) {
        setbkcolor(COLOR(18,103,72));
        readimagefile("pics/score.gif",0,0,1200,800);
        print(0);
    }

    void reset(int mode){ cout << mode << endl;
        ofstream tfile;  tfile.open("save\\"+modeArray[mode]+".log"); cout << 1 << endl;
        forw(j,1,10,1)tfile << 1000000 << '\n';
        tfile.close();
    }

    void getRank(string T, int mode){
        ifstream tfile; tfile.open("save\\"+T+".log");
        forw(i,1,10,1)tfile >> Rank[i];
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
            outtextxy(475,250+40*(i-1)+25,&Text[0]);
            rectangle(400,250+40*(i-1),550,250+40*i);

            if (Rank[i] != 1000000){
                int res = Rank[i] / 60;
                Text = to_string(res) + ":";
                while (Text.size() < 3)Text = "0" + Text;
                res = Rank[i] - Rank[i]/60*60;
                Text = Text + (res < 10 ? "0" : "") + to_string(res);
            } else Text = "N/A";
            outtextxy(680,250+40*(i-1)+25,&Text[0]);
            rectangle(550,250+40*(i-1),800,250+40*i);
        }
        Text = "Score (Time)";
        outtextxy(680,225,&Text[0]); rectangle(550,200,800,250);
    }
};

#endif // _SCOREBOARD_H_
