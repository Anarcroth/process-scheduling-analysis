#ifndef __FCFS_H_INCLUDED__
#define __FCFS_H_INCLUDED__

#include <vector>

#include "alg.h"

class fcfs : public alg
{
public:
    fcfs();
    ~fcfs();

    int get_awt();
    void work(std::vector<process*> &processes);

private:
    int average_wait_time;
};

#endif
