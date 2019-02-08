#include <vector>

#include "pool.h"

pool::pool()
{
}

pool& pool::get()
{
    static pool instance;
    return instance;
}

void set_pool(std::vector<process> p)
{
    processes = p;
}

std::vector<process> get_pool()
{
    return processes;
}
