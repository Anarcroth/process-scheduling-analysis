#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include <queue>

class process;

class alg
{
public:
    alg();
    ~alg();

    void work();

protected:
    // TODO use smart pointers instead of raw ones
    std::queue<process*> p_que;
};

#endif
