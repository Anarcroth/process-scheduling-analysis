#include <algorithm>

#include "pool.hpp"

namespace pool
{
    std::vector<process> wait_queue(0);
    std::vector<process> ready_queue(0);
    std::vector<process> done_queue(0);

    void make_pr(int ch)
    {
	switch (ch)
	{
	case 'r':
	    ready_queue.push_back(process());
	    break;
	case '0':
	    ready_queue.push_back(process(priority::PR0));
	    break;
	case '1':;
	    ready_queue.push_back(process(priority::PR1));
	    break;
	case '2':
	    ready_queue.push_back(process(priority::PR2));
	    break;
	case '3':
	    ready_queue.push_back(process(priority::PR3));
	    break;
	case '4':
	    ready_queue.push_back(process(priority::PR4));
	    break;
	case '5':
	    ready_queue.push_back(process(priority::PR5));
	    break;
	case '6':
	    ready_queue.push_back(process(priority::PR6));
	    break;
	}
    }

    void eval_prcs_prty()
    {
	for (auto& p : ready_queue)
	{
	    if (p.get_prty() != priority::NONE) // Skip already set priorities
		continue;
	    else if (p.get_ttl() < process::TTL_MEAN - 3 * process::TTL_STDDEV)
		p.set_prty(priority::PR0);
	    else if (p.get_ttl() < process::TTL_MEAN - 1.96 * process::TTL_STDDEV)
		p.set_prty(priority::PR1);
	    else if (p.get_ttl() < process::TTL_MEAN - process::TTL_STDDEV)
		p.set_prty(priority::PR2);
	    else if (p.get_ttl() < process::TTL_MEAN + process::TTL_STDDEV)
		p.set_prty(priority::PR3);
	    else if (p.get_ttl() < process::TTL_MEAN + 1.96 * process::TTL_STDDEV)
		p.set_prty(priority::PR4);
	    else if (p.get_ttl() < process::TTL_MEAN + 3 * process::TTL_STDDEV)
		p.set_prty(priority::PR5);
	    else
		p.set_prty(priority::PR6);
	}
    }

    void clear()
    {
	done_queue.clear();
    }

    bool empty()
    {
	return (ready_queue.empty() && wait_queue.empty()) ? true : false;
    }

    int size()
    {
	return ready_queue.size() + wait_queue.size() + done_queue.size();
    }

    int pr_size()
    {
	return ready_queue.size() + wait_queue.size();
    }
}
