#ifndef __POOL_H_INCLUDED__
#define __POOL_H_INCLUDED__

#include <vector>

#include "pcb.h"

class pool
{
public:
    static pool& get();

    pool(pool const&)           = delete;
    void operator=(pool const&) = delete;

    void make_pr(int ch);
    void push(process& pr);

    void set_pool(std::vector<pcb> p);
    std::vector<pcb>& get_pool();

private:
    pool();

    std::vector<process> processes;
};

#endif
