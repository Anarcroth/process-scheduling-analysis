#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include "process.hpp"

class scheduler
{
public:
    scheduler();

    void exec(std::vector<process>::iterator& pit, int tq);
    void take(std::vector<process>::iterator& pit, int tq);

    void fcfs();
    void sjf();
    void round_rob();
    void pfj();

    static int avg_wt;  /* average waiting time in ready queue */
    static int avg_tat; /* average turnaround time */
    static int total_t; /* total time of execution*/

private:
    void reset();

    static const int TIME_QUANTUM; /* time quantum */
};

#endif
