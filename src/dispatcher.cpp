#include <vector>
#include <algorithm>

#include "dispatcher.hpp"
#include "scheduler.hpp"
#include "pool.hpp"
#include "screen.hpp"

namespace dispatcher
{
    void interrupt(std::vector<process>::iterator& pit, int tq)
    {
	// TODO create a thread to work on the IO
	// remove one process io from pit
	context_switch(pit, tq);
    }

    void context_switch(std::vector<process>::iterator& pit, int tq)
    {
	save_state(pit, tq);
	restore_state(pit);
    }

    void save_state(std::vector<process>::iterator& pit, int ttl_p)
    {
	pit->set_ttl_passed(ttl_p);
    }

    void restore_state(std::vector<process>::iterator& pit)
    {
	if (pit->is_done())
	{
	    pool::done_queue.push_back(std::move(*pit));
	    pit = pool::ready_queue.erase(pit);

	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), pool::done_queue);
	    PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
	}
	else
	{
	    std::rotate(pool::ready_queue.begin(), pit + 1, pool::ready_queue.end());

	    PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
	    PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	}
    }
}
