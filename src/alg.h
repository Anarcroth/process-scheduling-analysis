#ifndef __ALG_H_INCLUDED__
#define __ALG_H_INCLUDED__

#include <vector>

class process;

class alg
{
public:
    alg();
    ~alg();

    void work();
private:
    std::vector<process*> queue;
};

#endif
