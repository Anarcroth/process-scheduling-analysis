#include "alg.h"
#include "process.h"

alg::alg(int awt, std::vector<std::unique_ptr<process>> prs) : average_wait_time(awt), processes(prs)
{
}

int alg::get_awt() const
{
    return average_wait_time;
}
