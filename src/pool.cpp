#include "pool.hpp"

pool::pool()
{
}

pool& pool::get()
{
    static pool instance;
    return instance;
}

void pool::make_pr(int ch)
{
    switch (ch)
    {
    case 'r':
	process_pool.push_back(process());
	break;
    case 'l':;
	process_pool.push_back(process(priority::LOW));
	break;
    case 'm':
	process_pool.push_back(process(priority::MEDIUM));
	break;
    case 'h':
	process_pool.push_back(process(priority::HIGH));
	break;
    case 'x':
	process_pool.push_back(process(priority::EXTREME));
	break;
    }
}

void pool::push(process &prcs)
{
    process_pool.push_back(prcs);
}

std::vector<process>& pool::get_pool()
{
    return process_pool;
}
