#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include "process.hpp"

class scheduler
{
public:
    scheduler();

    int get_awt() const;

    void exec(std::vector<process>::iterator& pit);

    void fcfs();
    void sjf();
    void round_rob();

private:
    void eval_pool();

    int average_wait_time;

    static const int TIME_QUANTUM;
};

#endif
