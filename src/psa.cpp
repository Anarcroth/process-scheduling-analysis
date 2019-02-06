#include <vector>

#include "process.h"
#include "priority.h"
#include "screen.h"
#include "fcfs.h"
#include "sjf.h"

int main()
{
    std::vector<process*> pool;
    int ch;
    while ((ch = getch()) != 'q')
    {
	switch (ch)
	{
	case 'r':
	    pool.push_back(new process());
	    break;
	case 'l':
	    pool.push_back(new process(priority::LOW));
	    break;
	case 'm':
	    pool.push_back(new process(priority::MEDIUM));
	    break;
	case 'h':
	    pool.push_back(new process(priority::HIGH));
	    break;
	case 'x':
	    pool.push_back(new process(priority::EXTREME));
	    break;
	}
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool);

	if (ch == 'f')
	{
	    fcfs f(pool);
	    f.work();
	    pool.clear();
	}
	else if (ch == 's')
	{
	    sjf s(pool);
	    s.work();
	    pool.clear();
	}

	PSAscreen::get().draw_frame();
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_walg(), " ALGORITHM ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wlegend(), " LEGEND ");
	PSAscreen::get().draw_legend_cont();
	doupdate();
    }

    for (std::vector<process*>::iterator it = pool.begin(); it != pool.end(); ++it)
    {
	delete (*it);
    }
    pool.clear();

    return 0;
}
