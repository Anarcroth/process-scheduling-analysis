#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include <vector>

class process;

class alg
{
public:
    alg();
    alg(int awt, std::vector<process*> prs);
    ~alg();

    int get_awt() const;

    virtual void work() = 0;

    int average_wait_time;
    std::vector<process*> processes;
};

#endif
