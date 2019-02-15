#include <thread>
#include <chrono>
#include <utility>
#include <algorithm>

#include "alg.hpp"
#include "process.hpp"
#include "screen.hpp"
#include "pool.hpp"

alg::alg() : average_wait_time(0) {}

int alg::get_awt() const
{
    return average_wait_time;
}

void alg::exec()
{
    average_wait_time = 0;

    std::vector<process> done_processes;

    auto pit = pool::get().get_pool().begin();
    while (pit != pool::get().get_pool().end())
    {
	PSAscreen::get().show_awt(average_wait_time);
	average_wait_time += pit->get_ttl();

	PSAscreen::get().show_process(*pit);
	std::this_thread::sleep_for(std::chrono::milliseconds(pit->get_ttl()));

	done_processes.push_back(*pit);
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), done_processes);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");

	pit = pool::get().get_pool().erase(pit);
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::get().get_pool());
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");

	doupdate();
    }
}

void alg::fcfs()
{
    exec();
}

void alg::sjf()
{
    std::sort(pool::get().get_pool().begin(),
	      pool::get().get_pool().end(),
	      [] (const process a, const process b) { return a.get_ttl() < b.get_ttl(); });
    exec();
}

void alg::round_rob()
{

}
