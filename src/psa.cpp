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
	if (ch == 'r')
	{
	    processes.push_back(new process());
	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	}
	else if (ch == 'l')
	{
	    processes.push_back(new process(priority::LOW));
	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	}
	else if (ch == 'm')
	{
	    processes.push_back(new process(priority::MEDIUM));
	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	}
	else if (ch == 'h')
	{
	    processes.push_back(new process(priority::HIGH));
	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	}
	else if (ch == 'x')
	{
	    processes.push_back(new process(priority::EXTREME));
	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
	}
	else if (ch == 'f')
	{
	    fcfs f(processes);
	    f.work();
	    processes.clear();
	}
	else if (ch == 's')
	{
	    sjf s(processes);
	    s.work();
	    processes.clear();
	}

	PSAscreen::get().draw_frame();
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_walg(), " ALGORITHM ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wlegend(), " LEGEND ");
	PSAscreen::get().draw_legend_cont();
	doupdate();
    }

    for (std::vector<process*>::iterator it = processes.begin(); it != processes.end(); ++it)
    {
	delete (*it);
    }
    processes.clear();

    return 0;
}
