#include <vector>

#include "process.h"
#include "priority.h"
#include "screen.h"
#include "fcfs.h"
#include "sjf.h"

int main()
{
    std::vector<process*> processes;
    int ch;
    while ((ch = getch()) != 'q')
    {
	if (ch == 'c')
	{
	    processes.push_back(new process());
	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	}
	if (ch == 'f')
	{
	    fcfs f(processes);
	    f.work();
	}
	if (ch == 's')
	{
	    sjf s(processes);
	    s.work();
	}

	PSAscreen::get().draw_frame();
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_walg(), " ALGORITHM ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wlegend(), " LEGEND ");
	doupdate();
    }

    for (std::vector<process*>::iterator it = processes.begin(); it != processes.end(); ++it)
    {
	delete (*it);
    }
    processes.clear();

    return 0;
}
