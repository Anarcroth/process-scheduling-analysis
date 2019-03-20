#include <vector>
#include <algorithm>
#include <thread>

#include "dispatcher.hpp"
#include "scheduler.hpp"
#include "pool.hpp"
#include "screen.hpp"

namespace dispatcher
{
    std::mutex iomutex;

    void interrupt(std::vector<process>::iterator& pit, int tq)
    {
	save_state(pit, tq);

	pool::wait_queue.push_back(std::move(*pit));
	pit = pool::ready_queue.erase(pit);

	std::thread iothread(dispatcher::exec_io, pool::wait_queue.begin());
	iothread.detach();
    }

    void context_switch(std::vector<process>::iterator& pit, int tq)
    {
	save_state(pit, tq);
	restore_state(pit);
    }

    void save_state(std::vector<process>::iterator& pit, int ttl_p)
    {
	pit->set_work_done(ttl_p);
    }

    void restore_state(std::vector<process>::iterator& pit)
    {
	if (pit->is_done())
	{
	    pit->set_toc(scheduler::tt - pit->get_tos());
	    PSAscreen::get().show_tat(pit->get_toc());
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

    void exec_io(std::vector<process>::iterator pit)
    {
	iomutex.lock();

	auto io_ttl = pit->get_ioops().begin();
	std::this_thread::sleep_for(std::chrono::milliseconds(*io_ttl));
	pit->add_tat(*io_ttl);
	io_ttl = pit->get_ioops().erase(io_ttl);

	pool::ready_queue.push_back(std::move(*pit));
	pool::wait_queue.erase(pit);

	iomutex.unlock();
    }
}
