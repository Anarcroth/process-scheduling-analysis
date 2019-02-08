#ifndef __POOL_H_INCLUDED__
#define __POOL_H_INCLUDED__

#include <vector>

#include "process.h"

class pool
{
public:
    static pool& get();

    pool(pool const&)           = delete;
    void operator=(pool const&) = delete;

    void set_pool(std::vector<process> p);
    std::vector<process> get_pool();

private:
    pool();

    std::vector<process> processes;
};

#endif
