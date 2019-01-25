#include <chrono>
#include <thread>

#include "fcfs.h"
#include "process.h"
#include "screen.h"

fcfs::fcfs()
{
}

fcfs::~fcfs()
{
}

void fcfs::work(std::vector<process*> &processes)
{
    for (auto &p : processes)
    {
	PSAscreen::get().show_process(p);
	std::this_thread::sleep_for(std::chrono::milliseconds(p->get_ttl()));
    }
    PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), processes);
}
