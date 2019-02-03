#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include <vector>
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
    void draw_frame_of(WINDOW *w, std::string title);

    void draw_small_arrows();

    void show_awt(int awt);
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
    static const int W_X_DONE;
    static const int W_Y_DONE;
    static const int W_W_PRC_DONE;
    static const int W_H_PRC_DONE;

    static const int W_X_LEGEND;
    static const int W_Y_LEGEND;
    static const int W_W_LEGEND;
    static const int W_H_LEGEND;

    static const int COLOR_ORANGE;

    WINDOW *walg;
    WINDOW *wprc;
    WINDOW *wdone;
    WINDOW *wlegend;
};

#endif
