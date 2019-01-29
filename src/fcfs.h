#ifndef __FCFS_H_INCLUDED__
#define __FCFS_H_INCLUDED__

#include "alg.h"

class fcfs : public alg
{
public:
    fcfs(std::vector<process*> prs);
    ~fcfs();

    virtual void work() override;

private:
};

#endif
