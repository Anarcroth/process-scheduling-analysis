#include <vector>
#include <memory>

#include "process.h"
#include "priority.h"
#include "screen.h"
#include "fcfs.h"
#include "sjf.h"
#include "commons.h"

int main()
{
    std::vector<std::unique_ptr<process>> pool;
    int ch;
    while ((ch = getch()) != 'q')
    {
	commons::get().make_pr((ch), pool);
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool);

	if (ch == 'f')
	{
	    fcfs f(pool);
	    f.work();
	}
	else if (ch == 's')
	{
	    sjf s(pool);
	    s.work();
	}

	PSAscreen::get().draw_frame();
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_walg(), " ALGORITHM ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wlegend(), " LEGEND ");
	PSAscreen::get().draw_legend_cont();
	doupdate();
    }

    return 0;
}
