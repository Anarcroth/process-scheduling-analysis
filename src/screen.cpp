#include <string>
#include <vector>

#include "screen.hpp"
#include "process.hpp"
#include "commons.hpp"
#include "pool.hpp"

float PSAscreen::x_partitioning = 0;
float PSAscreen::y_max = 0;

const int PSAscreen::W_Y_ALG = 1;
const int PSAscreen::W_X_ALG = 1;
const int PSAscreen::W_W_ALG = 132;
const int PSAscreen::W_H_ALG = 39;

const int PSAscreen::W_Y_PRC = 40;
const int PSAscreen::W_X_PRC = 1;
const int PSAscreen::W_Y_DONE = 40;
const int PSAscreen::W_X_DONE = 72;
const int PSAscreen::W_W_PRC_DONE = 61;
const int PSAscreen::W_H_PRC_DONE = 12;

const int PSAscreen::W_Y_LEGEND = 1;
const int PSAscreen::W_X_LEGEND = 133;
const int PSAscreen::W_W_LEGEND = 57;
const int PSAscreen::W_H_LEGEND = 51;

const int PSAscreen::W_Y_WT = 24;
const int PSAscreen::W_X_WT = 2;
const int PSAscreen::W_W_WT = 60;
const int PSAscreen::W_H_WT = 15;

const int PSAscreen::W_Y_TAT = 24;
const int PSAscreen::W_X_TAT = 72;
const int PSAscreen::W_W_TAT = 60;
const int PSAscreen::W_H_TAT = 15;

const std::string PSAscreen::LEG_PR = " Processes ";
const std::string PSAscreen::LEG_PR0 = "Priority 0: (0)";
const std::string PSAscreen::LEG_PR1 = "Priority 1: (1)";
const std::string PSAscreen::LEG_PR2 = "Priority 2: (2)";
const std::string PSAscreen::LEG_PR3 = "Priority 3: (3)";
const std::string PSAscreen::LEG_PR4 = "Priority 4: (4)";
const std::string PSAscreen::LEG_PR5 = "Priority 5: (5)";
const std::string PSAscreen::LEG_PR6 = "Priority 6: (6)";
const std::string PSAscreen::LEG_PRR = "Random Pri: (r)";
const std::string PSAscreen::LEG_ALG = " Algorithm ";
const std::string PSAscreen::LEG_FCFS_ALG = "First Come First Serve: FCFS (f)";
const std::string PSAscreen::LEG_SJFV1_ALG = "Shortest Job First (V1): SJF1 (h)";
const std::string PSAscreen::LEG_SJFV2_ALG = "Shortest Job First (V2): SJF2 (s)";
const std::string PSAscreen::LEG_RR_ALG = "Round Robbin: RR (o)";
const std::string PSAscreen::LEG_PJF_ALG = "Priority Job First: PJF (p)";
const std::string PSAscreen::LEG_CFS_ALG = "Completely Fair Scheduler: CFS (c)";

const int PSAscreen::PR0COLOR = 100;
const int PSAscreen::PR1COLOR = 101;
const int PSAscreen::PR2COLOR = 102;
const int PSAscreen::PR3COLOR = 103;
const int PSAscreen::PR4COLOR = 104;
const int PSAscreen::PR5COLOR = 105;
const int PSAscreen::PR6COLOR = 106;
const int PSAscreen::PR7COLOR = 107;

PSAscreen::PSAscreen()
{
    // Makes basic setup and starts colors
    init();

    walg = newwin(W_H_ALG, W_W_ALG, W_Y_ALG, W_X_ALG);
    wprc = newwin(W_H_PRC_DONE, W_W_PRC_DONE, W_Y_PRC, W_X_PRC);
    wdone = newwin(W_H_PRC_DONE, W_W_PRC_DONE, W_Y_DONE, W_X_DONE);
    wlegend = newwin(W_H_LEGEND, W_W_LEGEND, W_Y_LEGEND, W_X_LEGEND);
    wwt = newwin(W_H_WT, W_W_WT, W_Y_WT, W_X_WT);
    wtat = newwin(W_H_TAT, W_W_TAT, W_Y_TAT, W_X_TAT);

    wattron(walg, A_BOLD);
    wattron(wprc, A_BOLD);
    wattron(wdone, A_BOLD);
    wattron(wlegend, A_BOLD);
    wattron(wwt, A_BOLD);
    wattron(wtat, A_BOLD);
}

void PSAscreen::init()
{
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    if (has_colors() == FALSE) {
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
    init_color(PR7COLOR, 321, 545, 1000);
    init_pair(1, PR0COLOR, COLOR_BLACK);
    init_pair(2, PR1COLOR, COLOR_BLACK);
    init_pair(3, PR2COLOR, COLOR_BLACK);
    init_pair(4, PR3COLOR, COLOR_BLACK);
    init_pair(5, PR4COLOR, COLOR_BLACK);
    init_pair(6, PR5COLOR, COLOR_BLACK);
    init_pair(7, PR6COLOR, COLOR_BLACK);
    init_pair(8, PR7COLOR, COLOR_BLACK);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
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

WINDOW* PSAscreen::get_wwt() const
{
    return wwt;
}

WINDOW* PSAscreen::get_wtat() const
{
    return wtat;
}

void PSAscreen::draw_small_arrows()
{
    // This draws the small arrowsp between the
    // Process and Done windows
    move(43, W_W_PRC_DONE + 5);
    addch(ACS_RARROW);
    addch(ACS_RARROW);
    move(48, W_W_PRC_DONE + 5);
    addch(ACS_RARROW);
    addch(ACS_RARROW);
}

void PSAscreen::draw_legend_cont()
{
    // Creates the Process and Algorithm sub-windows
    wattron(wlegend, COLOR_PAIR(9));
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
    waddstr(wlegend, (LEG_PR0 + "    ").c_str());
    wattron(wlegend, COLOR_PAIR(2));
    waddstr(wlegend, (LEG_PR1 + "    ").c_str());
    wattron(wlegend, COLOR_PAIR(3));
    waddstr(wlegend, LEG_PR2.c_str());

    wmove(wlegend, 6, 2);
    wattron(wlegend, COLOR_PAIR(4));
    waddstr(wlegend, (LEG_PR3 + "    ").c_str());
    wattron(wlegend, COLOR_PAIR(5));
    waddstr(wlegend, (LEG_PR4 + "    ").c_str());
    wattron(wlegend, COLOR_PAIR(6));
    waddstr(wlegend, LEG_PR5.c_str());

    wmove(wlegend, 8, 2);
    wattron(wlegend, COLOR_PAIR(7));
    waddstr(wlegend, (LEG_PR6 + "    ").c_str());
    wattron(wlegend, COLOR_PAIR(9));
    waddstr(wlegend, LEG_PRR.c_str());

    // Adds different Algorithms
    wmove(wlegend, 12, 2);
    waddstr(wlegend, LEG_FCFS_ALG.c_str());
    wmove(wlegend, 14, 2);
    waddstr(wlegend, LEG_SJFV1_ALG.c_str());
    wmove(wlegend, 16, 2);
    waddstr(wlegend, LEG_SJFV2_ALG.c_str());
    wmove(wlegend, 18, 2);
    waddstr(wlegend, LEG_RR_ALG.c_str());
    wmove(wlegend, 20, 2);
    waddstr(wlegend, LEG_PJF_ALG.c_str());
    wmove(wlegend, 22, 2);
    waddstr(wlegend, LEG_CFS_ALG.c_str());


    wnoutrefresh(wlegend);
}

void PSAscreen::update_process_scr(process& pr)
{
    show_process(pr);
    push_prc_in(wprc, pool::ready_queue);
    draw_frame_of(wprc, " PROCESS ");
}

void PSAscreen::push_prc_in(WINDOW* w, std::vector<process>& prcs)
{
    wclear(w);
    int width = 1, height = 1;
    for (auto &p : prcs) {
	if (width >= W_W_PRC_DONE - 2) {
	    width = 1;
	    height += 1;
	}

	if (height >= W_H_PRC_DONE - 1)
	    break;

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
    case priority::PR0:
	wattron(w, COLOR_PAIR(1));
	break;
    case priority::PR1:
	wattron(w, COLOR_PAIR(2));
	break;
    case priority::PR2:
	wattron(w, COLOR_PAIR(3));
	break;
    case priority::PR3:
	wattron(w, COLOR_PAIR(4));
	break;
    case priority::PR4:
	wattron(w, COLOR_PAIR(5));
	break;
    case priority::PR5:
	wattron(w, COLOR_PAIR(6));
	break;
    case priority::PR6:
	wattron(w, COLOR_PAIR(7));
	break;
    case priority::NONE:
	wattron(w, COLOR_PAIR(9));
	break;
    }
}

void PSAscreen::show_wt(std::vector<process> dq, int wt)
{
    wattron(wwt, COLOR_PAIR(8));

    int x = std::floor(x_partitioning * dq.size() + 1);
    int y = std::floor((wt / y_max) * 13);

    wmove(wwt, 13 - y, x);
    waddstr(wwt, "*");
    wnoutrefresh(wwt);
}

void PSAscreen::get_table_partitionings()
{
    // needs to be calculated only once each algorithm
    x_partitioning = 52 / pool::size();
    y_max = pool::size() * 1500;
}

void PSAscreen::show_tat(int tat)
{
    wattron(walg, COLOR_PAIR(9));
    wmove(walg, 8, 2);
    waddstr(walg, ("Average Turnaround time: " +
		   std::to_string(tat) + "    ").c_str());
}

void PSAscreen::show_statistics(std::vector<std::string>& summaries)
{
    short int curr_summary_size = 0;
    if (summaries.size() > 10)
	curr_summary_size = 10;
    else
	curr_summary_size = summaries.size();

    // shows the first statistic and highlights it
    wattron(walg, COLOR_PAIR(8));
    wmove(walg, 8, 2);
    waddstr(walg, summaries.at(0).c_str());

    wattron(walg, COLOR_PAIR(9));
    for (size_t i = 1; i < curr_summary_size; i++) {
	wmove(walg, 8 + i, 2);
	waddstr(walg, summaries.at(i).c_str());
    }
    wrefresh(walg);
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

    wrefresh(walg);
}

void PSAscreen::show_alg_info(std::string alg)
{
    // Reset the screen from the leftovers from the previous data.
    wclear(wlegend);
    draw_frame_of(wlegend, " LEGEND ");
    draw_legend_cont();

    std::ifstream algfile;
    if (alg == "FCFS")
	algfile.open("fcfs.txt");
    else if (alg == "SJF")
	algfile.open("sjf.txt");
    else if (alg == "RR")
	algfile.open("rr.txt");
    else if (alg == "PJF")
	algfile.open("pjf.txt");
    else if (alg == "CFS")
	algfile.open("cfs.txt");

    std::string line;
    std::vector<std::string> text;
    if (algfile.is_open()) {
	while (getline(algfile, line))
	    text.push_back(line);
	algfile.close();
    }
    int i = 0;
    for (auto t : text) {
	wmove(wlegend, 24 + i, 2);
	waddstr(wlegend, t.c_str());
	i += 1;
    }
    wnoutrefresh(wlegend);
}

void PSAscreen::draw_frame()
{
    box(stdscr, 0, 0);
    draw_small_arrows();
    wnoutrefresh(stdscr);
}

void PSAscreen::draw_frame_of(WINDOW *w, std::string title)
{
    wattron(w, COLOR_PAIR(9)); // keeps the border of the window white
    box(w, 0, 0);
    wmove(w, 0, 1);
    waddstr(w, title.c_str());
    // The wt and tat windows should always have their scales drawn
    // makes sure to do that
    if (w == wwt)
	draw_w_scale();

    wnoutrefresh(w);
}

void PSAscreen::draw_w_scale()
{
    wattron(wwt, COLOR_PAIR(9));
    for (int i = 1; i < 14; i++) {
	wmove(wwt, 14 - i, 0);
	std::string scale_num = std::to_string(
	    std::floor(i * (y_max / 13)));
	scale_num = scale_num.substr(0, scale_num.find("."));

	if (scale_num.length() < 4)
	    scale_num = "." + scale_num.substr(0, 1) + "k";
	else if (scale_num.length() < 5)
	    scale_num = scale_num.substr(0, 1) + "k ";
	else
	    scale_num = scale_num.substr(0, 2) + "k";

	waddstr(wwt, scale_num.c_str());
    }
    wnoutrefresh(wwt);
}

void PSAscreen::clear_scr()
{
    wclear(wwt);
    PSAscreen::get().draw_frame_of(
	PSAscreen::get().get_wwt(), " Waiting Time ");
}

PSAscreen::~PSAscreen()
{
    delwin(walg);
    delwin(wprc);
    delwin(wdone);
    delwin(wlegend);
    endwin();
}
