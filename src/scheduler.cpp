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

void scheduler::exec(std::vector<process>::iterator pit)
{
    average_wait_time += pit->get_ttl();
    std::this_thread::sleep_for(std::chrono::milliseconds(pit->get_ttl()));
    done_processes.push_back(*pit);
    pit = pool::get().r_q().erase(pit);
}

void scheduler::fcfs()
{
    average_wait_time = 0;
    auto pit = pool::get().r_q().begin();
    while (pit != pool::get().r_q().end())
    {
	exec(pit);
	PSAscreen::get().draw_process_exec(average_wait_time, *pit, done_processes);
    }
}

void scheduler::sjf()
{
    std::sort(pool::get().r_q().begin(),
	      pool::get().r_q().end(),
	      [] (const process a, const process b) { return a.get_ttl() < b.get_ttl(); });

    average_wait_time = 0;
    auto pit = pool::get().r_q().begin();
    while (pit != pool::get().r_q().end())
    {
	exec(pit);
	PSAscreen::get().draw_process_exec(average_wait_time, *pit, done_processes);
    }
}

void scheduler::round_rob()
{
    average_wait_time = 0;
    std::vector<process> ready_q = pool::get().r_q();
    auto pit = ready_q.begin();
    while (!ready_q.empty())
    {
	int next_cpu_burst = pit->get_ttl_passed() + TIME_QUANTUM;
	if (next_cpu_burst >= pit->get_next_io())
	{
	    int left_time_q = next_cpu_burst - pit->get_next_io();
	    std::this_thread::sleep_for(std::chrono::milliseconds(left_time_q));
	    dispatcher::interrupt();
	}
	else
	{
	    std::this_thread::sleep_for(std::chrono::milliseconds(TIME_QUANTUM));
	    dispatcher::context_switch(*pit, 19);
	}
	int left_ttl = pit->get_ttl() - TIME_QUANTUM;
	average_wait_time += left_ttl;
	pit->set_ttl(left_ttl);
	if (left_ttl < 1)
	{
	    done_processes.push_back(std::move(*pit));
	    pit = ready_q.erase(pit);
	}
	else
	{
	    std::rotate(ready_q.begin(), pit + 1, ready_q.end());
	}

	PSAscreen::get().draw_process_exec(average_wait_time, *pit, done_processes);
    }
}
