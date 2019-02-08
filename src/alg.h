#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include <vector>

#include "process.h"

class alg
{
public:
    alg(int awt, std::vector<process>&& prs);

    int get_awt() const;

    virtual void work();
    virtual void exec();

    int average_wait_time;
    std::vector<process> processes;
};

#endif
