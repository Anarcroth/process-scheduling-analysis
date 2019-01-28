#include <algorithm>
#include <chrono>
#include <thread>

#include "sjf.h"
#include "process.h"
#include "screen.h"

bool sort_by_pr_ttl(const process* a, const process* b);

sjf::sjf() : alg(0)
{
}

sjf::~sjf()
{
}

int sjf::get_awt()
{
    return average_wait_time;
}

void sjf::work(std::vector<process*> &processes)
{
    average_wait_time = 0;

    std::vector<process*> done_processes;
    std::sort(processes.begin(), processes.end(), sort_by_pr_ttl);
    std::vector<process*> copy_processes = processes;

    for (auto &p : copy_processes)
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

bool sort_by_pr_ttl(const process* a, const process* b)
{
    return a->get_ttl() < b->get_ttl();
}
