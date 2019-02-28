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

    std::vector<process>::iterator context_switch(std::vector<process>::iterator& pit, int ttl)
    {
	save_state(pit, ttl);
	auto prev_state = restore_state(pit);
	return prev_state;
    }

    void save_state(std::vector<process>::iterator& pit, int ttl_p)
    {
	pit->set_ttl_passed(ttl_p);
	pit->incr_next_io();
    }

    std::vector<process>::iterator restore_state(std::vector<process>::iterator& pit)
    {
	if (pit->get_ttl_passed() >= pit->get_ttl())
	{
	    pool::done_queue().push_back(std::move(*pit));
	    return pool::ready_queue().erase(pit);
	}
	else
	{
	    std::rotate(pool::ready_queue().begin(), pit + 1, pool::ready_queue().end());
	    return pit;
	}
    }
}
