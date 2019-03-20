#include <thread>
#include <chrono>
#include <utility>
#include <algorithm>

#include "scheduler.hpp"
#include "process.hpp"
#include "screen.hpp"
#include "pool.hpp"
#include "dispatcher.hpp"
#include "commons.hpp"

const int scheduler::TIME_QUANTUM = 50;
int scheduler::tt = 0;

scheduler::scheduler() : avg_wait_t(0) {}

int scheduler::get_awt() const
{
    return avg_wait_t;
}

void scheduler::exec(std::vector<process>::iterator& pit, int tq)
{
    tt += tq;
    std::this_thread::sleep_for(std::chrono::milliseconds(tq));
    avg_wait_t += tq;
}

void scheduler::fcfs()
{
    tt = 0;
    avg_wait_t = 0;
    pool::eval_prcs_prty();
    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {
	pit->set_tos(tt);
	take(pit, pit->get_ttl());

	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	PSAscreen::get().show_awt(avg_wait_t);
	PSAscreen::get().show_process(*pit);
    }
}

void scheduler::sjf()
{
    pool::eval_prcs_prty();
    std::sort(pool::ready_queue.begin(),
	      pool::ready_queue.end(),
	      [] (const process a, const process b) {
		  return a.get_ttl() < b.get_ttl();
	      });

    avg_wait_t = 0;
    auto pit = pool::ready_queue.begin();
    while (pit != pool::ready_queue.end()) {
	take(pit, pit->get_ttl());

	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	PSAscreen::get().show_awt(avg_wait_t);
	PSAscreen::get().show_process(*pit);
    }
}

void scheduler::round_rob()
{
    pool::eval_prcs_prty();
    avg_wait_t = 0;
    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {
	take(pit, TIME_QUANTUM);

	PSAscreen::get().show_awt(avg_wait_t);
	PSAscreen::get().show_process(*pit);
    }
}

void scheduler::pfj()
{
    pool::eval_prcs_prty();
    std::sort(pool::ready_queue.begin(),
	      pool::ready_queue.end(),
	      [] (const process a, const process b) {
		  return a.get_prty() > b.get_prty();
	      });

    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {
	take(pit, pit->get_ttl());

	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	PSAscreen::get().show_awt(avg_wait_t);
	PSAscreen::get().show_process(*pit);
    }
}

void scheduler::take(std::vector<process>::iterator& pit, int tq)
{
    if (pit->has_io()) {
	exec(pit, tq / 2);
	dispatcher::interrupt(pit, tq / 2);
    }
    else {
	exec(pit, tq);
	dispatcher::context_switch(pit, tq);
    }
}
