#ifndef __FCFS_H_INCLUDED__
#define __FCFS_H_INCLUDED__

#include "alg.h"

class fcfs : public alg
{
public:
    fcfs();
    ~fcfs();

    void work(std::vector<process*> processes);
private:
};

#endif
