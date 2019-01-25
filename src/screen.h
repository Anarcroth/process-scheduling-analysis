#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include <ncurses.h>

#include "priority.h"

class process;

class PSAscreen
{
public:
    static PSAscreen& get();

    PSAscreen(PSAscreen const&)      = delete;
    void operator=(PSAscreen const&) = delete;

    void draw_frame();
    void draw_frame_alg();
    void draw_frame_prc();
    void draw_frame_done();
    void draw_frame_legend();
    void draw_small_arrows();

    void show_process(process* pr);

    void push_prc_in(WINDOW* w, std::vector<process*> &processes);

    WINDOW* get_walg() const;
    WINDOW* get_wprc() const;
    WINDOW* get_wdone() const;
    WINDOW* get_wlegend() const;

private:
    PSAscreen();
    ~PSAscreen();

    void init();
    void colorinprocess(WINDOW *w, priority pr);

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
