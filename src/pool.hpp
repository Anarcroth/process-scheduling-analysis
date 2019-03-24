#ifndef __POOL_H_INCLUDED__
#define __POOL_H_INCLUDED__

#include <vector>

#include "process.hpp"

namespace pool
{
    void make_pr(int ch);
    void eval_prcs_prty();
    void clear();

    bool empty();

    extern std::vector<process> wait_queue;
    extern std::vector<process> ready_queue;
    extern std::vector<process> done_queue;
}

#endif
