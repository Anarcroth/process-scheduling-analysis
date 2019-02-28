#ifndef __POOL_H_INCLUDED__
#define __POOL_H_INCLUDED__

#include <vector>

#include "process.hpp"

namespace pool
{
    void make_pr(int ch);
    void eval_prcs_prty();

    std::vector<process>& wait_queue();
    std::vector<process>& ready_queue();
    std::vector<process>& done_queue();

    extern std::vector<process> wait_q;
    extern std::vector<process> ready_q;
    extern std::vector<process> done_q;
}

#endif
