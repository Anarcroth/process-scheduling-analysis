#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include "process.hpp"

class scheduler
{
public:
    scheduler();

    int get_awt() const;

    void exec(std::vector<process>::iterator& pit, int tq);
    void take(std::vector<process>::iterator& pit, int tq);

    void fcfs();
    void sjf();
    void round_rob();
    void pfj();

    static int tt; /* total time of execution*/

private:
    void reset();

    int avg_wait_t; /* waiting time */

    static const int TIME_QUANTUM; /* time quantum */
};

#endif
