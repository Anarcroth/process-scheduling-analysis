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

const double scheduler::ALPHA = 0.5;
const int scheduler::TIME_QUANTUM = 50;

int scheduler::avg_wt = 0;
int scheduler::avg_tat = 0;
int scheduler::total_t = 0;
int scheduler::prev_pr_burst = 1000;

scheduler::scheduler() {}

void scheduler::reset()
{
    avg_wt = 0;
    avg_tat = 0;
    total_t = 0;
}

void scheduler::exec(int tq)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(tq));
    total_t += tq;
}

void scheduler::take(std::vector<process>::iterator& pit, int tq)
{
    pit->set_tos(total_t);
    pit->add_wait_t(total_t);

    if (pit->has_io()) {
	exec(tq / 2);
	dispatcher::interrupt(pit, tq / 2);
    } else {
	exec(tq);
	dispatcher::context_switch(pit, tq);
    }
}

void scheduler::fcfs()
{
    reset();
    pool::eval_prcs_prty();
    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {
	// first show the process, then execute it
	PSAscreen::get().show_process(*pit);
	take(pit, pit->get_ttl());

	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
    }
    PSAscreen::get().show_statistics(avg_wt, avg_tat);
}

void scheduler::sjf()
{
    reset();
    pool::eval_prcs_prty();

    int prediction = prev_pr_burst;
    auto pit = pool::ready_queue.begin();
    while (pit != pool::ready_queue.end()) {
	// first show the process, then execute it
	PSAscreen::get().show_process(*pit);

	// must be saved before the next process comes
	int prev_pr_ttl = pit->get_ttl();
	take(pit, prediction);
	prediction = exponential_average(prev_pr_ttl);

	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
    }
    PSAscreen::get().show_statistics(avg_wt, avg_tat);
}

int scheduler::exponential_average(int prev_pr_ttl)
{
    prev_pr_burst = ALPHA * prev_pr_ttl + (1 - ALPHA) * prev_pr_burst;
    return prev_pr_burst;
}

void scheduler::round_rob()
{
    reset();
    pool::eval_prcs_prty();
    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {
	// first show the process, then execute it
	PSAscreen::get().show_process(*pit);
	take(pit, TIME_QUANTUM);
    }
    PSAscreen::get().show_statistics(avg_wt, avg_tat);
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
	// first show the process, then execute it
	PSAscreen::get().show_process(*pit);
	take(pit, pit->get_ttl());

	PSAscreen::get().push_prc_in(PSAscreen::get().get_wprc(), pool::ready_queue);
	PSAscreen::get().draw_frame_of(PSAscreen::get().get_wprc(), " PROCESS ");
    }
    PSAscreen::get().show_process(*pit);
}
