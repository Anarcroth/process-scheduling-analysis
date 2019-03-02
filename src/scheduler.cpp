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

void scheduler::exec(std::vector<process>::iterator& pit, int awt)
{
    average_wait_time += awt;
    std::this_thread::sleep_for(std::chrono::milliseconds(pit->get_ttl()));
    pool::done_queue.push_back(*pit);
    pit = pool::ready_queue.erase(pit);
}

void scheduler::fcfs()
{
    average_wait_time = 0;
    auto pit = pool::ready_queue.begin();
    while (pit != pool::ready_queue.end())
    {
	exec(pit, pit->get_ttl_passed());
	PSAscreen::get().draw_process_exec(average_wait_time, *pit, pool::done_queue);
    }
}

void scheduler::sjf()
{
    std::sort(pool::ready_queue.begin(),
	      pool::ready_queue.end(),
	      [] (const process a, const process b) { return a.get_ttl() < b.get_ttl(); });

    average_wait_time = 0;
    auto pit = pool::ready_queue.begin();
    while (pit != pool::ready_queue.end())
    {
	exec(pit, pit->get_ttl_passed());
	PSAscreen::get().draw_process_exec(average_wait_time, *pit, pool::done_queue);
    }
}

void scheduler::round_rob()
{
    pool::eval_prcs_prty();
    average_wait_time = 0;
    auto pit = pool::ready_queue.begin();
    while (!pool::ready_queue.empty())
    {
	if (pit->has_io())
	{
	    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_QUANTUM / 2));
	    average_wait_time += TIME_QUANTUM / 2;
	    if (pit->is_done())
	    {
		pool::done_queue.push_back(std::move(*pit));
		pit = pool::ready_queue.erase(pit);

		PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), pool::done_queue);
		PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
	    }
	    else
	    {
		PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
		PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	    }
	    dispatcher::interrupt(pit, TIME_QUANTUM / 2);
	}
	else
	{
	    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_QUANTUM));
	    average_wait_time += TIME_QUANTUM;
	    if (pit->is_done())
	    {
		pool::done_queue.push_back(std::move(*pit));
		pit = pool::ready_queue.erase(pit);

		PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), pool::done_queue);
		PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
	    }
	    else
	    {
		PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
		PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	    }
	    dispatcher::context_switch(pit, TIME_QUANTUM);
	}


	PSAscreen::get().show_awt(average_wait_time);
	PSAscreen::get().show_process(*pit);

	doupdate();
    }
}
