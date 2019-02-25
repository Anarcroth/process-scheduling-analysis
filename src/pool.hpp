#ifndef __POOL_H_INCLUDED__
#define __POOL_H_INCLUDED__

#include <vector>

#include "process.hpp"

class pool
{
public:
    static pool& get();

    pool(pool const&)           = delete;
    void operator=(pool const&) = delete;

    void make_pr(int ch);
    void push(process& pr);

    std::vector<process>& r_q();
    std::vector<process>& w_q();
    std::vector<process>& d_q();

private:
    pool();

    std::vector<process> wait_queue;
    std::vector<process> ready_queue;
    std::vector<process> done_processes;
};

#endif
