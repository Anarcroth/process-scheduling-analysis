#ifndef __PCB_H_INCLUDED__
#define __PCB_H_INCLUDED__

#include <string>

#include "process.h"

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
    pcb(process _pr);

    void save_state();
    void restore_state();

private:
    int wait_time;
    state pr_state;
    process pr;
};

#endif
