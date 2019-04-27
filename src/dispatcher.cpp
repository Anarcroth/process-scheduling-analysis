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

	std::thread iothread(dispatcher::exec_io,
			     pool::wait_queue.begin());
	iothread.detach();
    }

    void context_switch(std::vector<process>::iterator& pit, int tq)
    {
	save_state(pit, tq);
	restore_state(pit);
    }

    void save_state(std::vector<process>::iterator& pit, int ttl_p)
    {
	pit->set_prev_exec_time(scheduler::total_t);
	pit->set_work_done(ttl_p);
    }

    void restore_state(std::vector<process>::iterator& pit)
    {
	if (pit->is_done()) {
	    pit->set_toc(scheduler::total_t);
	    pit->add_tat(pit->get_toc() - pit->get_tos());

	    pool::done_queue.push_back(std::move(*pit));
	    pit = pool::ready_queue.erase(pit);

	    scheduler::calc_current_awt();
	    PSAscreen::get().show_wt(scheduler::current_awt);

	    PSAscreen::get().push_prc_in(
		PSAscreen::get().get_wdone(), pool::done_queue);
	    PSAscreen::get().draw_frame_of(
		PSAscreen::get().get_wdone(), " DONE ");
	} else {
	    std::rotate(pool::ready_queue.begin(),
			pit + 1,
			pool::ready_queue.end());

	    PSAscreen::get().push_prc_in(
		PSAscreen::get().get_wprc(), pool::ready_queue);
	    PSAscreen::get().draw_frame_of(
		PSAscreen::get().get_wprc(), " PROCESS ");
	}
    }

    void exec_io(std::vector<process>::iterator pit)
    {
	iomutex.lock();

	auto io_ttl = pit->get_ioops().begin();
	std::this_thread::sleep_for(std::chrono::milliseconds(*io_ttl));
	pit->add_tat(*io_ttl);
	pit->get_ioops().erase(io_ttl);

	pool::ready_queue.push_back(std::move(*pit));
	pool::wait_queue.erase(pit);

	iomutex.unlock();
    }

    namespace cfs
    {
	void interpt(process &pit, int tq, rbtree &rbt)
	{
	    //save_st(pit, tq);

	    pool::wait_queue.push_back(std::move(pit));
	    //pit = pool::ready_queue.erase(pit);

	    std::thread iothread(dispatcher::cfs::ex_io,
				 pool::wait_queue.begin());
	    iothread.detach();
	}

	void con_swch(process &pit, int tq, rbtree &rbt)
	{
	    save_st(pit, tq);
	    restore_st(pit, rbt);
	}

	void save_st(process &pit, int ttl_p)
	{
	    pit.set_prev_exec_time(scheduler::total_t);
	    pit.set_work_done(ttl_p);
	}

	void restore_st(process &pit, rbtree &rbt)
	{
	    if (pit.is_done()) {
		pit.set_toc(scheduler::total_t);
		pit.add_tat(pit.get_toc() - pit.get_tos());

		rbt.dq.push_back(std::move(pit));

		//scheduler::calc_current_awt();
		//PSAscreen::get().show_wt(scheduler::current_awt);
	    } else {
		rbt.insert(pit);
	    }
	    PSAscreen::get().push_prc_in(
		PSAscreen::get().get_wdone(), rbt.dq);
	    PSAscreen::get().draw_frame_of(
		PSAscreen::get().get_wdone(), " DONE ");
	    PSAscreen::get().push_prc_in(
		PSAscreen::get().get_wprc(), rbt.rq);
	    PSAscreen::get().draw_frame_of(
		PSAscreen::get().get_wprc(), " PROCESS ");
	}

	void ex_io(std::vector<process>::iterator pit)
	{
	    iomutex.lock();

	    auto io_ttl = pit->get_ioops().begin();
	    std::this_thread::sleep_for(std::chrono::milliseconds(*io_ttl));
	    pit->add_tat(*io_ttl);
	    pit->get_ioops().erase(io_ttl);

	    pool::ready_queue.push_back(std::move(*pit));
	    pool::wait_queue.erase(pit);

	    iomutex.unlock();
	}
    }
}
