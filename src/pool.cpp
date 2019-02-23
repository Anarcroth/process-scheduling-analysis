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
    // TODO this maybe should create a random process since it would be evaluated before each algorithm
    switch (ch)
    {
    case 'r':
	ready_queue.push_back(process());
	break;
    case 'l':;
	ready_queue.push_back(process(priority::LOW));
	break;
    case 'm':
	ready_queue.push_back(process(priority::MEDIUM));
	break;
    case 'h':
	ready_queue.push_back(process(priority::HIGH));
	break;
    case 'x':
	ready_queue.push_back(process(priority::EXTREME));
	break;
    }
}

void pool::push(process &prcs)
{
    ready_queue.push_back(prcs);
}

std::vector<process>& pool::r_q()
{
    return ready_queue;
}
