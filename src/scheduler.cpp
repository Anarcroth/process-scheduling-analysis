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

void scheduler::exec(std::vector<process>::iterator& pit)
{
    average_wait_time += pit->get_ttl();
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
	exec(pit);
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
	exec(pit);
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
	int next_cpu_burst = pit->get_ttl_passed() + TIME_QUANTUM;
	if (next_cpu_burst >= pit->get_next_io())
	{
	    int left_time_q = next_cpu_burst - pit->get_next_io();
	    std::this_thread::sleep_for(std::chrono::milliseconds(left_time_q));
	    dispatcher::context_switch(pit, left_time_q);
	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
	    PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	}
	else
	{
	    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_QUANTUM));
	    dispatcher::context_switch(pit, TIME_QUANTUM);
	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), pool::done_queue);
	    PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
	}
	average_wait_time += TIME_QUANTUM;

	PSAscreen::get().show_awt(average_wait_time);
	PSAscreen::get().show_process(*pit);

	doupdate();
    }
}
