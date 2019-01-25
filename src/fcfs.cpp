#include <chrono>
#include <thread>

#include "fcfs.h"
#include "process.h"
#include <algorithm>

#include "screen.h"

fcfs::fcfs()
{
}

fcfs::~fcfs()
{
}

void fcfs::work(std::vector<process*> &processes)
{
    std::vector<process*> done_processes;
    std::vector<process*> copy_processes = processes;
    for (auto &p : copy_processes)
    {
	PSAscreen::get().show_process(p);
	std::this_thread::sleep_for(std::chrono::milliseconds(p->get_ttl()));

	done_processes.push_back(p);
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), done_processes);
	PSAscreen::get().draw_frame_done();

	processes.erase(std::remove(processes.begin(), processes.end(), p), processes.end());
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	PSAscreen::get().draw_frame_prc();

	doupdate();
    }
}
