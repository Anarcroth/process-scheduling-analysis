#include "screen.h"

const int PSAscreen::W_Y_ALG = 10;
const int PSAscreen::W_X_ALG = 10;
const int PSAscreen::W_W_ALG = 40;
const int PSAscreen::W_H_ALG = 3;

const int PSAscreen::W_Y_PRC = 40;
const int PSAscreen::W_X_PRC = 10;
const int PSAscreen::W_W_PRC = 60;
const int PSAscreen::W_H_PRC = 5;

const int PSAscreen::W_Y_DONE = 40;
const int PSAscreen::W_X_DONE = 80;
const int PSAscreen::W_W_DONE = 60;
const int PSAscreen::W_H_DONE = 5;

const int PSAscreen::W_Y_LEGEND = 10;
const int PSAscreen::W_X_LEGEND = 160;
const int PSAscreen::W_W_LEGEND = 20;
const int PSAscreen::W_H_LEGEND = 40;


PSAscreen::PSAscreen()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    walg = newwin(W_H_ALG, W_W_ALG, W_Y_ALG, W_X_ALG);
    wprc = newwin(W_H_PRC, W_W_PRC, W_Y_PRC, W_X_PRC);
    wdone = newwin(W_H_DONE, W_W_DONE, W_Y_DONE, W_X_DONE);
    wlegend = newwin(W_H_LEGEND, W_W_LEGEND, W_Y_LEGEND, W_X_LEGEND);
}

void PSAscreen::draw_frame()
{
    box(stdscr, 0, 0);
    refresh();
}

void PSAscreen::draw_frame_alg()
{
    box(walg, 0, 0);
    wrefresh(walg);
}

void PSAscreen::draw_frame_prc()
{
    box(wprc, 0, 0);
    wrefresh(wprc);
}

void PSAscreen::draw_frame_done()
{
    box(wdone, 0, 0);
    wrefresh(wdone);
}

void PSAscreen::draw_frame_legend()
{
    box(wlegend, 0, 0);
    wrefresh(wlegend);
}
