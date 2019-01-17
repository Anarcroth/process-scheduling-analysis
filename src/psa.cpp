#include <chrono>
#include <thread>
#include <vector>
#include <memory>

#include "process.h"
#include "priority.h"
#include "screen.h"

int main()
{
    std::vector<process*> processes;
    PSAscreen scr;
    int ch;
    while (1)
    {
	std::this_thread::sleep_for(std::chrono::milliseconds(30));
	scr.draw_frame();
	scr.draw_frame_alg();
	scr.draw_frame_prc();
	scr.draw_frame_done();
	scr.draw_frame_legend();
	if ((ch = getch()) == ERR)
	{

	}
	else
	{
	    switch(ch)
	    {
	    case 'r':
		processes.push_back(new process());
		scr.add_prc(processes);
		break;
	    }
	}
	refresh();
    }

    for (std::vector<process*>::iterator it = processes.begin(); it != processes.end(); ++it)
    {
	delete (*it);
    }
    processes.clear();

    return 0;
}
