#ifndef __FCFS_H_INCLUDED__
#define __FCFS_H_INCLUDED__

#include <vector>

class process;

class fcfs
{
public:
    fcfs();
    ~fcfs();
private:
    std::vector<process*> queue;
};
