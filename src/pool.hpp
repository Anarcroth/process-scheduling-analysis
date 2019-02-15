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

    std::vector<process>& get_pool();

private:
    pool();

    std::vector<process> process_pool;
};

#endif
