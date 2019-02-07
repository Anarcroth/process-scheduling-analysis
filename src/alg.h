#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include <vector>
#include <memory>

#include "process.h"

class alg
{
public:
    alg(int awt, std::vector<std::unique_ptr<process>> prs);

    int get_awt() const;

    virtual void work() = 0;

    int average_wait_time;
    std::vector<std::unique_ptr<process>> processes;
};

#endif
