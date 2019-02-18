#include <thread>
#include <chrono>
#include <utility>
#include <algorithm>

#include "alg.hpp"
#include "process.hpp"
#include "screen.hpp"
#include "pool.hpp"

const int alg::TIME_QUANTUM = 50;

alg::alg() : average_wait_time(0) {}

int alg::get_awt() const
{
    return average_wait_time;
}

void alg::exec(std::vector<process>::iterator pit)
{
    average_wait_time += pit->get_ttl();
    std::this_thread::sleep_for(std::chrono::milliseconds(pit->get_ttl()));
    done_processes.push_back(*pit);
    pit = pool::get().r_q().erase(pit);
}

void alg::fcfs()
{
    average_wait_time = 0;
    auto pit = pool::get().r_q().begin();
    while (pit != pool::get().r_q().end())
    {
	exec(pit);
	PSAscreen::get().draw_process_exec(average_wait_time, *pit, done_processes);
    }
}

void alg::sjf()
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

void alg::round_rob()
{

}
