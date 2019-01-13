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

    std::string get_pr() const;
    std::string get_id() const;
    unsigned int get_ttl() const;

private:
    priority pr;
    std::string id;
    unsigned int ttl;

    priority set_pr();
    std::string set_id();
    unsigned int set_ttl();
};

#endif
