#include <vector>
#include <memory>

#include "screen.hpp"
#include "alg.hpp"
#include "pool.hpp"

int main()
{
    scheduler ag;
    int ch;
    while ((ch = getch()) != 'q')
    {
	pool::get().make_pr(ch);
	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(),
				     pool::get().r_q());

	if (ch == 'f')
	{
	    ag.fcfs();
	}
	else if (ch == 's')
	{
	    ag.sjf();
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
