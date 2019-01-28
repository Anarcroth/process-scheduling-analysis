#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include <vector>

class process;

class alg
{
public:
    alg();
    alg(int awt);
    ~alg();

    virtual int get_awt() = 0;
    virtual void work(std::vector<process*> &processes) = 0;

    int average_wait_time;
};

#endif
