#include <vector>

#include "process.h"
#include "priority.h"
#include "screen.h"
#include "fcfs.h"

int main()
{
    std::vector<process*> processes;
    fcfs f;
    int ch;
    while (1)
    {
	if ((ch = getch()) == ERR)
	{

	}
	else
	{
	    switch(ch)
	    {
	    case 'r':
		processes.push_back(new process());
		PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), processes);
		break;
	    case 's':
		f.work(processes);
		break;
	    }
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
