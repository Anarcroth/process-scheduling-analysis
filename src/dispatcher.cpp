#include <thread>
#include <vector>
#include <chrono>
#include <algorithm>

#include "dispatcher.hpp"
#include "scheduler.hpp"
#include "process.hpp"
#include "pool.hpp"

namespace dispatcher
{
    void interrupt()
    {
	//context_switch();
    }

    void context_switch(std::vector<process>::iterator& pit, int ttl)
    {
	save_state(pit, ttl);
	restore_state(pit);
    }

    void save_state(std::vector<process>::iterator& pit, int ttl_p)
    {
	// TODO this might be called way too often for its own good
	pit->set_ttl_passed(ttl_p);
	pit->incr_next_io();
    }

    void restore_state(std::vector<process>::iterator& pit)
    {
	if (pit->get_ttl_passed() >= pit->get_ttl())
	{
	    pool::done_queue.push_back(std::move(*pit));
	    pit = pool::ready_queue.erase(pit);
	}
	else
	{
	    std::rotate(pool::ready_queue.begin(), pit + 1, pool::ready_queue.end());
	}
    }
}
