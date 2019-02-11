#include <vector>

#include "pool.hpp"
#include "commons.hpp"
#include "priority.hpp"

pool::pool()
{
}

pool& pool::get()
{
    static pool instance;
    return instance;
}

void pool::make_pr(int ch)
{
    pcb pr_block;
    switch (ch)
    {
    case 'r':
	pr_block.set_process(process());
	break;
    case 'l':;
	pr_block.set_process(process(priority::LOW));
	break;
    case 'm':
	pr_block.set_process(process(priority::MEDIUM));
	break;
    case 'h':
	pr_block.set_process(process(priority::HIGH));
	break;
    case 'x':
	pr_block.set_process(process(priority::EXTREME));
	break;
    }
    processes.push_back(pr_block);
}

void pool::push(process &pr)
{
    processes.push_back(pr);
}

void pool::set_pool(std::vector<pcb> pr_pool)
{
    process_pool = pr_pool;
}

std::vector<pcb>& pool::get_pool()
{
    return processes;
}
