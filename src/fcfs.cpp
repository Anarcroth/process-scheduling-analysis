#include "fcfs.h"
#include "process.h"

fcfs::fcfs(std::vector<process>&& prs) : alg(0, std::move(prs))
{
}

void fcfs::work()
{
    exec();
}

void fcfs::exec()
{
    alg::exec();
}
