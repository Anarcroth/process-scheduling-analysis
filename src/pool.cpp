#include <vector>

#include "pool.h"
#include "commons.h"
#include "priority.h"

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
	processes.push_back(process());
	break;
    case 'l':;
	processes.push_back(process(priority::LOW));
	break;
    case 'm':
	processes.push_back(process(priority::MEDIUM));
	break;
    case 'h':
	processes.push_back(process(priority::HIGH));
	break;
    case 'x':
	processes.push_back(process(priority::EXTREME));
	break;
    }
}

void pool::push(process &pr)
{
    processes.push_back(pr);
}

void pool::set_pool(std::vector<process> p)
{
    processes = p;
}

std::vector<process>& pool::get_pool()
{
    return processes;
}
