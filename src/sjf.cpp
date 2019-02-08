#include <algorithm>
#include <utility>

#include "sjf.h"
#include "process.h"

sjf::sjf(std::vector<process>&& prs) : alg(0, std::move(prs))
{
}

void sjf::work()
{
    std::sort(processes.begin(), processes.end(), [] (const process a, const process b) { return a.get_ttl() < b.get_ttl(); });
    exec();
}

void sjf::exec()
{
    alg::exec();
}
