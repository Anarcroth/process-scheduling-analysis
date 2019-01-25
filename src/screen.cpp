#include <string>
#include <vector>

#include "screen.h"
#include "process.h"
#include "priority.h"

// TODO	add orange color

const int PSAscreen::W_Y_ALG = 1;
const int PSAscreen::W_X_ALG = 3;
const int PSAscreen::W_W_ALG = 119;
const int PSAscreen::W_H_ALG = 39;

const int PSAscreen::W_Y_PRC = 40;
const int PSAscreen::W_X_PRC = 3;
const int PSAscreen::W_W_PRC = 56;
const int PSAscreen::W_H_PRC = 12;

const int PSAscreen::W_Y_DONE = 40;
const int PSAscreen::W_X_DONE = 66;
const int PSAscreen::W_W_DONE = 56;
const int PSAscreen::W_H_DONE = 12;

const int PSAscreen::W_Y_LEGEND = 1;
const int PSAscreen::W_X_LEGEND = 123;
const int PSAscreen::W_W_LEGEND = 65;
const int PSAscreen::W_H_LEGEND = 51;

PSAscreen::PSAscreen()
{
    // Makes basic setup and starts colors
    init();

    walg = newwin(W_H_ALG, W_W_ALG, W_Y_ALG, W_X_ALG);
    wprc = newwin(W_H_PRC, W_W_PRC, W_Y_PRC, W_X_PRC);
    wdone = newwin(W_H_DONE, W_W_DONE, W_Y_DONE, W_X_DONE);
    wlegend = newwin(W_H_LEGEND, W_W_LEGEND, W_Y_LEGEND, W_X_LEGEND);

    wattron(walg, A_BOLD);
    wattron(wprc, A_BOLD);
    wattron(wdone, A_BOLD);
    wattron(wlegend, A_BOLD);
}

void PSAscreen::init()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    if (has_colors() == FALSE)
    {
	endwin();
	printf("Your terminal does not support color\n");
	exit(1);
    }

    start_color();
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
}

PSAscreen& PSAscreen::get()
{
    static PSAscreen intstance;
    return intstance;
}

WINDOW* PSAscreen::get_walg() const
{
    return walg;
}

WINDOW* PSAscreen::get_wprc() const
{
    return wprc;
}

WINDOW* PSAscreen::get_wdone() const
{
    return wdone;
}

WINDOW* PSAscreen::get_wlegend() const
{
    return wlegend;
}

void PSAscreen::draw_small_arrows()
{
    // This draws the small arrows between the
    // Process and Done windows
    move(43, 62);
    addch(ACS_RARROW);
    addch(ACS_RARROW);
    move(48, 62);
    addch(ACS_RARROW);
    addch(ACS_RARROW);
}

void PSAscreen::push_prc_in(WINDOW* w, std::vector<process*> &processes)
{
    int width = 1, height = 1;
    for (size_t i = 0; i < processes.size(); i++)
    {
	if (width >= W_W_PRC - 2)
	{
	    width = 1;
	    height += 1;
	}
	if (height >= W_H_PRC - 1)
	{
	    break;
	}
	wmove(w, height, width);
	colorinprocess(w, processes[i]->get_pr());
	waddstr(w, processes[i]->get_id().c_str());
	width += 5;
	wattron(w, COLOR_PAIR(6));
    }
}

void PSAscreen::colorinprocess(WINDOW *w, priority pr)
{
    switch (pr)
    {
    case priority::LOW:
	wattron(w, COLOR_PAIR(2));
	break;
    case priority::MEDIUM:
	wattron(w, COLOR_PAIR(3));
	break;
    case priority::HIGH:
	wattron(w, COLOR_PAIR(4));
	break;
    case priority::EXTREME:
	wattron(w, COLOR_PAIR(5));
	break;
    }
}

void PSAscreen::show_process(process* pr)
{
    // This will color in the process
    colorinprocess(walg, pr->get_pr());

    wmove(walg, 2, 2);
    waddstr(walg, pr->get_id().c_str());

    // This clears the previous data, since it might be too long in chars
    wmove(walg, 3, 2);
    waddstr(walg, (prtostr(pr->get_pr()) + "    ").c_str());

    // This clears the previous data, since it might be too long in chars
    wmove(walg, 4, 2);
    waddstr(walg, (std::to_string(pr->get_ttl()) + "    ").c_str());

    wattron(walg, COLOR_PAIR(6));
    wrefresh(walg);
}

void PSAscreen::draw_frame()
{
    box(stdscr, 0, 0);
    draw_small_arrows();
    wnoutrefresh(stdscr);
}

void PSAscreen::draw_frame_alg()
{
    box(walg, 0, 0);
    wmove(walg, 0, 1);
    waddstr(walg, " ALGORITHM ");
    wnoutrefresh(walg);
}

void PSAscreen::draw_frame_prc()
{
    box(wprc, 0, 0);
    wmove(wprc, 0, 1);
    waddstr(wprc, " PROCESS ");
    wnoutrefresh(wprc);
}

void PSAscreen::draw_frame_done()
{
    box(wdone, 0, 0);
    wmove(wdone, 0, 1);
    waddstr(wdone, " DONE ");
    wnoutrefresh(wdone);
}

void PSAscreen::draw_frame_legend()
{
    box(wlegend, 0, 0);
    wmove(wlegend, 0, 1);
    waddstr(wlegend, " LEGEND ");
    wnoutrefresh(wlegend);
}

PSAscreen::~PSAscreen()
{
    delwin(walg);
    delwin(wprc);
    delwin(wdone);
    delwin(wlegend);
    endwin();
}
