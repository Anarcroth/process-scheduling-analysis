#include "screen.h"

const int PSAscreen::W_Y_ALG = 1;
const int PSAscreen::W_X_ALG = 3;
const int PSAscreen::W_W_ALG = 120;
const int PSAscreen::W_H_ALG = 39;

const int PSAscreen::W_Y_PRC = 40;
const int PSAscreen::W_X_PRC = 3;
const int PSAscreen::W_W_PRC = 57;
const int PSAscreen::W_H_PRC = 15;

const int PSAscreen::W_Y_DONE = 40;
const int PSAscreen::W_X_DONE = 66;
const int PSAscreen::W_W_DONE = 57;
const int PSAscreen::W_H_DONE = 15;

const int PSAscreen::W_Y_LEGEND = 1;
const int PSAscreen::W_X_LEGEND = 124;
const int PSAscreen::W_W_LEGEND = 64;
const int PSAscreen::W_H_LEGEND = 54;


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

    wattron(walg, A_BOLD);
    wattron(wprc, A_BOLD);
    wattron(wdone, A_BOLD);
    wattron(wlegend, A_BOLD);
}

void PSAscreen::draw_frame()
{
    box(stdscr, 0, 0);
    draw_small_arrows();
    refresh();
}

void PSAscreen::draw_small_arrows()
{
    // This draws the small arrows between the
    // Process and Done window
    move(45, 62);
    addch(ACS_RARROW);
    addch(ACS_RARROW);
    move(50, 62);
    addch(ACS_RARROW);
    addch(ACS_RARROW);

}

void PSAscreen::draw_frame_alg()
{
    box(walg, 0, 0);
    wmove(walg, 0, 1);
    waddstr(walg, " ALGORITHM ");
    wrefresh(walg);
}

void PSAscreen::draw_frame_prc()
{
    box(wprc, 0, 0);
    wmove(wprc, 0, 1);
    waddstr(wprc, " PROCESS ");
    wrefresh(wprc);
}

void PSAscreen::draw_frame_done()
{
    box(wdone, 0, 0);
    wmove(wdone, 0, 1);
    waddstr(wdone, " DONE ");
    wrefresh(wdone);
}

void PSAscreen::draw_frame_legend()
{
    box(wlegend, 0, 0);
    wmove(wlegend, 0, 1);
    waddstr(wlegend, " LEGEND ");
    wrefresh(wlegend);
}
