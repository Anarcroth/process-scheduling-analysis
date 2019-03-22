#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include "process.hpp"

class scheduler
{
public:
    scheduler();

    void exec(int tq);
    void take(std::vector<process>::iterator& pit, int tq);

    void fcfs();
    void sjf();
    void round_rob();
    void pfj();

    static int avg_wt;        /* average waiting time in ready queue */
    static int avg_tat;       /* average turnaround time */
    static int total_t;       /* total time of execution*/
    static int prev_pr_burst; /* previous process burst */

private:
    void reset();

    int exponential_average(int prev_pr_ttl);

    static const double ALPHA;      /* weight of previous process execution */
    static const int TIME_QUANTUM;  /* time quantum */
};

#endif
