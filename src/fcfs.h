#ifndef __FCFS_H_INCLUDED__
#define __FCFS_H_INCLUDED__

#include <vector>

#include "alg.h"

class fcfs : public alg
{
public:
    fcfs();
    ~fcfs();

    virtual int get_awt() override;
    virtual void work(std::vector<process*> &processes) override;

private:
};

#endif
