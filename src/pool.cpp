#include <algorithm>
#include <thread>
#include <chrono>
#include "pool.hpp"
#include "screen.hpp"

namespace pool
{
    std::vector<process> wait_q(0);
    std::vector<process> ready_q(0);
    std::vector<process> done_q(0);

    void make_pr(int ch)
    {
	// TODO this maybe should create a random process since it would be evaluated before each algorithm
	switch (ch)
	{
	case 'r':
	    ready_q.push_back(process());
	    break;
	case 'l':;
	    ready_q.push_back(process(priority::LOW));
	    break;
	case 'm':
	    ready_q.push_back(process(priority::MEDIUM));
	    break;
	case 'h':
	    ready_q.push_back(process(priority::HIGH));
	    break;
	case 'x':
	    ready_q.push_back(process(priority::EXTREME));
	    break;
	}
    }

    void eval_prcs_prty()
    {
	int sum_of_ttls = 0;
	std::for_each(ready_q.begin(),
		      ready_q.end(),
		      [&] (process& p) {
			  sum_of_ttls += p.get_ttl();
		      });
	int average_ttl = sum_of_ttls / ready_q.size();
	int quota = average_ttl / 4;
	for (auto& p : ready_q)
	{
	    if (p.get_ttl() < 730) p.set_prty(priority::LOW);
	    else if (p.get_ttl() < 1000) p.set_prty(priority::MEDIUM);
	    else if (p.get_ttl() < 1270) p.set_prty(priority::HIGH);
	    else if (p.get_ttl() < 1540) p.set_prty(priority::EXTREME);
	    else p.set_prty(priority::EXTREME);
	}
    }

    std::vector<process>& wait_queue()
    {
	return wait_q;
    }

    std::vector<process>& ready_queue()
    {
	return ready_q;
    }

    std::vector<process>& done_queue()
    {
	return done_q;
    }
}
