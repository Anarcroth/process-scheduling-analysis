#include <thread>
#include <chrono>
#include <utility>
#include <algorithm>

#include "scheduler.hpp"
#include "process.hpp"
#include "screen.hpp"
#include "pool.hpp"
#include "dispatcher.hpp"
#include "commons.hpp"

const int scheduler::TIME_QUANTUM = 50;

scheduler::scheduler() : average_wait_time(0) {}

int scheduler::get_awt() const
{
    return average_wait_time;
}

void scheduler::exec(std::vector<process>::iterator& pit, int tq)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(tq));
    average_wait_time += tq;
}

void scheduler::fcfs()
{
    average_wait_time = 0;
    pool::eval_prcs_prty();
    auto pit = pool::ready_queue.begin();
    while (pit != pool::ready_queue.end())
    {
	exec(pit, pit->get_ttl());

	dispatcher::context_switch(pit, pit->get_ttl());

	PSAscreen::get().draw_process_exec(average_wait_time, *pit, pool::done_queue);
    }
}

void scheduler::sjf()
{
    pool::eval_prcs_prty();
    std::sort(pool::ready_queue.begin(),
	      pool::ready_queue.end(),
	      [] (const process a, const process b) { return a.get_ttl() < b.get_ttl(); });

    average_wait_time = 0;
    auto pit = pool::ready_queue.begin();
    while (pit != pool::ready_queue.end())
    {
	exec(pit, pit->get_ttl());

	dispatcher::context_switch(pit, pit->get_ttl());

	PSAscreen::get().draw_process_exec(average_wait_time, *pit, pool::done_queue);
    }
}

void scheduler::round_rob()
{
    pool::eval_prcs_prty();
    average_wait_time = 0;
    auto pit = pool::ready_queue.begin();
    // TODO create pool::empty() method
    while (!pool::ready_queue.empty() || !pool::wait_queue.empty())
    {
	if (pit->has_io())
	{
	    exec(pit, TIME_QUANTUM / 2);
	    dispatcher::interrupt(pit, TIME_QUANTUM / 2);
	}
	else
	{
	    exec(pit, TIME_QUANTUM);
	    dispatcher::context_switch(pit, TIME_QUANTUM);
	}

	PSAscreen::get().show_awt(average_wait_time);
	PSAscreen::get().show_process(*pit);
    }
}
