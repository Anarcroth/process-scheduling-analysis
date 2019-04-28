#ifndef __SCREEN_H_INCLUDED__
#define __SCREEN_H_INCLUDED__

#include <vector>
#include <memory>
#include <ncurses.h>
#include <fstream>

#include "process.hpp"

class PSAscreen
{
public:
    static PSAscreen& get();

    PSAscreen(PSAscreen const&)      = delete;
    void operator=(PSAscreen const&) = delete;

    void draw_frame();
    void draw_frame_of(WINDOW *w, std::string title);

    void draw_small_arrows();
    void draw_legend_cont();
    void draw_w_scale();

    void clear_scr();

    void update_process_scr(process& pr);

    void show_wt(std::vector<process> dq, int wt);
    void show_tat(int tat);
    void show_statistics(std::vector<std::string>& summaries);
    void show_process(process& pr);
    void show_alg_info(std::string alg);

    void push_prc_in(WINDOW* w, std::vector<process>& pcbs);

    void get_table_partitionings();

    WINDOW* get_walg() const;
    WINDOW* get_wprc() const;
    WINDOW* get_wdone() const;
    WINDOW* get_wlegend() const;
    WINDOW* get_wwt() const;
    WINDOW* get_wtat() const;

private:
    PSAscreen();
    ~PSAscreen();

    void init();
    void colorinprocess(WINDOW *w, priority pr);

    static float x_partitioning;
    static float y_max;

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

    static const int W_X_WT;
    static const int W_Y_WT;
    static const int W_W_WT;
    static const int W_H_WT;

    static const int W_X_TAT;
    static const int W_Y_TAT;
    static const int W_W_TAT;
    static const int W_H_TAT;

    static const std::string LEG_PR;
    static const std::string LEG_PR0;
    static const std::string LEG_PR1;
    static const std::string LEG_PR2;
    static const std::string LEG_PR3;
    static const std::string LEG_PR4;
    static const std::string LEG_PR5;
    static const std::string LEG_PR6;
    static const std::string LEG_PRR;
    static const std::string LEG_ALG;
    static const std::string LEG_FCFS_ALG;
    static const std::string LEG_SJFV1_ALG;
    static const std::string LEG_SJFV2_ALG;
    static const std::string LEG_RR_ALG;
    static const std::string LEG_PJF_ALG;
    static const std::string LEG_CFS_ALG;

    static const int PR0COLOR;
    static const int PR1COLOR;
    static const int PR2COLOR;
    static const int PR3COLOR;
    static const int PR4COLOR;
    static const int PR5COLOR;
    static const int PR6COLOR;
    static const int PR7COLOR;

    WINDOW *walg;
    WINDOW *wprc;
    WINDOW *wdone;
    WINDOW *wlegend;
    WINDOW *wwt;
    WINDOW *wtat;
};

#endif
