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
    reset();
    pool::eval_prcs_prty();
    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {

	take(pit, pit->get_ttl());

	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
	PSAscreen::get().show_awt(avg_wait_t);
	PSAscreen::get().show_process(*pit);
    }
    int avg_tat = 0;
    for (auto& p : pool::done_queue) {
	avg_tat += p.get_tat();
    }
    PSAscreen::get().show_tat(avg_tat / pool::done_queue.size());
    wrefresh(PSAscreen::get().get_walg());
}

void scheduler::sjf()
{
    reset();
    pool::eval_prcs_prty();
    std::sort(pool::ready_queue.begin(),
	      pool::ready_queue.end(),
	      [] (const process a, const process b) {
		  return a.get_ttl() < b.get_ttl();
	      });
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
    reset();
    pool::eval_prcs_prty();
    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {
	take(pit, TIME_QUANTUM);

	PSAscreen::get().show_awt(avg_wait_t);
	PSAscreen::get().show_process(*pit);
    }
}

void scheduler::pfj()
{
    reset();
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
    pit->set_tos(tt);

    if (pit->has_io()) {
	exec(pit, tq / 2);
	dispatcher::interrupt(pit, tq / 2);
    }
    else {
	exec(pit, tq);
	dispatcher::context_switch(pit, tq);
    }
}

void scheduler::reset()
{
    tt = 0;
    avg_wait_t = 0;
}
