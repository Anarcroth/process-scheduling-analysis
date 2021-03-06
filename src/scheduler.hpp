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
    void sjf_v1();    /* shortest job first basic version */
    void sjf_v2();    /* shortest job first approximation version */
    void round_rob(); /* round-robin */
    void pjf();       /* priority job first */
    void cfs();       /* completely fair scheduler */

    static void calc_current_awt(std::vector<process> d_queue);
    static void calc_current_tat(std::vector<process> d_queue);

    static int avg_wt;        /* average waiting time in ready queue */
    static int avg_tat;       /* average turnaround time */
    static int total_t;       /* total time of execution*/
    static int prev_pr_burst; /* previous process burst */

    static int current_awt;   /* current average waiting time */
    static int current_tat;   /* current average turnaround time */

private:
    void reset(); /* reset global variables */

    void add_summary(std::string algname); /* add newest summary stats */

    int exponential_average(int prev_pr_ttl); /* calc expo average */

    std::vector<std::string> summaries; /* summaries of executions */

    static const double ALPHA;      /* weight of previous process execution */
    static const int TIME_QUANTUM;  /* time quantum */
};

#endif
