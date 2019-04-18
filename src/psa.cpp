#include <vector>
#include <memory>

#include "screen.hpp"
#include "scheduler.hpp"
#include "pool.hpp"
#include "commons.hpp"

int main()
{
    scheduler schedule;
    int ch;
    while ((ch = getch()) != 'q')
    {
	pool::make_pr(ch);
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(),
				     pool::ready_queue);

	if (ch == 'f')
	{
	    schedule.fcfs();
	}
	else if (ch == 'h')
	{
	    schedule.sjf_v1();
	}
	else if (ch == 's')
	{
	    schedule.sjf_v2();
	}
	else if (ch == 'o')
	{
	    schedule.round_rob();
	}
	else if (ch == 'p')
	{
	    schedule.pjf();
	}
	else if (ch == 'c')
	{
	    schedule.cfs();
	}

	PSAscreen::get().draw_frame();
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_walg(), " ALGORITHM ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wlegend(), " LEGEND ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wwt(), " Waiting Time ");
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wtat(), " Turnaround Time ");
	PSAscreen::get().draw_legend_cont();
	doupdate();
    }

    return 0;
}
