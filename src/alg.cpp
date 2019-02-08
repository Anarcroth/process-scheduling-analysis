#include <algorithm>
#include <chrono>
#include <thread>
#include <utility>

#include "alg.h"
#include "process.h"
#include "screen.h"

alg::alg(int awt, std::vector<process>&& prs) : average_wait_time(awt), processes(std::move(prs))
{
}

int alg::get_awt() const
{
    return average_wait_time;
}

void alg::work()
{
}

void alg::exec()
{
    average_wait_time = 0;
    std::vector<process> done_processes;
    std::vector<process> copy_processes = processes;
    for (auto &p : copy_processes)
    {
	PSAscreen::get().show_awt(average_wait_time);
	average_wait_time += p.get_ttl();

	PSAscreen::get().show_process(p);
	std::this_thread::sleep_for(std::chrono::milliseconds(p.get_ttl()));

	done_processes.push_back(p);
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), done_processes);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");

	//processes.erase(std::remove(processes.begin(), processes.end(), p), processes.end());
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");

	doupdate();
    }
}
