#include <algorithm>
#include <chrono>
#include <thread>

#include "sjf.h"
#include "process.h"
#include "screen.h"

sjf::sjf(std::vector<process*> prs) : alg(0, prs)
{
}

void sjf::work()
{
    std::sort(processes.begin(), processes.end(), [] (const process* a, const process* b) { return a->get_ttl() < b->get_ttl(); });
    std::vector<process*> prs_sorted_by_ttl = processes;
    exec(prs_sorted_by_ttl);
}

void sjf::exec(std::vector<process*> &prs_sorted_by_ttl)
{
    average_wait_time = 0;
    std::vector<process*> done_processes;
    for (auto &p : prs_sorted_by_ttl)
    {
	PSAscreen::get().show_awt(average_wait_time);

	PSAscreen::get().show_process(p);
	std::this_thread::sleep_for(std::chrono::milliseconds(p->get_ttl()));

	done_processes.push_back(p);
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), done_processes);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");

	processes.erase(std::remove(processes.begin(), processes.end(), p), processes.end());
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");

	doupdate();

	average_wait_time += p->get_ttl();
    }
}

sjf::~sjf()
{
}
