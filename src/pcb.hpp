#ifndef __PCB_H_INCLUDED__
#define __PCB_H_INCLUDED__

#include <string>

#include "process.hpp"

enum class state
{
    NEW = 0,
    READY,
    RUNNING,
    WAITING,
    TERMINATED
};

class pcb
{
public:
    void save_state();
    void restore_state();

    void set_process(process _pr);

    process get_process();

private:
    int wait_time;
    state pr_state;
    process pr;
};

#endif
