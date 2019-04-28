#include <vector>
#include <thread>
#include <chrono>
#include <utility>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "scheduler.hpp"
#include "process.hpp"
#include "screen.hpp"
#include "pool.hpp"
#include "dispatcher.hpp"
#include "commons.hpp"
#include "cfs/rbtree.hpp"

void log1(const std::string &text)
{
    std::ofstream log_file(
        "log_file.txt", std::ios_base::out | std::ios_base::app);
    log_file << text << std::endl;
}

const double scheduler::ALPHA = 0.5;
const int scheduler::TIME_QUANTUM = 50;

int scheduler::avg_wt = 0;
int scheduler::avg_tat = 0;
int scheduler::total_t = 0;
int scheduler::prev_pr_burst = 1000;
int scheduler::current_awt = 0;

scheduler::scheduler() {}

/*
 * Description: resets all of the global
 * variables used across every algorithm.
 * Clear the DONE panel and done queue.
 */
void scheduler::reset()
{
    avg_wt = 0;
    avg_tat = 0;
    total_t = 0;
    prev_pr_burst = 0;
    current_awt = 0;

    pool::clear();

    PSAscreen::get().clear_scr();
    PSAscreen::get().get_table_partitionings();
    PSAscreen::get().draw_w_scale();
    PSAscreen::get().push_prc_in(PSAscreen::get().get_wdone(), pool::done_queue);
    PSAscreen::get().draw_frame_of(PSAscreen::get().get_wdone(), " DONE ");
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
    PSAscreen::get().show_alg_info("FCFS");

    reset();
    pool::eval_prcs_prty();
    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {
	PSAscreen::get().update_process_scr(*pit);

	pit->set_tos(total_t);
	pit->add_wait_t(total_t);
	exec(pit->get_ttl());
	if (pit->has_io()) {
	    dispatcher::interrupt(pit, pit->get_ciopart());
	} else {
	    dispatcher::context_switch(pit, pit->get_ciopart());
	}
    }
    add_summary("FCFS");
    PSAscreen::get().show_statistics(summaries);
}

/*
 * Description: shortest job first (basic version).
 *
 * Each process has its priority evaluated. Then the
 * pool of processes are evaluated based on their
 * `ttl`, starting from the shortest to the longest.
 * Each process _can_ have IO and be pushed to the
 * ready queue again. At the end, the statistics of
 * executions are shown.
 */
void scheduler::sjf_v1()
{
    PSAscreen::get().show_alg_info("SJF");

    reset();
    pool::eval_prcs_prty();
    std::sort(pool::ready_queue.begin(),
	      pool::ready_queue.end(),
	      [] (const process a, const process b) {
		  return a.get_ttl() < b.get_ttl();
	      });
    auto pit = pool::ready_queue.begin();
    while (pit != pool::ready_queue.end()) {
	PSAscreen::get().update_process_scr(*pit);

	take(pit, pit->get_ttl());
    }
    add_summary("SJF V1");
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
void scheduler::sjf_v2()
{
    PSAscreen::get().show_alg_info("SJF");

    reset();
    pool::eval_prcs_prty();

    int prediction = prev_pr_burst;
    auto pit = pool::ready_queue.begin();
    while (pit != pool::ready_queue.end()) {
	PSAscreen::get().update_process_scr(*pit);

	// must be saved before the next process comes
	int prev_pr_ttl = pit->get_ttl();
	take(pit, prediction);
	prediction = exponential_average(prev_pr_ttl);
    }
    add_summary("SJF V2");
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
    PSAscreen::get().show_alg_info("RR");

    reset();
    pool::eval_prcs_prty();
    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {
	PSAscreen::get().show_process(*pit);
	take(pit, TIME_QUANTUM);

    }
    add_summary("Round Robin");
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
    PSAscreen::get().show_alg_info("PJF");

    reset();
    pool::eval_prcs_prty();
    std::sort(pool::ready_queue.begin(),
	      pool::ready_queue.end(),
	      [] (const process a, const process b) {
		  return a.get_prty() > b.get_prty();
	      });

    auto pit = pool::ready_queue.begin();
    while (!pool::empty()) {
	PSAscreen::get().update_process_scr(*pit);

	take(pit, pit->get_ttl());
    }
    add_summary("PJF");
    PSAscreen::get().show_statistics(summaries);
}

void scheduler::cfs()
{
    PSAscreen::get().show_alg_info("CFS");

    reset();
    pool::eval_prcs_prty();

    rbtree rbt;
    for (auto p : pool::ready_queue)
    	rbt.insert(p);

    // small hack to make the thing more optimal
    rbt.fix_internal_repr();

    while (!rbt.empty()) {

	sched_entity *shortest = rbt.get_smallest(rbt.root);
	process pr = shortest->key;

	rbt.delete_node(shortest);

	PSAscreen::get().update_process_scr(pr);

	// stats
	pr.set_tos(total_t);
	pr.add_wait_t(total_t);

	// exec time calc
	pr.calc_max_exec_t();
	int exec_t = 0;
	if (pr.get_max_exec_t() > 0)
	    exec_t = pr.get_max_exec_t();
	else
	    exec_t = pr.get_ttl();

	// IO
	if (pr.has_io())
	    exec(exec_t / 2);
	else
	    exec(exec_t);

	pr.add_vruntime(exec_t);
	dispatcher::cfs::con_swch(pr, exec_t, rbt);
    }
    // these queues have to be cleared otherwise
    // they will be in a polluted state
    pool::ready_queue.clear();
    rbt.rq.clear();

    pool::done_queue = rbt.dq;
    add_summary("CFS");
    PSAscreen::get().show_statistics(summaries);
}

void scheduler::add_summary(std::string algname)
{
    for (auto& p : pool::done_queue) {
	avg_tat += p.get_tat();
	avg_wt += p.get_wait_t();
    }
    avg_tat /= pool::done_queue.size();
    avg_wt /= pool::done_queue.size();
    std::string sumr = algname +
	" (" + std::to_string(pool::done_queue.size()) + ") >" +
	" Average Waiting Time: " + std::to_string(avg_wt) +
	" Average Turnaround Time: " + std::to_string(avg_tat) +
	"                ";

    summaries.insert(summaries.begin(), sumr);
}

void scheduler::calc_current_awt(std::vector<process> d_queue)
{
    for (auto& p : d_queue)
	current_awt += p.get_wait_t();

    current_awt = current_awt /	d_queue.size();
}
