#include <string>
#include <vector>

#include "screen.hpp"
#include "process.hpp"
#include "commons.hpp"
#include "pool.hpp"

const int PSAscreen::W_Y_ALG = 1;
const int PSAscreen::W_X_ALG = 3;
const int PSAscreen::W_W_ALG = 119;
const int PSAscreen::W_H_ALG = 39;

const int PSAscreen::W_Y_PRC = 40;
const int PSAscreen::W_X_PRC = 3;
const int PSAscreen::W_Y_DONE = 40;
const int PSAscreen::W_X_DONE = 66;
const int PSAscreen::W_W_PRC_DONE = 56;
const int PSAscreen::W_H_PRC_DONE = 12;

const int PSAscreen::W_Y_LEGEND = 1;
const int PSAscreen::W_X_LEGEND = 123;
const int PSAscreen::W_W_LEGEND = 65;
const int PSAscreen::W_H_LEGEND = 51;

const std::string PSAscreen::LEG_PR = " Processes ";
const std::string PSAscreen::LEG_LPR = "Low Priority: (l)";
const std::string PSAscreen::LEG_MPR = "Medium Priority: (m)";
const std::string PSAscreen::LEG_HPR = "High Priority: (h)";
const std::string PSAscreen::LEG_XPR = "Extreme Priority: (x)";
const std::string PSAscreen::LEG_RPR = "Random: (r)";
const std::string PSAscreen::LEG_ALG = " Algorithm ";
const std::string PSAscreen::LEG_FCFS_ALG = "First Come First Serve: FCFS (f)";
const std::string PSAscreen::LEG_SJF_ALG = "Shortest Job First: SJF (s)";
const std::string PSAscreen::LEG_RR_ALG = "Round Robbin: RR (o)";
const std::string PSAscreen::LEG_PJF_ALG = "Priority Job First: PJF (p)";

const int PSAscreen::PR0COLOR = 100;
const int PSAscreen::PR1COLOR = 101;
const int PSAscreen::PR2COLOR = 102;
const int PSAscreen::PR3COLOR = 103;
const int PSAscreen::PR4COLOR = 104;
const int PSAscreen::PR5COLOR = 105;
const int PSAscreen::PR6COLOR = 106;

PSAscreen::PSAscreen()
{
    // Makes basic setup and starts colors
    init();

    walg = newwin(W_H_ALG, W_W_ALG, W_Y_ALG, W_X_ALG);
    wprc = newwin(W_H_PRC_DONE, W_W_PRC_DONE, W_Y_PRC, W_X_PRC);
    wdone = newwin(W_H_PRC_DONE, W_W_PRC_DONE, W_Y_DONE, W_X_DONE);
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

    if (has_colors() == FALSE)
    {
	endwin();
	printf("Your terminal does not support color\n");
	exit(1);
    }

    start_color();
    init_color(PR0COLOR, 243, 1000, 50);
    init_color(PR1COLOR, 819, 909, 47);
    init_color(PR2COLOR, 1000, 831, 0);
    init_color(PR3COLOR, 909, 588, 47);
    init_color(PR4COLOR, 1000, 376, 27);
    init_color(PR5COLOR, 909, 82, 15);
    init_color(PR6COLOR, 1000, 50, 749);
    init_pair(1, PR0COLOR, COLOR_BLACK);
    init_pair(2, PR1COLOR, COLOR_BLACK);
    init_pair(3, PR2COLOR, COLOR_BLACK);
    init_pair(4, PR3COLOR, COLOR_BLACK);
    init_pair(5, PR4COLOR, COLOR_BLACK);
    init_pair(6, PR5COLOR, COLOR_BLACK);
    init_pair(7, PR6COLOR, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
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
    // This draws the small arrowsp between the
    // Process and Done windows
    move(43, 62);
    addch(ACS_RARROW);
    addch(ACS_RARROW);
    move(48, 62);
    addch(ACS_RARROW);
    addch(ACS_RARROW);
}

void PSAscreen::draw_legend_cont()
{
    // Creates the Process and Algorithm sub-windows
    wattron(wlegend, COLOR_PAIR(8));
    wmove(wlegend, 2, 0);
    waddch(wlegend, ACS_LTEE);
    whline(wlegend, ACS_HLINE, W_W_LEGEND - 2);
    wmove(wlegend, 2, W_W_LEGEND - 1);
    waddch(wlegend, ACS_RTEE);
    wmove(wlegend, 2, 2);
    waddstr(wlegend, LEG_PR.c_str());

    wmove(wlegend, 10, 0);
    waddch(wlegend, ACS_LTEE);
    whline(wlegend, ACS_HLINE, W_W_LEGEND - 2);
    wmove(wlegend, 10, W_W_LEGEND - 1);
    waddch(wlegend, ACS_RTEE);
    wmove(wlegend, 10, 2);
    waddstr(wlegend, LEG_ALG.c_str());

    // Adds different Processes
    wmove(wlegend, 4, 2);
    wattron(wlegend, COLOR_PAIR(1));
    waddstr(wlegend, (LEG_LPR + "\t").c_str());
    wattron(wlegend, COLOR_PAIR(2));
    waddstr(wlegend, LEG_MPR.c_str());

    wmove(wlegend, 6, 2);
    wattron(wlegend, COLOR_PAIR(3));
    waddstr(wlegend, (LEG_HPR + "\t").c_str());
    wattron(wlegend, COLOR_PAIR(4));
    waddstr(wlegend, LEG_XPR.c_str());

    wmove(wlegend, 8, 2);
    wattron(wlegend, COLOR_PAIR(8));
    waddstr(wlegend, (LEG_RPR + "\t").c_str());

    // Adds different Algorithms
    wmove(wlegend, 12, 2);
    waddstr(wlegend, LEG_FCFS_ALG.c_str());
    wmove(wlegend, 14, 2);
    waddstr(wlegend, LEG_SJF_ALG.c_str());
    wmove(wlegend, 16, 2);
    waddstr(wlegend, LEG_RR_ALG.c_str());
    wmove(wlegend, 18, 2);
    waddstr(wlegend, LEG_PJF_ALG.c_str());

    wnoutrefresh(wlegend);
}

void PSAscreen::push_prc_in(WINDOW* w, std::vector<process>& prcs)
{
    wclear(w);
    int width = 1, height = 1;
    for (auto &p : prcs)
    {
	if (width >= W_W_PRC_DONE - 2)
	{
	    width = 1;
	    height += 1;
	}
	if (height >= W_H_PRC_DONE - 1)
	{
	    break;
	}
	wmove(w, height, width);
	colorinprocess(w, p.get_prty());
	waddstr(w, p.get_id().c_str());

	width += p.get_id().length() + 1;
    }
}

void PSAscreen::colorinprocess(WINDOW *w, priority pr)
{
    switch (pr)
    {
    case priority::LOW:
	wattron(w, COLOR_PAIR(1));
	break;
    case priority::MEDIUM:
	wattron(w, COLOR_PAIR(2));
	break;
    case priority::HIGH:
	wattron(w, COLOR_PAIR(3));
	break;
    case priority::EXTREME:
	wattron(w, COLOR_PAIR(5));
	break;
    case priority::NONE:
	wattron(w, COLOR_PAIR(8));
	break;
    }
}

void PSAscreen::show_awt(int awt)
{
    wmove(walg, 6, 2);
    waddstr(walg,  (commons::get_time(awt)).c_str());
}

void PSAscreen::show_process(process& pr)
{
    // This will color in the process
    colorinprocess(walg, pr.get_prty());

    wmove(walg, 2, 2);
    waddstr(walg, pr.get_id().c_str());

    // This clears the previous data, since it might be too long in chars
    wmove(walg, 3, 2);
    waddstr(walg, (commons::prtostr(pr.get_prty()) + "    ").c_str());

    // This clears the previous data, since it might be too long in chars
    wmove(walg, 4, 2);
    waddstr(walg, (std::to_string(pr.get_ttl()) + "    ").c_str());

    wattron(walg, COLOR_PAIR(6));
    wrefresh(walg);
}

void PSAscreen::draw_frame()
{
    box(stdscr, 0, 0);
    draw_small_arrows();
    wnoutrefresh(stdscr);
}

void PSAscreen::draw_frame_of(WINDOW *w, std::string title)
{
    wattron(w, COLOR_PAIR(8)); // keeps the border of the window white
    box(w, 0, 0);
    wmove(w, 0, 1);
    waddstr(w, title.c_str());
    wnoutrefresh(w);
}

PSAscreen::~PSAscreen()
{
    delwin(walg);
    delwin(wprc);
    delwin(wdone);
    delwin(wlegend);
    endwin();
}
