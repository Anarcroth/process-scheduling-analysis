#include <chrono>
#include <thread>

#include "fcfs.h"
#include "process.h"

fcfs::fcfs()
{
}

void fcfs::work()
{
    while (p_que.size() > 0)
    {
	std::this_thread::sleep_for(std::chrono::milliseconds(p_que.front()->get_ttl()));
	p_que.pop();
    }
}
