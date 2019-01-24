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
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);
    if(has_colors() == FALSE)
    {	endwin();
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

    walg = newwin(W_H_ALG, W_W_ALG, W_Y_ALG, W_X_ALG);
    wprc = newwin(W_H_PRC, W_W_PRC, W_Y_PRC, W_X_PRC);
    wdone = newwin(W_H_DONE, W_W_DONE, W_Y_DONE, W_X_DONE);
    wlegend = newwin(W_H_LEGEND, W_W_LEGEND, W_Y_LEGEND, W_X_LEGEND);

    wattron(walg, A_BOLD);
    wattron(wprc, A_BOLD);
    wattron(wdone, A_BOLD);
    wattron(wlegend, A_BOLD);
}

PSAscreen& PSAscreen::get()
{
    static PSAscreen intstance;
    return intstance;
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
    // Process and Done windows
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

void PSAscreen::add_prc(std::vector<process*> &processes)
{
    int w = 1, h = 1;
    for (size_t i = 0; i < processes.size(); i++)
    {
	if (w >= W_W_PRC - 2)
	{
	    w = 1;
	    h += 1;
	}
	if (h >= W_H_PRC - 1)
	{
	    break;
	}
	wmove(wprc, h, w);
	int n = 2;
	switch (processes[i]->get_pr())
	{
	case priority::LOW:
	    wattron(wprc, COLOR_PAIR(n));
	    break;
	case priority::MEDIUM:
	    n = 3;
	    wattron(wprc, COLOR_PAIR(3));
	    break;
	case priority::HIGH:
	    n = 4;
	    wattron(wprc, COLOR_PAIR(n));
	    break;
	case priority::EXTREME:
	    n = 5;
	    wattron(wprc, COLOR_PAIR(n));
	    break;
	}
	waddstr(wprc, processes[i]->get_id().c_str());
	w += 5;
	wattron(wprc, COLOR_PAIR(6));
    }
}

void PSAscreen::show_process(process* pr)
{
    wmove(walg, 2, 2);
    waddstr(walg, pr->get_id().c_str());
    wmove(walg, 3, 2);
    waddstr(walg, prtostr(pr->get_pr()).c_str());
    wmove(walg, 4, 2);
    waddstr(walg, std::to_string(pr->get_ttl()).c_str());
    wrefresh(walg);
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

PSAscreen::~PSAscreen()
{
    delwin(walg);
    delwin(wprc);
    delwin(wdone);
    delwin(wlegend);
    endwin();
}
