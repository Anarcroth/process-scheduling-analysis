#ifndef __SJF_H_INCLUDED__
#define __SJF_H_INCLUDED__

#include "alg.h"

class sjf : public alg
{
public:
    sjf();
    ~sjf();

    virtual void work(std::vector<process*> &processes) override;

private:
    void exec(std::vector<process*> &processes, std::vector<process*> &prs_sorted_by_ttl);
};

#endif
