#include "process.h"
#include "alg.h"

alg::alg()
{
}

alg::~alg()
{
    for (auto it = queue.begin(); it != queue.end(); ++it)
    {
	delete (*it);
    }
    queue.clear();
}
