#include "process.h"
#include "alg.h"

alg::alg()
{
}

alg::~alg()
{
    for (size_t i = 0; i < p_que.size(); i++)
    {
	delete &p_que.front();
    }
    // This clears the queue
    p_que = {};
}
