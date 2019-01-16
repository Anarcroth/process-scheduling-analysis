#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include <ncurses.h>

class PSAscreen
{
public:
    PSAscreen();

    void draw_frame();
    void draw_frame_alg();
    void draw_frame_prc();
    void draw_frame_done();
    void draw_frame_legend();
    void draw_small_arrows();

private:
    static const int W_X_ALG;
    static const int W_Y_ALG;
    static const int W_W_ALG;
    static const int W_H_ALG;

    static const int W_X_PRC;
    static const int W_Y_PRC;
    static const int W_W_PRC;
    static const int W_H_PRC;

    static const int W_X_DONE;
    static const int W_Y_DONE;
    static const int W_W_DONE;
    static const int W_H_DONE;

    static const int W_X_LEGEND;
    static const int W_Y_LEGEND;
    static const int W_W_LEGEND;
    static const int W_H_LEGEND;

    WINDOW *walg;
    WINDOW *wprc;
    WINDOW *wdone;
    WINDOW *wlegend;
};

#endif
