#include <algorithm>
#include <utility>

#include "sjf.h"
#include "process.h"
#include "pool.h"

sjf::sjf() {}

void sjf::work()
{
    std::sort(pool::get().get_pool().begin(), pool::get().get_pool().end(), [] (const process a, const process b) { return a.get_ttl() < b.get_ttl(); });
    exec();
}

void sjf::exec()
{
    alg::exec();
}
