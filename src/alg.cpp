#include "process.h"
#include "alg.h"

alg::alg()
{
}

alg::alg(int awt) : average_wait_time(awt)
{
}

int alg::get_awt() const
{
    return average_wait_time;
}

alg::~alg()
{
}
