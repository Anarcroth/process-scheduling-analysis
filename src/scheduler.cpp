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

/*
 * Description: resets all of the global
 * variables used across every algorithm.
 */
void scheduler::reset()
{
    avg_wt = 0;
    avg_tat = 0;
    total_t = 0;
    prev_pr_burst = 0;
}

/*
 * Description: executes the passed time quantum
 * `tq` and increments the total time of execution.
 *
 * By execution it is meant that the main program
 * sleeps for the `tq` amount.
 */
void scheduler::exec(int tq)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(tq));
    total_t += tq;
}

/*
 * Description: takes each process, sets it up and
 * checks for IO. Then it sends the process to be
 * executed.
 */
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

/*
 * Description: first come first serve algorithm.
 *
 * Each process has its priority evaluated, then
 * is taken from the start of the queue and is
 * executed sequentially. Each process _can_
 * have IO and be pushed to the ready queue again.
 * At the end, the statistics of executions are shown.
 */
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
    PSAscreen::get().show_statistics(summaries);
}

/*
 * Description: shortest job first.
 *
 * Each process has its priority evaluated. Then
 * an execution estimation is made as to how long
 * should that process execute. This prediction is
 * updated on every that comes next. Each process _can_
 * have IO and be pushed to the ready queue again.
 * At the end, the statistics of executions are shown.
 */
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
    PSAscreen::get().show_statistics(summaries);
}

/*
 * Description: calculates the next expected duration
 * of a process CPU burst and returns it as a recommendation.
 */
int scheduler::exponential_average(int prev_pr_ttl)
{
    prev_pr_burst = ALPHA * prev_pr_ttl + (1 - ALPHA) * prev_pr_burst;
    return prev_pr_burst;
}

/*
 * Description: round-robin.
 *
 * Each process has its priority evaluated. Each
 * sequential process is taken and is executed for
 * a constant `TIME_QUANTUM`. Each process _can_
 * have IO and be pushed to the ready queue again.
 * At the end, the statistics of executions are shown.
 */
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
    PSAscreen::get().show_statistics(summaries);
}

/*
 * Description: priority job first.
 *
 * Each process has its priority evaluated. The processes
 * are ordered based on their labeled priority and
 * are executed. Each process _can_ have IO and be
 * pushed to the ready queue again. At the end, the
 * statistics of executions are shown.
 */
void scheduler::pjf()
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
    PSAscreen::get().show_statistics(summaries);
}

void scheduler::add_to_summaries()
{
    for (auto& p : pool::done_queue) {
	avg_tat += p.get_tat();
	avg_wt += p.get_wait_t();
    }
    avg_tat /= pool::done_queue.size();
    avg_wt /= pool::done_queue.size();
    std::string sumr = "Average Waiting Time: " + std::to_string(avg_wt) +
	"\nAverage Turnaround Time: " + std::to_string(avg_tat);
    summaries.push_back(sumr);
}
