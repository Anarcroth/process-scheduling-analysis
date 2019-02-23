#include <thread>
#include <chrono>

#include "dispatcher.hpp"
#include "scheduler.hpp"
#include "process.hpp"

namespace dispatcher
{
    void interrupt()
    {
	context_switch();
    }

    void context_switch(process& pr, int ttl)
    {
	save_state(pr, ttl);
	restore_state();
    }

    void save_state(process& pr, int ttl_p)
    {
	pr.set_ttl_passed(ttl_p);
	pr.set_next_io();
    }

    void restore_state()
    {

    }
}
