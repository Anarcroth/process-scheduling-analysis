#ifndef __PROCESS_H_INCLUDED__
#define __PROCESS_H_INCLUDED__

#include <string>

#include "priority.h"

class process
{
public:
    process();
    process(priority pr);
    process(priority pr, unsigned int ttl);

    priority get_pr();
    std::string get_id();
    unsigned int get_ttl();

private:
    priority pr;
    std::string id;
    unsigned int ttl;
};

#endif
