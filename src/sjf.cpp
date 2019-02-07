#include <algorithm>
#include <chrono>
#include <thread>

#include "sjf.h"
#include "process.h"
#include "screen.h"

sjf::sjf(std::vector<std::unique_ptr<process>> prs) : alg(0, prs)
{
}

void sjf::work()
{
    std::sort(processes.begin(), processes.end(), [] (const process a, const process b) { return a.get_ttl() < b.get_ttl(); });
    exec();
}

void sjf::exec()
{
    average_wait_time = 0;
    std::vector<std::unique_ptr<process>> done_processes;
    std::vector<std::unique_ptr<process>> copy_processes = processes;
    for (auto &p : copy_processes)
    {
	PSAscreen::get().show_awt(average_wait_time);
	average_wait_time += p->get_ttl();

	PSAscreen::get().show_process(*p);
	std::this_thread::sleep_for(std::chrono::milliseconds(p->get_ttl()));

	done_processes.push_back(p);
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), done_processes);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");

	processes.erase(std::remove(processes.begin(), processes.end(), p), processes.end());
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");

	doupdate();
    }
}
