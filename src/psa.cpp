#include <chrono>
#include <thread>
#include <vector>
#include <memory>

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
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	PSAscreen::get().draw_frame();
	PSAscreen::get().draw_frame_alg();
	PSAscreen::get().draw_frame_prc();
	PSAscreen::get().draw_frame_done();
	PSAscreen::get().draw_frame_legend();
	if ((ch = getch()) == ERR)
	{

	}
	else
	{
	    switch(ch)
	    {
	    case 'r':
		processes.push_back(new process());
	        PSAscreen::get().add_prc(processes);
		break;
	    case 's':
		f.work(processes);
		break;
	    }
	}
	doupdate();
    }

    for (std::vector<process*>::iterator it = processes.begin(); it != processes.end(); ++it)
    {
	delete (*it);
    }
    processes.clear();

    return 0;
}
