#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include "process.hpp"

class scheduler
{
public:
    scheduler();

    void exec(int tq);
    void take(std::vector<process>::iterator& pit, int tq);

    void fcfs();      /* first come first served */
    void sjf();       /* shortest job first */
    void round_rob(); /* round-robin */
    void pjf();       /* priority job first */

    static int avg_wt;        /* average waiting time in ready queue */
    static int avg_tat;       /* average turnaround time */
    static int total_t;       /* total time of execution*/
    static int prev_pr_burst; /* previous process burst */

private:
    void reset(); /* reset global variables */

    int exponential_average(int prev_pr_ttl);

    static const double ALPHA;      /* weight of previous process execution */
    static const int TIME_QUANTUM;  /* time quantum */
};

#endif
