#include "process.h"
#include "alg.h"

alg::alg()
{
}

alg::alg(int awt, std::vector<process*> prs) : average_wait_time(awt), processes(prs)
{
}

int alg::get_awt() const
{
    return average_wait_time;
}

alg::~alg()
{
}
