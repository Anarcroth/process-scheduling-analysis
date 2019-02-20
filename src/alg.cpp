#include <thread>
#include <chrono>
#include <utility>
#include <algorithm>

#include "alg.hpp"
#include "process.hpp"
#include "screen.hpp"
#include "pool.hpp"

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
    auto pit = pool::get().r_q().begin();
    //std::thread ti(interrupt);
    while (!pool::get().r_q().empty())
    {
	std::this_thread::sleep_for(std::chrono::milliseconds(TIME_QUANTUM));
	int left_ttl = pit->get_ttl() - TIME_QUANTUM;
	average_wait_time += left_ttl;
	pit->set_ttl(left_ttl);
	if (left_ttl < 1)
	{
	    done_processes.push_back(std::move(*pit));
	    pit = pool::get().r_q().erase(pit);
	}
	else
	{
	    std::rotate(pool::get().r_q().begin(), pit + 1, pool::get().r_q().end());
	}

	PSAscreen::get().draw_process_exec(average_wait_time, *pit, done_processes);
    }
    //ti.join();
}

void scheduler::interrupt()
{

}
